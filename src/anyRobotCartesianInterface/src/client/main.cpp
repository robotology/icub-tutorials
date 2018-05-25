/* 
 * Copyright (C) 2011 Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
 * Author: Ugo Pattacini
 * email:  ugo.pattacini@iit.it
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
*/

#include <yarp/os/all.h>
#include <yarp/dev/all.h>
#include <yarp/sig/all.h>
#include <yarp/math/Math.h>
#include <yarp/math/Rand.h>

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
using namespace yarp::os;
using namespace yarp::dev;
using namespace yarp::sig;
using namespace yarp::math;

/**
 * This class implements the client.
 */
class ClientModule: public RFModule
{
protected:
    PolyDriver         client;
    ICartesianControl *arm;
    Vector xdhat;

public:
    /**********************************************************/
    bool configure(ResourceFinder &rf)
    {
        string remote=rf.find("remote").asString();
        string local=rf.find("local").asString();

        // Just usual things...
        Property option("(device cartesiancontrollerclient)");
        option.put("remote","/"+remote);
        option.put("local","/"+local);

        if (!client.open(option))
            return false;

        // open the view
        client.view(arm);
        arm->setTrajTime(2.0);
        arm->setInTargetTol(1e-3);

        Vector dof;
        arm->getDOF(dof);
        for (size_t i=0; i<dof.length(); i++)
        {
            double min,max;
            arm->getLimits(i,&min,&max);

            // these margins are just to prevent the
            // solver from solving for exactly the
            // joints bounds
            min+=1.0; max-=1.0; // [deg]
            arm->setLimits(i,min,max);
        }

        Rand::init();

        return true;
    }

    /**********************************************************/
    bool close()
    {
        if (client.isValid())
            client.close();

        return true;
    }

    /**********************************************************/
    bool updateModule()
    {
        bool done=false;
        arm->checkMotionDone(&done);
        if (done)
        {
            Vector xd(3);
            xd[0]=Rand::scalar(1.0,2.5);
            xd[1]=Rand::scalar(0.0,2.0);
            xd[2]=0.0;

            cout<<endl;
            cout<<"Solving for: ("<<xd.toString()<<")"<<endl;
            arm->goToPositionSync(xd);
            Vector odhat,qdhat;
            arm->getDesired(xdhat,odhat,qdhat);
            cout<<"Going to: ("<<xdhat.toString()<<")"<<endl;
            cout<<"Solved Configuration: ["<<qdhat.toString()<<"]"<<endl;
        }
        else
        {
            Vector x,o;
            arm->getPose(x,o);
            cout<<"Running: ("<<x.toString()<<");  distance to go: "<<norm(xdhat-x)<<endl;
        }

        return true;
    }

    /**********************************************************/
    double getPeriod() { return 0.4; }
};


/**********************************************************/
int main(int argc, char *argv[])
{   
    Network yarp;
    if (!yarp.checkNetwork())
    {
        cout<<"Error: yarp server does not seem available"<<endl;
        return 1;
    }

    ResourceFinder rf;
    rf.setVerbose(true);
    rf.setDefault("remote","server");
    rf.setDefault("local","client");
    rf.configure(argc,argv);

    ClientModule client;
    return client.runModule(rf);
}



