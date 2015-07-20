// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include <stdio.h>
#include <yarp/os/Network.h>
#include <yarp/dev/ControlBoardInterfaces.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/os/Time.h>
#include <yarp/sig/Vector.h>

#include <string>

using namespace yarp::dev;
using namespace yarp::sig;
using namespace yarp::os;

int main(int argc, char *argv[]) 
{
    Network yarp;

    Property params;
    params.fromCommand(argc, argv);

    if (!params.check("robot"))
    {
        fprintf(stderr, "Please specify the name of the robot\n");
        fprintf(stderr, "--robot name (e.g. icub)\n");
        return 1;
    }
    std::string robotName=params.find("robot").asString().c_str();
    std::string remotePorts="/";
    remotePorts+=robotName;
    remotePorts+="/right_arm";

    std::string localPorts="/test/client";

    Property options;
    options.put("device", "remote_controlboard");
    options.put("local", localPorts.c_str());   //local port names
    options.put("remote", remotePorts.c_str());         //where we connect to

    // create a device
    PolyDriver robotDevice(options);
    if (!robotDevice.isValid()) {
        printf("Device not available.  Here are the known devices:\n");
        printf("%s", Drivers::factory().toString().c_str());
        return 1;
    }

    IPositionControl *pos;
    IEncoders *encs;
    IControlMode2 *ictrl;
    IInteractionMode *iint;
    IImpedanceControl *iimp;
    ITorqueControl *itrq;


    bool ok;
    ok = robotDevice.view(pos);
    ok = ok && robotDevice.view(encs);
    ok = ok && robotDevice.view(ictrl);
    ok = ok && robotDevice.view(iimp);
    ok = ok && robotDevice.view(itrq);
    ok = ok && robotDevice.view(iint);

    if (!ok) {
        printf("Problems acquiring interfaces\n");
        return 1;
    }

    int nj=0;
    pos->getAxes(&nj);
    Vector encoders;
    Vector torques;
    Vector command;
    Vector tmp;
    int control_mode;
    yarp::dev::InteractionModeEnum interaction_mode;
    encoders.resize(nj);
    torques.resize(nj);
    tmp.resize(nj);
    command.resize(nj);
    
    int i;
    for (i = 0; i < nj; i++) {
         tmp[i] = 50.0;
    }
    pos->setRefAccelerations(tmp.data());

    for (i = 0; i < nj; i++) {
        tmp[i] = 10.0;
        pos->setRefSpeed(i, tmp[i]);
        //SET THE IMPEDANCE:
        //0.111 is the stiffness coefficient. units:   Nm/deg
        //0.014 is the damping coefficient. units:     Nm/(deg/s)
        //0 is the additional torque offset
        //WARNING: playing with this value may lead to undamped oscillatory behaviours.
        //when you raise the stiffness, you should increase the damping coefficient accordingly.
        iimp->setImpedance(i, 0.111, 0.014);
    }

    //pos->setRefSpeeds(tmp.data()))
    
    //fisrst zero all joints
    //
    command=0;
    //now set the shoulder to some value
    command[0]=-50;
    command[1]=20;
    command[2]=-10;
    command[3]=50;
    pos->positionMove(command.data());
    
    /*
    bool done=false;

    while(!done)
    {
        pos->checkMotionDone(&done);
        Time::delay(0.1);
    }
    */

    int times=0;
    while(true)
    {
        times++;
        if (times%2)
        {
             // set the elbow joint only in compliant mode
             ictrl->setPositionMode(3);
             iint->setInteractionMode(3,VOCAB_IM_COMPLIANT);
             // set new reference positions
             command[0]=-50;
             command[1]=20;
             command[2]=-10;
             command[3]=60;
        }
        else
        {
             // set the elbow joint in stiff mode
             ictrl->setPositionMode(3);
             iint->setInteractionMode(3,VOCAB_IM_STIFF);
             // set new reference positions
             command[0]=-20;
             command[1]=40;
             command[2]=-10;
             command[3]=30;
        }

        pos->positionMove(command.data());

        int count=50;
        while(count--)
            {
                Time::delay(0.1);
                encs->getEncoders(encoders.data());
                itrq->getTorques(torques.data());
                printf("Encoders: %+5.1lf %+5.1lf %+5.1lf %+5.1lf ", encoders[0], encoders[1], encoders[2], encoders[3]);
                printf("Torques:  %+5.1lfNm %+5.1lfNm %+5.1lfNm %+5.1lfNm ", torques[0], torques[1], torques[2], torques[3]);
                printf("Control:  ");
                for (i = 0; i < 4; i++)
                {
                    ictrl->getControlMode(i, &control_mode);
                    iint->getInteractionMode(i, &interaction_mode);
                    switch (control_mode)
                    {
                        case VOCAB_CM_IDLE:            printf("IDLE     ");        break;
                        case VOCAB_CM_POSITION:        printf("POSITION ");         break;
                        case VOCAB_CM_POSITION_DIRECT: printf("POSITION DIRECT ");  break;
                        case VOCAB_CM_VELOCITY:        printf("VELOCITY ");         break;
                        case VOCAB_CM_MIXED:           printf("MIXED POS/VEL");     break;
                        case VOCAB_CM_TORQUE:          printf("TORQUE   ");         break;
                        case VOCAB_CM_OPENLOOP:        printf("OPENLOOP ");         break;
                        default:
                        case VOCAB_CM_UNKNOWN:         printf("UNKNOWN  ");         break;
                    }
                }
                printf("\n");
                printf("Interaction:  ");
                for (i = 0; i < 4; i++)
                {
                    switch (interaction_mode)
                    {
                        case VOCAB_IM_COMPLIANT:       printf("(COMPLIANT MODE)");  break;
                        case VOCAB_IM_STIFF:           printf("(STIFF MODE)");      break;
                        default:
                        case VOCAB_CM_UNKNOWN:         printf("(UNKNOWN)  ");       break;
                    }
                }
                printf("\n");
            }
    }

    robotDevice.close();
    
    return 0;
}
