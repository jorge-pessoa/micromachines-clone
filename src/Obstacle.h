//
//  Obstacle.h
//  CGProj
//

#ifndef __CGProj__Obstacle__
#define __CGProj__Obstacle__

#include "Common.h"
#include "DynamicObject.h"

class Obstacle : public DynamicObject {
public:
	Obstacle();
    Obstacle(GLdouble posx, GLdouble posy, GLdouble posz,
             GLdouble rotangle=0, GLdouble rotx=0, GLdouble roty=0, GLdouble rotz=0,
             GLdouble scalex=1, GLdouble scaley=1, GLdouble scalez=1);
	~Obstacle();
};

#endif /* defined(__CGProj__Obstacle__) */
