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

#include <private/fakeMotorDeviceComponents.h>

#include <string>
#include <stdio.h>

using namespace std;
using namespace yarp::os;
using namespace yarp::dev;
using namespace yarp::sig;
using namespace iCub::ctrl;

/**********************************************************/
fakeMotorDeviceServer::fakeMotorDeviceServer() : PeriodicThread(0.01)
{
    motors=NULL;
    configured=false;
}

/**********************************************************/
bool fakeMotorDeviceServer::open(Searchable &config)
{
    printf("Opening Fake Motor Device Server ...\n");

    string local=config.check("local",Value("/fakeyServer")).asString();
    int Ts=config.check("Ts",Value(10)).asInt();

    statePort.open(local+"/state:o");
    cmdPort.open(local+"/cmd:i");
    rpcPort.open(local+"/rpc");
    rpcPort.setReader(*this);
 
    // the part is composed of three rotational joints
    // whose bounds are given in degrees just below
    Matrix lim(3,2);
    lim(0,0)=-180.0; lim(0,1)=180.0;    // joint 0
    lim(1,0)=-90.0;  lim(1,1)=90.0;     // joint 1
    lim(2,0)=-45.0;  lim(2,1)=45.0;     // joint 2

    Vector q0;
    for (int i=0; i<lim.rows(); i++)
        q0.push_back((lim(i,0)+lim(i,1))/2.0);

    // the motors themselves are represented
    // by pure integrators that give back joints
    // positions when fed with joints velocities
    motors=new Integrator((double)Ts/1000.0,q0,lim);
    vel.resize(motors->get().length(),0.0);        

    setPeriod((double)Ts/1000.0);
    start();

    configured=true;

    printf("Fake Motor Device Server successfully open\n");
    return true;
}

/**********************************************************/
bool fakeMotorDeviceServer::close()
{
    printf("Closing Fake Motor Device Server ...\n");

    if (isRunning())
        stop();

    mutex.wait();
    PeriodicThread::stop();
    mutex.post();

    statePort.interrupt();
    cmdPort.interrupt();
    rpcPort.interrupt();

    statePort.close();
    cmdPort.close();
    rpcPort.close();

    if (motors!=NULL)
    {
        delete motors;
        motors=NULL;
    }

    configured=false;

    printf("Fake Motor Device Server successfully closed\n");
    return true;
}

/**********************************************************/
void fakeMotorDeviceServer::run()
{
    mutex.wait();

    if (Bottle *cmd=cmdPort.read(false))
    {
        if ((size_t)cmd->size()>=vel.length())
            for (size_t i=0; i<vel.length(); i++)
                vel[i]=cmd->get(i).asDouble();
    }

    statePort.prepare()=motors->integrate(vel);
    statePort.write();

    mutex.post();
}

/**********************************************************/
bool fakeMotorDeviceServer::read(ConnectionReader &connection)
{        
    Bottle cmd,reply;
    cmd.read(connection);
    
    mutex.wait();

    int codeIF=cmd.get(0).asVocab();
    int codeMethod=cmd.get(1).asVocab();

    if (codeIF==Vocab::encode("lim"))
    {
        if (codeMethod==Vocab::encode("get"))
        {
            int axis=cmd.get(2).asInt();
            double min,max;
            if (getLimits(axis,&min,&max))
            {
                reply.addVocab(Vocab::encode("ack"));
                reply.addDouble(min);
                reply.addDouble(max);
            }
        }
    }
    else if (codeIF==Vocab::encode("enc"))
    {
        if (codeMethod==Vocab::encode("axes"))
        {
            int ax;
            if (getAxes(&ax))
            {
                reply.addVocab(Vocab::encode("ack"));
                reply.addInt(ax);
            }
        }
    }
    else if (codeIF==Vocab::encode("vel"))
    {
        if (codeMethod==Vocab::encode("move"))
        {
            int axis=cmd.get(2).asInt();
            double sp=cmd.get(3).asDouble();
            if (velocityMove(axis,sp))
                reply.addVocab(Vocab::encode("ack"));
        }
        else if (codeMethod==Vocab::encode("acc"))
        {
            int axis=cmd.get(2).asInt();
            double acc=cmd.get(3).asDouble();
            if (setRefAcceleration(axis,acc))
                reply.addVocab(Vocab::encode("ack"));
        }
        else if (codeMethod==Vocab::encode("stop"))
        {
            int axis=cmd.get(2).asInt();
            if (stop(axis))
                reply.addVocab(Vocab::encode("ack"));
        }
    }

    if (reply.size()==0)
        reply.addVocab(Vocab::encode("nack"));

    mutex.post();

    if (ConnectionWriter *returnToSender=connection.getWriter())
        reply.write(*returnToSender);

    return true;
}

/**********************************************************/
bool fakeMotorDeviceServer::getLimits(int axis, double *min, double *max)
{
    if (!configured)
        return false;

    if ((axis<(int)motors->get().length()) && (min!=NULL) && (max!=NULL))
    {
        Matrix lim=motors->getLim();
        *min=lim(axis,0); *max=lim(axis,1);
        return true;
    }
    else
        return false;
}

/**********************************************************/
bool fakeMotorDeviceServer::getAxes(int *ax)
{
    if (!configured)
        return false;

    if (ax!=NULL)
    {
        *ax=(int)motors->get().length();
        return true;
    }
    else
        return false;
}

/**********************************************************/
bool fakeMotorDeviceServer::velocityMove(int j, double sp)
{
    if (!configured)
        return false;

    if ((size_t)j<vel.length())
    {
        vel[j]=sp;
        return true;
    }
    else
        return false;
}

/**********************************************************/
bool fakeMotorDeviceServer::setRefAcceleration(int j, double acc)
{
    if (configured && ((size_t)j<vel.length()))
        return true;
    else
        return false;
}

/**********************************************************/
bool fakeMotorDeviceServer::stop(int j)
{
    return velocityMove(j,0.0);
}



