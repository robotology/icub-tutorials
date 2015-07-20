// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-
//
// A tutorial on how to use the Gaze Interface.
//
// Author: Ugo Pattacini - <ugo.pattacini@iit.it>

#include <yarp/os/Network.h>
#include <yarp/os/RFModule.h>
#include <yarp/os/RateThread.h>
#include <yarp/os/Time.h>
#include <yarp/sig/Vector.h>
#include <yarp/math/Math.h>

#include <yarp/dev/Drivers.h>
#include <yarp/dev/ControlBoardInterfaces.h>
#include <yarp/dev/GazeControl.h>
#include <yarp/dev/PolyDriver.h>

#include <gsl/gsl_math.h>

#include <stdio.h>
#include <deque>

#define CTRL_THREAD_PER     0.02        // [s]
#define PRINT_STATUS_PER    1.0         // [s]
#define STORE_POI_PER       3.0         // [s]
#define SWITCH_STATE_PER    10.0        // [s]
#define STILL_STATE_TIME    5.0         // [s]

#define STATE_TRACK         0
#define STATE_RECALL        1
#define STATE_WAIT          2
#define STATE_STILL         3

using namespace std;
using namespace yarp::os;
using namespace yarp::dev;
using namespace yarp::sig;
using namespace yarp::math;


