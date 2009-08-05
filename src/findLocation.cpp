// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/**
 * @ingroup icub_tutorials
 *
 * \defgroup findLocation Find Location
 *
 * This tutorials shows how to do basic
 * image processsing from images coming from 
 * the robot or the simulator
 *
 * \author Paul Fitzpatrick
 */ 

#include <stdio.h>
// Get all OS and signal processing YARP classes
#include <yarp/os/all.h>
#include <yarp/sig/all.h>
using namespace yarp::os;
using namespace yarp::sig;

int main() {
  Network yarp; // set up yarp
  BufferedPort<ImageOf<PixelRgb> > imagePort;  // make a port for reading images
  BufferedPort<Vector> targetPort;

  imagePort.open("/paul/image/in");  // give the port a name
  targetPort.open("/paul/target/out");
  Network::connect("/icubSim/cam/left","/paul/image/in");

  while (1) { // repeat forever
    ImageOf<PixelRgb> *image = imagePort.read();  // read an image
    if (image!=NULL) { // check we actually got something
       printf("We got an image of size %dx%d\n", image->width(), image->height());
       double xMean = 0;
       double yMean = 0;
       int ct = 0;
       for (int x=0; x<image->width(); x++) {
         for (int y=0; y<image->height(); y++) {
           PixelRgb& pixel = image->pixel(x,y);
           // very simple test for blueishness
           // make sure blue level exceeds red and green by a factor of 2
           if (pixel.b>pixel.r*1.2+10 && pixel.b>pixel.g*1.2+10) {
            // there's a blueish pixel at (x,y)!
            // let's find the average location of these pixels
            xMean += x;
            yMean += y;
            ct++;
           }
         }
       }
       if (ct>0) {
         xMean /= ct;
         yMean /= ct;
       }
       if (ct>(image->width()/20)*(image->height()/20)) {
         printf("Best guess at blue target: %g %g\n", xMean, yMean);
         Vector& target = targetPort.prepare();
         target.resize(3);
         target[0] = xMean;
         target[1] = yMean;
         target[2] = 1;
         targetPort.write();
       } else {
         Vector& target = targetPort.prepare();
         target.resize(3);
         target[0] = 0;
         target[1] = 0;
         target[2] = 0;
         targetPort.write();
       }
    }
  }
  return 0;
}
