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

#ifndef __FAKEMOTORDEVICECOMPONENTS_H__
#define __FAKEMOTORDEVICECOMPONENTS_H__

#include <yarp/os/all.h>
#include <yarp/dev/all.h>
#include <yarp/sig/all.h>

#include <iCub/ctrl/pids.h>

/**
 * This class implements the server part of the fake motor device driver.
 * Only the used interface methods are actually implemented.
 */
class fakeMotorDeviceServer : public yarp::dev::DeviceDriver,
                              public yarp::os::RateThread,
                              public yarp::os::PortReader,
                              public yarp::dev::IControlLimits,
                              public yarp::dev::IEncoders,
                              public yarp::dev::IVelocityControl
{
protected:
    yarp::os::BufferedPort<yarp::sig::Vector> statePort;
    yarp::os::BufferedPort<yarp::os::Bottle>  cmdPort;
    yarp::os::Port                            rpcPort;

    yarp::os::Semaphore mutex;

    iCub::ctrl::Integrator *motors;
    yarp::sig::Vector vel;
    bool configured;

    void run();
    /**
     * This method decodes the requests forwarded by the client and
     * responds with corresponding replies.
     */
    bool read(yarp::os::ConnectionReader &connection);

public:
    fakeMotorDeviceServer();
    bool open(yarp::os::Searchable &config);
    bool close();

    ////////////////////////////////////////////////////////////
    ////
    //// IControlLimits Interface
    ////
    /**********************************************************/
    bool getLimits(int axis, double *min, double *max);

    // not implemented
    /**********************************************************/
    bool setLimits(int,double,double)      { return false; }
    bool setVelLimits(int,double,double)   { return false; }
    bool getVelLimits(int,double*,double*) { return false; }

    ////////////////////////////////////////////////////////////
    ////
    //// IEncoders Interface
    ////
    /**********************************************************/
    bool getAxes(int *ax);

    // not implemented
    /**********************************************************/
    bool getEncoder(int,double*)             { return false; }
    bool getEncoders(double*)                { return false; }
    bool resetEncoder(int)                   { return false; }
    bool resetEncoders()                     { return false; }
    bool setEncoder(int,double)              { return false; }
    bool setEncoders(const double*)          { return false; } 
    bool getEncoderSpeed(int,double*)        { return false; }
    bool getEncoderSpeeds(double*)           { return false; }
    bool getEncoderAcceleration(int,double*) { return false; }
    bool getEncoderAccelerations(double*)    { return false; }

    ////////////////////////////////////////////////////////////
    ////
    //// IVelocityControl Interface
    ////
    /**********************************************************/
    bool velocityMove(int j, double sp);
    bool setRefAcceleration(int j, double acc);
    bool stop(int j);

    // not implemented
    /**********************************************************/
    bool velocityMove(const int,const int*,const double*)        { return false; }
    bool velocityMove(const double*)                             { return false; }
    bool setRefAccelerations(const int,const int*,const double*) { return false; }
    bool setRefAccelerations(const double*)                      { return false; }
    bool getRefAccelerations(const int,const int*,double*)       { return false; }
    bool getRefAcceleration(int,double*)                         { return false; }
    bool getRefAccelerations(double*)                            { return false; }
    bool stop(const int,const int*)                              { return false; }
    bool stop()                                                  { return false; }
};

/**
 * This class implements the client part of the fake motor device driver.
 * Only the used interface methods are actually implemented.
 */
class fakeMotorDeviceClient : public yarp::dev::DeviceDriver,
                              public yarp::dev::IControlLimits,
                              public yarp::dev::IEncoders,
                              public yarp::dev::IVelocityControl
{
protected:
    class StatePort : public yarp::os::BufferedPort<yarp::sig::Vector>
    {
        fakeMotorDeviceClient *owner;
        void onRead(yarp::sig::Vector &encs)
        {
            if (owner!=NULL)
            {
                owner->mutex.wait();
                owner->encs=encs;
                owner->mutex.post();
            }
        }
    public:
        StatePort() : owner(NULL)                   { useCallback();     }
        void setOwner(fakeMotorDeviceClient *owner) { this->owner=owner; }
    };

    StatePort                                statePort;
    yarp::os::BufferedPort<yarp::os::Bottle> cmdPort;
    yarp::os::RpcClient                      rpcPort;

    yarp::os::Semaphore mutex;

    yarp::sig::Vector encs;
    bool configured;

    friend class StatePort;

public:
    fakeMotorDeviceClient();
    bool open(yarp::os::Searchable &config);
    bool close();

    ////////////////////////////////////////////////////////////
    ////
    //// IControlLimits Interface
    ////
    /**********************************************************/
    bool getLimits(int axis, double *min, double *max);

    // not implemented
    /**********************************************************/
    bool setLimits(int,double,double)      { return false; }
    bool setVelLimits(int,double,double)   { return false; }
    bool getVelLimits(int,double*,double*) { return false; }

    ////////////////////////////////////////////////////////////
    ////
    //// IEncoders Interface
    ////
    /**********************************************************/
    bool getAxes(int *ax);
    bool getEncoders(double *encs);

    // not implemented
    /**********************************************************/
    bool getEncoder(int,double*)             { return false; }
    bool resetEncoder(int)                   { return false; }
    bool resetEncoders()                     { return false; }
    bool setEncoder(int,double)              { return false; }
    bool setEncoders(const double*)          { return false; }
    bool getEncoderSpeed(int,double*)        { return false; }
    bool getEncoderSpeeds(double*)           { return false; }
    bool getEncoderAcceleration(int,double*) { return false; }
    bool getEncoderAccelerations(double*)    { return false; }

    ////////////////////////////////////////////////////////////
    ////
    //// IVelocityControl Interface
    ////
    /**********************************************************/
    bool velocityMove(int j, double sp);
    bool setRefAcceleration(int j, double acc);
    bool stop(int j);

    // not implemented
    /**********************************************************/
    bool velocityMove(const int,const int*,const double*)        { return false; }
    bool velocityMove(const double*)                             { return false; }
    bool setRefAccelerations(const int,const int*,const double*) { return false; }
    bool setRefAccelerations(const double*)                      { return false; }
    bool getRefAccelerations(const int,const int*,double*)       { return false; }
    bool getRefAcceleration(int,double*)                         { return false; }
    bool getRefAccelerations(double*)                            { return false; }
    bool stop(const int,const int*)                              { return false; }
    bool stop()                                                  { return false; }
};

#endif


