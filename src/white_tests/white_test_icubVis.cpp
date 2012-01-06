// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

// This code is just a white test to verify compilation against libraries (iCubVis)
// Copyright: Department of Robotics Brain and Cognitive Sciences, Istituto Italiano di Tecnologie 2011
// Author: Lorenzo Natale

#include <iCub/iCubVis/cht.h>
#include <yarp/os/ResourceFinder.h>
#include <iostream>

using namespace std;
int main(int argc, char *argv[]) 
{
    yarp::os::ResourceFinder config;
    config.configure("ICUB_ROOT", argc, argv);

    CircularHT ht;
    ht.alloc();
    ht.buildLookUpTable();

    ht.dealloc();
    return 0;
}
