/**
 * @ingroup icub_tutorials
 *
 * \defgroup icub_python_motor_interfaces Using motor interfaces with Python
 *
 * Shows how to control the robot using motor interfaces within Python.
 *
 * \author Lorenzo Natale
 * 
 * CopyPolicy: Released under the terms of GPL 2.0 or later
 */ 

import yarp;
yarp.Network.init();

# prepare a property object
props = yarp.Property()
props.put("device","remote_controlboard")
props.put("local","/client/right_arm")
props.put("remote","/icubSim/right_arm")

# create remote driver
armDriver = yarp.PolyDriver(props)

#query motor control interfaces
iPos = armDriver.viewIPositionControl()
iVel = armDriver.viewIVelocityControl()
iEnc = armDriver.viewIEncoders()

#retrieve number of joints
jnts=iPos.getAxes()

print 'Controlling', jnts, 'joints'

# read encoders
encs=yarp.Vector(jnts)
iEnc.getEncoders(encs.data())

## store as home position
home=yarp.Vector(jnts, encs.data())

#initialize a new tmp vector identical to encs
tmp=yarp.Vector(jnts)


tmp.set(0, tmp.get(0)+10)
tmp.set(1, tmp.get(1)+10)
tmp.set(2, tmp.get(2)+10)
tmp.set(3, tmp.get(3)+10)

iPos.positionMove(tmp.data())

## wait some time then go back to initial position
iPos.positionMove(encs.data())
