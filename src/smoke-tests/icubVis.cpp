// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

// This code is just a white test to verify compilation against libraries (iCubVis)
// Copyright: Department of Robotics Brain and Cognitive Sciences, Istituto Italiano di Tecnologie 2011
// Author: Lorenzo Natale

#include <iCub/iCubVis/cht.h>
#include <iostream>

using namespace std;
int main(int argc, char *argv[]) 
{
    printf("iCubVis: testing library linking...");
    CircularHT ht;
	ht.setParameters(1, 255, 1, 320, 240);
		
	printf("success!\n");
    return 0;
}
