/**
 * @ingroup icub_tutorials
 *
 * \defgroup icub_iCubLimbsFwKin Example on Forward Kinematics of iCub limbs 
 *
 * A tutorial on how to use iKin library for forward kinematics of iCub limbs. 
 *
 * \author Ugo Pattacini
 * 
 * CopyPolicy: Released under the terms of GPL 2.0 or later
 */

#include <cstdlib>
#include <memory>
#include <cmath>
#include <string>
#include <iostream>
#include <algorithm>

#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include <iCub/iKin/iKinFwd.h>

using namespace std;
using namespace yarp::os;
using namespace yarp::sig;
using namespace iCub::iKin;

/****************************************************************/
int main(int argc, char *argv[])
{
    ResourceFinder rf;
    rf.configure(argc, argv);
    if (rf.check("help"))
    {
        cout << "Options:" << endl;
        cout << "--kinematics eye|arm|leg" << endl;
        cout << "--type left|right" << endl;
        cout << "--q \"(1.0 ... n)\"" << endl;
        return EXIT_SUCCESS;
    }

    string kinematics = rf.check("kinematics", Value("eye")).asString();
    string type = rf.check("type", Value("left")).asString();

    transform(kinematics.begin(), kinematics.end(), kinematics.begin(), ::tolower);
    transform(type.begin(), type.end(), type.begin(), ::tolower);

    if ((kinematics != "eye") && (kinematics != "arm") && (kinematics != "leg"))
    {
        cerr << "unrecognized kinematics \"" << kinematics << "\"" << endl;
        return EXIT_FAILURE;
    }

    if ((type != "left") && (type != "right"))
    {
        cerr << "unrecognized type \"" << type << "\"" << endl;
        return EXIT_FAILURE;
    }

    unique_ptr<iKinLimb> limb;
    if (kinematics == "eye")
    {
        limb = unique_ptr<iKinLimb>(new iCubEye(type));
    }
    else if (kinematics == "arm")
    {
        limb = unique_ptr<iKinLimb>(new iCubArm(type));
    }
    else
    {
        limb = unique_ptr<iKinLimb>(new iCubLeg(type));
    }

	iKinChain* chain = limb->asChain();
	chain->setAllConstraints(false);
    for (size_t i = 0; i < chain->getN(); i++)
    {
        chain->releaseLink(i);
    }

    Vector q(chain->getN(), 0.0);
    if (Bottle *b = rf.find("q").asList())
    {
        size_t len = std::min(q.length(), (size_t)b->size());
        for (size_t i = 0; i < len; i++)
        {
            q[i] = b->get(i).asDouble();
        }
    }

    Matrix H = chain->getH((M_PI / 180.0) * q);

    cout << "kinematics=\"" << kinematics << "/" << type << "\"" << endl;
    cout << "q=(" << ((180.0 / M_PI) * chain->getAng()).toString(5, 5) << ")" << endl;
    cout << "H=" << endl << H.toString(5, 5) << endl;
    cout << endl;

    return EXIT_SUCCESS;
}
