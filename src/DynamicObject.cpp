//
//  DynamicObject.cpp
//  CGProj
//

#include "DynamicObject.h"
#include "Logger.h"

DynamicObject::DynamicObject()
{
    _speed = 0;
}
DynamicObject::DynamicObject(GLdouble posx, GLdouble posy, GLdouble posz,
                   GLdouble rotangle, GLdouble rotx, GLdouble roty, GLdouble rotz,
                   GLdouble scalex, GLdouble scaley, GLdouble scalez)
:GameObject(posx, posy, posz,
               rotangle, rotx, roty, rotz,
               scalex, scaley, scalez)
{
    _direction.set(cos((rotangle*3.14)/180),0, sin((rotangle*3.14)/180));
    _speed = 0;
}

DynamicObject::~DynamicObject()
{
}

void DynamicObject::update(GLdouble delta_t)
{
	if (_speed > 0) {
		move(delta_t);
		_speed -= _friction*delta_t;
		if (_speed < 0) _speed = 0;
	}
}

void DynamicObject::setSpeed(GLdouble speed)
{
	_speed = speed;
}

GLdouble DynamicObject::getSpeed()
{
    return _speed;
}

void DynamicObject::setDirection(GLdouble x, GLdouble y, GLdouble z)
{
	_direction.set(x, y, z);
}

Vector3 DynamicObject::getDirection()
{
	return _direction;
}
void DynamicObject::reset()
{
	_speed = 0;
	GameObject::reset();
}

void DynamicObject::reset(GLint lives)
{
    _speed = 0;
}

void DynamicObject::move(GLdouble delta_t)
{
	_position.set(_position.getX() + _direction.getX()*_speed*delta_t, 
				  _position.getY(), 
				  _position.getZ() + _direction.getZ()*_speed*delta_t);

}


