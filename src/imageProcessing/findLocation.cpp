// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/**
* @ingroup icub_tutorials
* \defgroup imageProc imageProc
*/

#include <stdio.h>
#include <yarp/os/Network.h>
#include <yarp/os/BufferedPort.h>
#include <yarp/sig/Image.h>
#include <yarp/os/Time.h>
#include <yarp/os/Property.h>

#include <string>

using namespace yarp::sig;
using namespace yarp::os;

int main(int argc, char *argv[]) 
{
    Network yarp;

    BufferedPort<ImageOf<PixelRgb> > imagePort;  // make a port for reading images
    BufferedPort<ImageOf<PixelRgb> > outPort;

    imagePort.open("/imageProc/image/in");  // give the port a name
    outPort.open("/imageProc/image/out");

    while (1) { // repeat forever
        ImageOf<PixelRgb> *image = imagePort.read();  // read an image
        ImageOf<PixelRgb> &outImage = outPort.prepare(); //get an output image

        outImage=*image;
    
        if (image!=NULL) { // check we actually got something
            //printf("We got an image of size %dx%d\n", image->width(), image->height());
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

                        outImage(x,y).r=255;
                    }
                }
            }
            if (ct>0) {
                xMean /= ct;
                yMean /= ct;
            }
            if (ct>(image->width()/20)*(image->height()/20)) {
                printf("Best guess at blue target: %g %g\n", xMean, yMean);
            }

            outPort.write();
        }
    }
    return 0;
}



