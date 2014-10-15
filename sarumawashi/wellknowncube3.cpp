/**
 * wellknowncube3.cpp
 * 
 * Extended of Cube3. Implemented some well-known sequences.
 * 
 * @author kotarot
 * @version 0.1 2014-10-16
 */

#include <string>
#include "wellknowncube3.h"

namespace Sarumawashi {

/** Sets the cube to a well-known state given by name. */
void WellKnownCube3::wellknown(std::string name) {
    if (name == "superflip") {
        init("U R2 F B R B2 R U2 L B2 R U' D' R2 F R' L B2 U2 F2");
    }
}

} // end of namespace
