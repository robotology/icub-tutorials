// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include <yarp/os/Network.h>
#include <yarp/os/RateThread.h>
#include <yarp/os/Time.h>
#include <yarp/os/Property.h>
#include <yarp/dev/ControlBoardInterfaces.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/sig/Vector.h>

#include <string>
#include <iostream>

using namespace yarp::os;
using namespace yarp::dev;
using namespace yarp::sig;

using namespace std;

class ControlThread: public RateThread
{
    PolyDriver dd;
    IVelocityControl *ivel;
    IEncoders        *iencs;
    Vector encoders;
    Vector commands;
    int count;
public:
    ControlThread(int period):RateThread(period){}

    bool threadInit()
    {
        //initialize here variables
        printf("ControlThread:starting\n");
        
        Property options;
        options.put("device", "remote_controlboard");
        options.put("local", "/local/head");
        options.put("remote", "/icubSim/head");
        
        dd.open(options);

        dd.view(iencs);
        dd.view(ivel);

        if ( (!iencs) || (!ivel) )
            return false;
        
        int joints;
   
        iencs->getAxes(&joints);
    
        encoders.resize(joints);
        commands.resize(joints);

        commands=10000;
        ivel->setRefAccelerations(commands.data());

        count=0;
        return true;
    }

    void threadRelease()
    {
        printf("ControlThread:stopping the robot\n");
        
        ivel->stop();

        dd.close();

        printf("Done, goodbye from ControlThread\n");
    }

    void run()
    {
        //do the work
        iencs->getEncoders(encoders.data());

        count++;

        if (count%2)
            commands=5;
        else
            commands=-5;
    
        ivel->velocityMove(commands.data());

        printf(".");
    }
};

int main(int argc, char *argv[]) 
{
    Network yarp;

    if (!yarp.checkNetwork())
    {
        printf("No yarp network, quitting\n");
        return false;
    }


    ControlThread myThread(4000); //period is 40ms

    myThread.start();

    bool done=false;
    double startTime=Time::now();
    while(!done)
    {
        if ((Time::now()-startTime)>5)
            done=true;
    }
    
    myThread.stop();

    return 0;
}
