//
//  StaticObject.h
//  CGproj
//

#ifndef __CGProj__StaticObject__
#define __CGProj__StaticObject__

#include "Common.h"
#include "GameObject.h"

class StaticObject : public GameObject{
public:
    StaticObject();
    StaticObject(GLdouble posx, GLdouble posy, GLdouble posz,
                  GLdouble rotangle, GLdouble rotx, GLdouble roty, GLdouble rotz,
                  GLdouble scalex, GLdouble scaley, GLdouble scalez);
    ~StaticObject();
};

#endif /* defined(__CGProj__StaticObject__) */