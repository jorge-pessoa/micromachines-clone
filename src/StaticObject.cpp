//
//  StaticObject.cpp
//  CGproj
//

#include "StaticObject.h"
#include "Logger.h"

StaticObject::StaticObject()
{
}

StaticObject::StaticObject(GLdouble posx, GLdouble posy, GLdouble posz,
                             GLdouble rotangle, GLdouble rotx, GLdouble roty, GLdouble rotz,
                             GLdouble scalex, GLdouble scaley, GLdouble scalez)
:GameObject(posx, posy, posz,
            rotangle, rotx, roty, rotz,
            scalex, scaley, scalez)
{
}

StaticObject::~StaticObject()
{
}
