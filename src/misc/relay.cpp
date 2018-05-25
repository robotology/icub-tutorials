// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/**
 * @ingroup icub_tutorials
 *
 * \defgroup relay Relay
 *
 * This tutorials shows how to write a process
 * that reads data from a port and relays it to 
 * another one
 *
 * \author Lorenzo Natale
 */ 


#include <yarp/os/all.h>
#include <iostream>

using namespace std;
using namespace yarp::os;

int main(int argc, char **argv) {
    Network yarp;
    BufferedPort<Bottle> inPort;
    inPort.open("/relay/in");

    BufferedPort<Bottle> outPort;
    outPort.open("/relay/out");

    while (true) {
        cout << "waiting for input" << endl;
        Bottle *input = inPort.read();
        if (input!=NULL) 
        {
            Bottle& output = outPort.prepare();
            output=*input;
            
            cout << "writing " << output.toString() << endl;
            outPort.write();
        }
    }
    return 0;
}
