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

/**********************************************************/
fakeMotorDeviceClient::fakeMotorDeviceClient()
{
    configured=false;
    statePort.setOwner(this);
}

/**********************************************************/
bool fakeMotorDeviceClient::open(Searchable &config)
{
    printf("Opening Fake Motor Device Client ...\n");

    string remote=config.check("remote",Value("/fakeyServer")).asString();
    string local=config.check("local",Value("/fakeyClient")).asString();

    statePort.open(local+"/state:i");
    cmdPort.open(local+"/cmd:o");
    rpcPort.open(local+"/rpc");
    
    bool ok=true;
    ok&=Network::connect(remote+"/state:o",statePort.getName(),"udp");
    ok&=Network::connect(cmdPort.getName(),remote+"/cmd:i","udp");
    ok&=Network::connect(rpcPort.getName(),remote+"/rpc","tcp");

    if (ok)
    {
        configured=true;

        printf("Fake Motor Device Client successfully open\n");
        return true;
    }
    else
    {
        statePort.close();
        cmdPort.close();
        rpcPort.close();

        printf("Fake Motor Device Client failed to open\n");
        return false;
    }
}

/**********************************************************/
bool fakeMotorDeviceClient::close()
{
    printf("Closing Fake Motor Device Client ...\n");

    statePort.interrupt();
    cmdPort.interrupt();
    rpcPort.interrupt();

    statePort.close();
    cmdPort.close();
    rpcPort.close();

    configured=false;

    printf("Fake Motor Device Client successfully closed\n");
    return true;
}

/**********************************************************/
bool fakeMotorDeviceClient::getLimits(int axis, double *min, double *max)
{
    if (!configured || (min==NULL) || (max==NULL))
        return false;

    Bottle cmd,reply;
    cmd.addVocab(Vocab::encode("lim"));
    cmd.addVocab(Vocab::encode("get"));
    cmd.addInt(axis);
    if (rpcPort.write(cmd,reply))
    {
        *min=reply.get(1).asDouble();
        *max=reply.get(2).asDouble();

        return true;
    }
    else
        return false;
}

/**********************************************************/
bool fakeMotorDeviceClient::getAxes(int *ax)
{
    if (!configured || (ax==NULL))
        return false;

    Bottle cmd,reply;
    cmd.addVocab(Vocab::encode("enc"));
    cmd.addVocab(Vocab::encode("axes"));
    if (rpcPort.write(cmd,reply))
    {
        *ax=reply.get(1).asInt();
        return true;
    }
    else
        return false;
}

/**********************************************************/
bool fakeMotorDeviceClient::getEncoders(double *encs)
{
    if (!configured || (encs==NULL))
        return false;

    lock_guard<mutex> lg(mtx);
    for (size_t i=0; i<this->encs.length(); i++)
        encs[i]=this->encs[i];

    return true;
}

/**********************************************************/
bool fakeMotorDeviceClient::velocityMove(int j, double sp)
{
    if (!configured)
        return false;

    Bottle cmd,reply;
    cmd.addVocab(Vocab::encode("vel"));
    cmd.addVocab(Vocab::encode("move"));
    cmd.addInt(j);
    cmd.addDouble(sp);
    if (rpcPort.write(cmd,reply))
        return true;
    else
        return false;
}

/**********************************************************/
bool fakeMotorDeviceClient::setRefAcceleration(int j, double acc)
{
    if (!configured)
        return false;

    Bottle cmd,reply;
    cmd.addVocab(Vocab::encode("vel"));
    cmd.addVocab(Vocab::encode("acc"));
    cmd.addInt(j);
    cmd.addDouble(acc);
    if (rpcPort.write(cmd,reply))
        return true;
    else
        return false;
}

/**********************************************************/
bool fakeMotorDeviceClient::stop(int j)
{
    if (!configured)
        return false;

    Bottle cmd,reply;
    cmd.addVocab(Vocab::encode("vel"));
    cmd.addVocab(Vocab::encode("stop"));
    cmd.addInt(j);
    if (rpcPort.write(cmd,reply))
        return true;
    else
        return false;
}



