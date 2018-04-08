//
//  Obstacle.cpp
//  CGProj
//

#include "Obstacle.h"

Obstacle::Obstacle()
{
}

Obstacle::Obstacle(GLdouble posx, GLdouble posy, GLdouble posz,
                   GLdouble rotangle, GLdouble rotx, GLdouble roty, GLdouble rotz,
                   GLdouble scalex, GLdouble scaley, GLdouble scalez)
:DynamicObject(posx, posy, posz,
               rotangle, rotx, roty, rotz,
               scalex, scaley, scalez)
{
}

Obstacle::~Obstacle()
{
}
