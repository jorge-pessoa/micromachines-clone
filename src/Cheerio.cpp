#include "Cheerio.h"

Cheerio::Cheerio()
{
    _hascollider = true;
    _collisionradius *= 0.45;
    _friction = 0.0000009;
}

Cheerio::Cheerio(GLdouble posx, GLdouble posy, GLdouble posz,
	GLdouble rotangle, GLdouble rotx, GLdouble roty, GLdouble rotz,
	GLdouble scalex, GLdouble scaley, GLdouble scalez)
	:Obstacle(posx, posy, posz,
		rotangle, rotx, roty, rotz,
		scalex, scaley, scalez)
{
	_hascollider = true;
	_collisionradius *= 0.45;
	_friction = 0.000009;
    GLfloat amb[4] = {0.11f,0.05f,0.0f,1.0f},
            diff[4] = {0.7f,0.65f,0.1f,1.0f},
            spec[4] = {0.0f,0.0f,0.0f,1.0f},
            shine=0.0f;
    setMaterial(amb, diff, spec, shine);
}


Cheerio::~Cheerio()
{
}

void Cheerio::render()
{
	glColor3f(1, 1, 0.4);
	glPushMatrix();
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glScalef(0.5, 0.5, 0.5);
	glutSolidTorus(0.4, 0.9, 4, 10);
	glPopMatrix();

}

void Cheerio::collide(GameObject* obj)
{
    obj->collideWith(this);
}

void Cheerio::collideWith(Car* car)
{
	if (fabs(_speed) < fabs(car->getSpeed()))
		_speed = fabs(car->getSpeed()*1);
    _direction.set(_position.getX() - car->_position.getX(), _position.getY() - car->_position.getY(),_position.getZ() - car->_position.getZ());
    _direction.normalize2D();
}

void Cheerio::collideWith(Cheerio* cheer)
{
    if (fabs(_speed) < fabs(cheer->getSpeed()))
        _speed = fabs(cheer->getSpeed()*0.6);
    else if (_speed == 0)
        _speed = 0.005;
    _direction.set(_position.getX() - cheer->_position.getX(), _position.getY() - cheer->_position.getY(),_position.getZ() - cheer->_position.getZ());
    _direction.normalize2D();
}

void Cheerio::collideWith(Butter* butter)
{
    if (fabs(_speed) < fabs(butter->getSpeed()))
        _speed = fabs(butter->getSpeed()*0.9);
    _direction.set(_position.getX() - butter->_position.getX(), _position.getY() - butter->_position.getY(),_position.getZ() - butter->_position.getZ());
    _direction.normalize2D();
}

void Cheerio::reset(GLint lives)
{
    DynamicObject::reset();
}