class CtrlThread: public RateThread,
                  public GazeEvent
{
protected:
    PolyDriver        clientGaze;
    PolyDriver        clientTorso;
    IGazeControl     *igaze;
    IEncoders        *ienc;
    IPositionControl *ipos;

    int state;
    int startup_context_id;

    Vector fp;

    deque<Vector> poiList;

    double t;
    double t0;
    double t1;
    double t2;
    double t3;
    double t4;

    // the motion-done callback
    virtual void gazeEventCallback()
    {
        Vector ang;
        igaze->getAngles(ang);

        fprintf(stdout,"Actual gaze configuration: (%s) [deg]\n",
                ang.toString(3,3).c_str());

        fprintf(stdout,"Moving the torso; see if the gaze is compensated ...\n");

        // move the torso yaw
        double val;
        ienc->getEncoder(0,&val);
        ipos->positionMove(0,val>0.0?-30.0:30.0);

        t4=t;
        
        // detach the callback
        igaze->unregisterEvent(*this);

        // switch state
        state=STATE_STILL;
    }

public:
    CtrlThread(const double period) : RateThread(int(period*1000.0))
    {
        // here we specify that the event we are interested in is
        // of type "motion-done"
        gazeEventParameters.type="motion-done";
    }

    virtual bool threadInit()
    {
        // open a client interface to connect to the gaze server
        // we suppose that:
        // 1 - the iCub simulator is running;
        // 2 - the gaze server iKinGazeCtrl is running and
        //     launched with the following options: "--from configSim.ini"
        Property optGaze("(device gazecontrollerclient)");
        optGaze.put("remote","/iKinGazeCtrl");
        optGaze.put("local","/gaze_client");

        if (!clientGaze.open(optGaze))
            return false;

        // open the view
        clientGaze.view(igaze);

        // latch the controller context in order to preserve
        // it after closing the module
        // the context contains the tracking mode, the neck limits and so on.
        igaze->storeContext(&startup_context_id);

        // set trajectory time:
        igaze->setNeckTrajTime(0.8);
        igaze->setEyesTrajTime(0.4);

        // put the gaze in tracking mode, so that
        // when the torso moves, the gaze controller 
        // will compensate for it
        igaze->setTrackingMode(true);

        // print out some info about the controller
        Bottle info;
        igaze->getInfo(info);
        fprintf(stdout,"info = %s\n",info.toString().c_str());

        Property optTorso("(device remote_controlboard)");
        optTorso.put("remote","/icubSim/torso");
        optTorso.put("local","/torso_client");

        if (!clientTorso.open(optTorso))
            return false;

        // open the view
        clientTorso.view(ienc);
        clientTorso.view(ipos);
        ipos->setRefSpeed(0,10.0);

        fp.resize(3);

        state=STATE_TRACK;

        t=t0=t1=t2=t3=t4=Time::now();

        return true;
    }

    virtual void afterStart(bool s)
    {
        if (s)
            fprintf(stdout,"Thread started successfully\n");
        else
            fprintf(stdout,"Thread did not start\n");        
    }

    virtual void run()
    {
        t=Time::now();

        generateTarget();

        if (state==STATE_TRACK)
        {
            // look at the target (streaming)
            igaze->lookAtFixationPoint(fp);

            // some verbosity
            printStatus();

            // we collect from time to time
            // some interesting points (POI)
            // where to look at soon afterwards
            storeInterestingPoint();

            if (t-t2>=SWITCH_STATE_PER)
            {
                // switch state
                state=STATE_RECALL;
            }
        }

        if (state==STATE_RECALL)
        {
            // pick up the first POI
            // and clear the list
            Vector ang=poiList.front();
            poiList.clear();

            fprintf(stdout,"Retrieving POI #0 ... (%s) [deg]\n",
                    ang.toString(3,3).c_str());

            // register the motion-done event, attaching the callback
            // that will be executed as soon as the gaze is accomplished
            igaze->registerEvent(*this);

            // look at the chosen POI
            igaze->lookAtAbsAngles(ang);

            // switch state
            state=STATE_WAIT;
        }

        if (state==STATE_STILL)
        {
            if (t-t4>=STILL_STATE_TIME)
            {
                fprintf(stdout,"done\n");

                t1=t2=t3=t;

                // switch state
                state=STATE_TRACK;
            }
        }
    }

    virtual void threadRelease()
    {    
        // we require an immediate stop
        // before closing the client for safety reason
        igaze->stopControl();

        // it's a good rule to restore the controller
        // context as it was before opening the module
        igaze->restoreContext(startup_context_id);

        clientGaze.close();
        clientTorso.close();
    }

    void generateTarget()
    {   
        // translational target part: a circular trajectory
        // in the yz plane centered in [-0.5,0.0,0.3] with radius=0.1 m
        // and frequency 0.1 Hz
        fp[0]=-0.5;
        fp[1]=+0.0+0.1*cos(2.0*M_PI*0.1*(t-t0));
        fp[2]=+0.3+0.1*sin(2.0*M_PI*0.1*(t-t0));            
    }

    void storeInterestingPoint()
    {
        if (t-t3>=STORE_POI_PER)
        {
            Vector ang;

            // we store the current azimuth, elevation
            // and vergence wrt the absolute reference frame
            // The absolute reference frame for the azimuth/elevation couple
            // is head-centered with the robot in rest configuration
            // (i.e. torso and head angles zeroed). 
            igaze->getAngles(ang);

            int numPOI=(int)poiList.size();
            fprintf(stdout,"Storing POI #%d: (%s) [deg]\n",
                    numPOI,ang.toString(3,3).c_str());

            poiList.push_back(ang);

            t3=t;
        }
    }

    void printStatus()
    {        
        if (t-t1>=PRINT_STATUS_PER)
        {
            // we get the current fixation point in the
            // operational space
            Vector x;
            igaze->getFixationPoint(x);

            fprintf(stdout,"+++++++++\n");
            fprintf(stdout,"fp         [m] = (%s)\n",fp.toString(3,3).c_str());
            fprintf(stdout,"x          [m] = (%s)\n",x.toString(3,3).c_str());
            fprintf(stdout,"norm(fp-x) [m] = %g\n",norm(fp-x));
            fprintf(stdout,"---------\n\n");

            t1=t;
        }
    }
};



class CtrlModule: public RFModule
{
protected:
    CtrlThread *thr;

public:
    virtual bool configure(ResourceFinder &rf)
    {
        Time::turboBoost();

        thr=new CtrlThread(CTRL_THREAD_PER);
        if (!thr->start())
        {
            delete thr;
            return false;
        }

        return true;
    }

    virtual bool close()
    {
        thr->stop();
        delete thr;

        return true;
    }

    virtual double getPeriod()    { return 1.0;  }
    virtual bool   updateModule() { return true; }
};



int main(int argc, char *argv[])
{
    Network yarp;
    if (!yarp.checkNetwork())
    {
        fprintf(stdout,"Error: yarp server does not seem available\n");
        return 1;
    }

    CtrlModule mod;

    ResourceFinder rf;
    return mod.runModule(rf);
}



