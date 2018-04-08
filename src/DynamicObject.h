//
//  DynamicObject.h
//  CGProj
//

#ifndef __CGProj__DynamicObject__
#define __CGProj__DynamicObject__

#include "Common.h"
#include "GameObject.h"

class DynamicObject : public GameObject{
protected:
	Vector3 _direction;

	GLdouble _accel,
            _speed,
            _friction;
	
public:
	DynamicObject();
    DynamicObject(GLdouble posx, GLdouble posy, GLdouble posz,
                                 GLdouble rotangle, GLdouble rotx, GLdouble roty, GLdouble rotz,
                                 GLdouble scalex, GLdouble scaley, GLdouble scalez);
	~DynamicObject();

	void update(GLdouble delta_t);
	void setSpeed(GLdouble speed);
    GLdouble getSpeed();
	void setDirection(GLdouble x, GLdouble y, GLdouble z);

	Vector3 getDirection();
	virtual void reset();
    virtual void reset(GLint lives);
	virtual void move(GLdouble delta_t);
};

#endif /* defined(__CGProj__DynamicObject__) */
