//
//  Orange.cpp
//  CGProj
//

#include "Orange.h"
#include "Logger.h"

/*FIXME glutTimerFunc */

GLboolean Orange::checkOutOfBounds()
{
	GLdouble x = getPosition()._x, z = getPosition()._z;
	if (x > 75 || x < -75 || z > 50 || z < -50)
		return true;
	return false;
}

void Orange::setOrangeRespawnCallback()
{
	glutTimerFunc(RESPAWN_TIME, Orange::orangeRespawnCallback, (int)(size_t)this);
}

void Orange::setOrangeSpeedCallback()
{
	glutTimerFunc(SPEED_UP_INTERVAL, Orange::orangeSpeedCallback, (int)(size_t)this);
}
	
Orange::Orange()
{
	Orange(0, 0, 0);
    _hascollider = true;
    _collisionradius *= 1.1;

}


Orange::Orange(GLdouble posx, GLdouble posy, GLdouble posz,
               GLdouble rotangle, GLdouble rotx, GLdouble roty, GLdouble rotz,
               GLdouble scalex, GLdouble scaley, GLdouble scalez)
:Obstacle(posx, posy, posz,
          rotangle, rotx, roty, rotz,
          scalex, scaley, scalez)
{

	_direction = Vector3(2*((double)(std::rand()) / RAND_MAX)-1, 0, 2 * ((double)(std::rand()) / RAND_MAX) - 1);
	_direction.normalize();
	_speed_modifier = 1;
	_speed = ((double)std::rand() / RAND_MAX)*0.010+0.005;
	_base_speed = _speed;
	setOrangeSpeedCallback();
    _hascollider = true;
    _collisionradius *= 1.1;
    GLfloat amb[4] = {0.24f,0.04f,0.0f,1.0f},
            diff[4] = {0.8f,0.46f,0.0f,1.0f},
            spec[4] = {0.0f,0.0f,0.0f,1.0f},
            shine = 0.0f;
    setMaterial(amb, diff, spec, shine);
	GLfloat ambpe[4] = { 0.08f,0.1f,0.0f,1.0f },
		diffpe[4] = { 0.05,0.025,0.0f,1.0f },
		specpe[4] = { 0.0f,0.0f,0.0f,1.0f },
		shinepe = 0;
    _materialpe.setValues(ambpe, diffpe, specpe, shinepe);
}


Orange::~Orange()
{
}

void Orange::render()
{
	glPushMatrix();
	 glTranslatef(0,0.2, 0);
     glScalef(2, 2, 2);
    
	 //corpo	
     glPushMatrix();
	  glColor3f(0.85f, 0.53f, 0.1f);
	  glutSolidSphere(1, 16, 16);
	 glPopMatrix();

	 //pe da laranja
	 glPushMatrix();
	  glColor3f(0.2f, 0.0f, 0.0f);
      _materialpe.applyMaterial();
	  glTranslatef(0.5f, 0.8f, 0.0f);
	  glRotatef(-30, 0, 0, 1);
	  glScalef(0.15, 0.7f, 0.15);
	  glutSolidCube(1);

	 glPopMatrix();
	 
	glPopMatrix();

}

void Orange::update(GLdouble delta_t)
{
	_speed = _speed_modifier*_base_speed;
	//setPosition(_position._x + _speedModifier*_speed*delta_t*_direction._x , _position._y,
		//_position._z + _speedModifier*_speed*delta_t*_direction._z);
	DynamicObject::move(delta_t);

	_rotation.set(_direction._z, _direction._y,- _direction._x);
	_rotangle += delta_t*50*_speed;

	if (checkOutOfBounds() == true) {
		_draw = false;
		setOrangeRespawnCallback();
		setPosition(0, 0, 0);
    }
}

void Orange::collide(GameObject* obj)
{
    obj->collideWith(this);
}

void Orange::respawn()
{
    setPosition((std::rand() % (60 - 0 + 1)) - 30, _position._y, (std::rand() % (60 - 0 + 1)) - 30);
	_direction = Vector3(2 * ((double)(std::rand()) / RAND_MAX) - 1, 0, 2 * ((double)(std::rand()) / RAND_MAX) - 1);
	_direction.normalize();
	_base_speed = ((double)std::rand() / RAND_MAX)*0.010 + 0.005;
	_draw = true;
}

void Orange::increaseSpeed()
{
	_speed_modifier++;
	Logger::printf("Speed increase!");
}

void Orange::resetSpeed() {	
	_speed_modifier = 1;
}
void Orange::orangeRespawnCallback(int obj)
{
    if(GameManager::getCurrentInstance()->isRunning()){
        Orange* o = (Orange*)obj;
        o->respawn();
    }
}

void Orange::orangeSpeedCallback(int obj)
{
    if(GameManager::getCurrentInstance()->isRunning()){
        Orange* o = (Orange*)obj;
        o->increaseSpeed();
        o->setOrangeSpeedCallback();
    }
}

void Orange::collideWith(Car* obj)
{
    GameManager::getCurrentInstance()->GGWP();
}

void Orange::reset()
{
    DynamicObject::reset();
	resetSpeed();
}

void Orange::reset(GLint lives)
{
    if(lives != 0){
        resetSpeed();
        Vector3 _pos = Vector3((std::rand() % (60 - 0 + 1)) - 30, _position._y, (std::rand() % (60 - 0 + 1)) - 30);
        Entity::setInitPosition(_pos._x, _pos._y, _pos._z);
        _direction = Vector3(2 * ((double)(std::rand()) / RAND_MAX) - 1, 0, 2 * ((double)(std::rand()) / RAND_MAX) - 1);
        _direction.normalize();
        _base_speed = ((double)std::rand() / RAND_MAX)*0.010 + 0.005;
        DynamicObject::reset();
    }
    else reset();
}

