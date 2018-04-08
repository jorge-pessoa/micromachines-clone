//
//  Butter.cpp
//  CGProj
//

#include "Butter.h"

GLboolean Butter::checkOutOfBounds()
{
	GLdouble x = _position.getX(), z = _position.getZ();
	if (x > 75 || x < -75 || z > 50 || z < -50)
		return true;
	return false;
}

Butter::Butter()
{
	Butter::Butter(0, 0, 0);
}

Butter::Butter(GLdouble posx, GLdouble posy, GLdouble posz,
               GLdouble rotangle, GLdouble rotx, GLdouble roty, GLdouble rotz,
               GLdouble scalex, GLdouble scaley, GLdouble scalez)
:Obstacle(posx, posy, posz,
          rotangle, rotx, roty, rotz,
          scalex, scaley, scalez)
{
    _hascollider = true;
    _collisionradius *= 1;
    _friction = 0.000002;
    GLfloat amb[4] = {0.24f,0.1f,0.0f,1.0f},
            diff[4] = {1.0f,0.88f,0.44f,1.0f},
            spec[4] = {0.67f,0.6f,0.0f,1.0f},
            shine = 66.0f;
	setMaterial(amb, diff, spec, shine);
}

Butter::~Butter()
{
}

void Butter::render()
{
    glPushMatrix();
     glTranslated(0,-0.3f, 0);
     glScalef(1.5f, 1.5f, 1.5f);
    //Body
     glPushMatrix();
      glColor3f(1, 1, 0.67f);
      glScalef(1.1f,1.0f,1.5f);
      glutSolidCube(1);
     glPopMatrix();
	 //Droplet 1
     glPushMatrix();
      glTranslatef(0.65f, -0.25f, 0.2f);
      glutSolidSphere(0.25f, 16, 16);
    //Droplet 2
      glPushMatrix();
       glTranslatef(0.2f, -0.05f,0.25f);
       glutSolidSphere(0.2f, 16, 16);
    //Droplet3
       glPushMatrix();
        glTranslatef(0.125f, -0.025f,0.125f);
        glutSolidSphere(0.15f, 16, 16);
       glPopMatrix();

      glPopMatrix();

     glPopMatrix();
    
    glPopMatrix();
    
}


void Butter::update(GLdouble delta_t) 
{
	
	DynamicObject::update(delta_t);

	if (checkOutOfBounds() == true)
        DynamicObject::reset();
}

void Butter::collide(GameObject* obj) 
{
	obj->collideWith(this);
}

void Butter::collideWith(Car* car)
{
	if (fabs(_speed) < fabs(car->getSpeed()))
		_speed += fabs(car->getSpeed()*0.6);

    _direction.set(_position.getX() - car->_position.getX(),
				   _position.getY() - car->_position.getY(),
			       _position.getZ() - car->_position.getZ());
    _direction.normalize2D();
}

void Butter::reset(GLint lives)
{
    if(lives == 0){
        float posx =((std::rand() % (60 -0 + 1)))-30;
        float posy = -1;
        float posz = (std::rand() % (60-0 + 1))-30;
        float roty = 1;
        float angle = (std::rand() % (360-0 + 1));
        float scale = 0.8+(std::rand() % (20-0 + 1))/100.0f;
        
        Entity::setInitPosition(posx, posy, posz);
        GameObject::setInitRotation(angle, 0,roty,0);
        GameObject::setInitScale(scale, scale, scale);
        DynamicObject::reset();
    }
    else DynamicObject::reset();
}

