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
#include <fakeMotorDevice.h>

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
using namespace yarp::os;
using namespace yarp::dev;

/**
 * This class launches the server.
 */
class ServerModule: public RFModule
{
protected:
    PolyDriver partDrv;
    PolyDriver server;

public:
    /**********************************************************/
    bool configure(ResourceFinder &rf)
    {   
        // grab parameters from the configuration file
        string robot=rf.find("robot").asString();
        string part=rf.find("part").asString();
        string local=rf.find("local").asString();
        string pathToKin=rf.findFile("kinematics_file");

        // prepare the option to open up the device driver to
        // access the fake robot
        Property optPart;
        optPart.put("device","fakeyClient");
        optPart.put("remote","/"+robot+"/"+part);
        optPart.put("local","/"+local+"/"+part);
        optPart.put("part",part);

        // open the device driver
        if (!partDrv.open(optPart))
        {
            cout<<"Error: Device driver not available!"<<endl;
            close();
            return false;
        }

        // now go on with the server driver
        PolyDriverList list;
        list.push(&partDrv,part.c_str());

        // take the parameters and fill the kinematic description
        Property optServer("(device cartesiancontrollerserver)");
        optServer.fromConfigFile(rf.findFile("from"),false);
        if (!server.open(optServer))
        {
            cout<<"Error: Unable to open the Cartesian Controller Server!"<<endl;
            close();    
            return false;
        }

        // attach the device driver to the server
        IMultipleWrapper *wrapper;
        server.view(wrapper);
        if (!wrapper->attachAll(list))
        {
            cout<<"Error: Unable to attach device drivers!"<<endl;
            close();    
            return false;
        }

        return true;
    }

    /**********************************************************/
    bool close()
    {
        if (server.isValid())
            server.close();

        if (partDrv.isValid())
            partDrv.close();

        return true;
    }

    /**********************************************************/
    double getPeriod()    { return 1.0;  }
    bool   updateModule() { return true; }
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

    // register here the new yarp devices
    // for dealing with the fake robot
    registerFakeMotorDevices();

    ResourceFinder rf;
    rf.setDefaultConfigFile("server.ini");
    rf.setDefault("robot","fake_robot");
    rf.setDefault("part","fake_part");
    rf.setDefault("local","server");
    rf.setDefault("kinematics_file","kinematics.ini");
    rf.configure(argc,argv);

    ServerModule server;
    return server.runModule(rf);
}


