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

using namespace std;
using namespace yarp::os;
using namespace yarp::dev;

/**
 * This container class launches the server part of the
 * fake motor device in order to simulate a robot called
 * "fake_robot" wiht the part "fake_part" composed of three
 * actuated rotational joints.
 */
class Launcher: public RFModule
{
    PolyDriver driver;

public:
    /**********************************************************/
    bool configure(ResourceFinder &rf)
    {
        Time::turboBoost();

        Property options;
        options.put("device","fakeyServer");
        options.put("local","fake_robot/fake_part");

        driver.open(options);
        return driver.isValid();
    }

    /**********************************************************/
    bool close()
    {
        if (driver.isValid())
            driver.close();

        return true;
    }

    /**********************************************************/
    double getPeriod()    { return 1.0;  }
    bool   updateModule() { return true; }
};


/**********************************************************/
int main()
{
    Network yarp;
    if (!yarp.checkNetwork())
    {
        cout<<"Error: yarp server does not seem available"<<endl;
        return -1;
    }

    // register here the new yarp devices
    // for dealing with the fake robot
    registerFakeMotorDevices();
    
    Launcher launcher;
    ResourceFinder rf;
    return launcher.runModule(rf);
}



