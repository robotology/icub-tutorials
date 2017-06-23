/*
 * Copyright (C) 2012 Department of Robotics Brain and Cognitive Sciences, Istituto Italiano di Tecnologie
 * Author: Ugo Pattacini
 * CopyPolicy: Released under the terms of the GNU GPL v2.0.
 *
 */

// This code is just a white test to verify Ipopt installation

#include <cstdio>

#include <yarp/os/Time.h>
#include <yarp/sig/Vector.h>
#include <yarp/math/Math.h>

#include <iCub/iKin/iKinFwd.h>
#include <iCub/iKin/iKinIpOpt.h>

using namespace std;
using namespace yarp::sig;
using namespace yarp::math;
using namespace iCub::iKin;


int main()
{
    printf("Ipopt: testing correct installation...\n");

    iCubArm arm("right");
    iKinChain *chain=arm.asChain();

    iKinIpOptMin slv(*chain,IKINCTRL_POSE_XYZ,1e-3,1e-6,100);
    slv.setUserScaling(true,100.0,100.0,100.0);

    Vector xf(7,0.0);
    xf[0]=-0.3;
    xf[1]=+0.1;
    xf[2]=+0.1;

    slv.solve(chain->getAng(),xf);
    Vector xhat=chain->EndEffPose().subVector(0,2);
    xf=xf.subVector(0,2);
    double dist=norm(xf-xhat);
    bool ok=dist<1e-3;

    printf("target position = (%s) [m]\n",xf.toString(5,5).c_str());
    printf("solved position = (%s) [m]\n",xhat.toString(5,5).c_str());
    printf("distance to target = %g [m] ... ",dist);
    if (ok)
    {
        printf("test successful!\n");
        return 0;
    }
    else
    {
        printf("test failed!\n");
        return 1;
    }
}
