//
//  Car.cpp
//  CGProj
//

#include "Car.h"
#include "Logger.h"

GLboolean Car::checkOutOfBounds()
{
	GLdouble x = _position.getX(), z = _position.getZ();
	if (x > 75 || x < -75 || z > 50 || z < -50)
		return true;
	return false;
}

Car::Car()
{
    _position.set(0,0,0);
    init();
}

Car::Car(GLdouble posx, GLdouble posy, GLdouble posz,
               GLdouble rotangle, GLdouble rotx, GLdouble roty, GLdouble rotz,
               GLdouble scalex, GLdouble scaley, GLdouble scalez)
:DynamicObject(posx, posy, posz,
          rotangle, rotx, roty, rotz,
          scalex, scaley, scalez)
{
    
    GLfloat amb[4] = {0.0f,0.0f,0.0f,1.0f},
    diff[4] = {0.83f,0.48f,0.0f,1.0f},
    spec[4] = {0.0f,0.0f,0.0f,1.0f},
    shine = 40.0f;
    setMaterial(amb, diff, spec, shine);
    GLfloat ambmotor[4] = {0.0f,0.0f,0.0f,1.0f},
    diffmotor[4] = {0.8f,0.78f,0.78f,1.0f},
    specmotor[4] = {0.0f,0.0f,0.0f,1.0f},
    shinemotor = 20.0f;
    _materialmotor.setValues(ambmotor, diffmotor, specmotor, shinemotor);
    GLfloat ambrodas[4] = {0.0f,0.0f,0.0f,1.0f},
    diffrodas[4] = {0.05f,0.05f,0.05f,1.0f},
    specrodas[4] = {0.0f,0.0f,0.0f,1.0f},
    shinerodas = 10.0f;
    _materialrodas.setValues(ambrodas, diffrodas, specrodas, shinerodas);
    GLfloat ambcap[4] = {0.0215f,0.0f,0.0215f,1.0f},
    diffcap[4] = {0.49f,0.0f,0.0f,1.0f},
    speccap[4] = {0.0f,0.0f,0.0f,1.0f},
    shinecap = 20.0f;
    _materialcapota.setValues(ambcap, diffcap, speccap, shinecap);
    init();

	_light_l = GameManager::getCurrentInstance()->createSpotLight();
	_light_l->setPosition(-1.3, 2, 0);
	_light_l->setDirection(1, 0, 0);
	_light_l->setCutoff(90.0);
	_light_l->setExponent(18);
	_light_l->setDiffuse(1.0, 1.0, 1.0, 1.0);
	_light_l->setAmbient(0.0, 0.0, 0.0, 1.0);
	_light_l->setSpecular(0.3, 0.3, 0.3, 1.0);
	_light_l->setAttenuation(0.000, 0.0003, 0.0018);
	_light_l->setState(false);
}


Car::~Car()
{
}

void Car::init()
{
    /*FIXME direction should be set with rotation*/
    _direction.set(1,0,0);
	_moving.set(1, 0, 0);
    _accel = 0.000012;
    _break_accel = 0.000035;
    _speed = 0;
    _turnSpeed = 0.035;
	_max_turn_speed = 2;
    _friction = 0.000006;
    _angle = 0;
    _max_speed = 0.035;
    _max_reverse_speed = 0.008;
    _up_pressed = false;
    _down_pressed = false;
    _left_pressed = false;
    _right_pressed = false;
	_turn_velocity = 0;
	_turn_friction = 0.93;
	_facing_angle = 0;
	_max_facing_angle = 1;
	_drift = 0.98;
    _hascollider = true;
    _collisionradius *= 1.7;
    _front_wheel_rotation = 0;
    _drift = 0;
	_spot_on = false;
}

void Car::render()
{
	glPushMatrix();
	glRotatef(_angle, 0, 1, 0);
	_light_l->draw();
	glScalef(0.2, 0.2, 0.2);

	_materialcapota.applyMaterial();
	glPushMatrix();
	glScalef(4, 4, 4);
	glColor3f(1, 0, 0);
	//1
	glBegin(GL_TRIANGLES);
	glNormal3f(0, -1, 0);
	glVertex3f(2.1, -0.2, 1);
	glNormal3f(0, -1, 0);
	glVertex3f(-2.1, -0.2, 1);
	glNormal3f(0, -1, 0);
	glVertex3f(-2.1, -0.2, -1);
	glEnd();
	//2
	glBegin(GL_TRIANGLES);
	glNormal3f(0.2, 0.98, 0);
	glVertex3f(-2.1, 1.1, -1);
	glNormal3f(0.2, 0.98, 0);
	glVertex3f(-2.1, 1.1, 1);
	glNormal3f(0.2, 0.98, 0);
	glVertex3f(2.1, 0.2, 1);
	glEnd();
	//3
	glBegin(GL_TRIANGLES);
	glNormal3f(1, 0, 0);
	glVertex3f(2.1, 0.2, -1);
	glNormal3f(1, 0, 0);
	glVertex3f(2.1, 0.2, 1);
	glNormal3f(1, 0, 0);
	glVertex3f(2.1, -0.2, 1);
	glEnd();
	//4
	glBegin(GL_TRIANGLES);
	glNormal3f(0, 0, 1);
	glVertex3f(2.1, 0.2, 1);
	glNormal3f(0, 0, 1);
	glVertex3f(-2.1, 1.1, 1);
	glNormal3f(0, 0, 1);
	glVertex3f(-2.1, -0.2, 1);
	glEnd();
	//5
	glBegin(GL_TRIANGLES);
	glNormal3f(-1, 0, 0);
	glVertex3f(-2.1, 1.1, 1);
	glNormal3f(-1, 0, 0);
	glVertex3f(-2.1, 1.1, -1);
	glNormal3f(-1, 0, 0);
	glVertex3f(-2.1, -0.2, -1);
	glEnd();
	//6
	glBegin(GL_TRIANGLES);
	glNormal3f(0, 0, -1);
	glVertex3f(2.1, 0.2, -1);
	glNormal3f(0, 0, -1);
	glVertex3f(2.1, -0.2, -1);
	glNormal3f(0, 0, -1);
	glVertex3f(-2.1, -0.2, -1);
	glEnd();
	//7
	glBegin(GL_TRIANGLES);
	glNormal3f(0, 0, -1);
	glVertex3f(2.1, -0.2, -1);
	glNormal3f(0, 0, -1);
	glVertex3f(2.1, -0.2, -1);
	glNormal3f(0, 0, -1);
	glVertex3f(-2.1, -0.2, -1);
	glEnd();
	//8
	glBegin(GL_TRIANGLES);
	glNormal3f(0.2, 0.98, 0);
	glVertex3f(2.1, 0.2, -1);
	glNormal3f(0.2, 0.98, 0);
	glVertex3f(-2.1, 1.1, -1);
	glNormal3f(0.2, 0.98, 0);
	glVertex3f(2.1, 0.2, 1);
	glEnd();
	//9
	glBegin(GL_TRIANGLES);
	glNormal3f(1, 0, 0);
	glVertex3f(2.1, -0.2, -1);
	glNormal3f(1, 0, 0);
	glVertex3f(2.1, 0.2, -1);
	glNormal3f(1, 0, 0);
	glVertex3f(2.1, -0.2, 1);
	glEnd();
	//10
	glBegin(GL_TRIANGLES);
	glNormal3f(0, 1, 0);
	glVertex3f(2.1, -0.2, 1);
	glNormal3f(0, 1, 0);
	glVertex3f(2.1, 0.2, 1);
	glNormal3f(0, 1, 0);
	glVertex3f(-2.1, -0.2, 1);
	glEnd();
	//11
	glBegin(GL_TRIANGLES);
	glNormal3f(-1, 0, 0);
	glVertex3f(-2.1, -0.2, 1);
	glNormal3f(-1, 0, 0);
	glVertex3f(-2.1, 1.1, 1);
	glNormal3f(-1, 0, 0);
	glVertex3f(-2.1, -0.2, -1);
	glEnd();
	//12
	glBegin(GL_TRIANGLES);
	glNormal3f(0, 0, -1);
	glVertex3f(-2.1, 1.1, -1);
	glNormal3f(0, 0, -1);
	glVertex3f(2.1, 0.2, -1);
	glNormal3f(0, 0, -1);
	glVertex3f(-2.1, -0.2, -1);
	glEnd();

	glPopMatrix();

	_materialmotor.applyMaterial();
	glPushMatrix();
	glTranslatef(0, 4, 0);
	glRotatef(-90, 0, 1, 0);
	glScalef(2, 2, 2);
	glColor3f(1, 1, 1);
	//1
	glBegin(GL_TRIANGLES);
	glNormal3f(0, -1, 0);
	glVertex3f(1, -0.6, 1);
	glNormal3f(0, -1, 0);
	glVertex3f(-1, -0.6, 1);
	glNormal3f(0, -1, 0);
	glVertex3f(-1, -0.6, -1);
	glEnd();
	//2
	glBegin(GL_TRIANGLES);
	glNormal3f(0, -1, 0);
	glVertex3f(1, -0.6, -1);
	glNormal3f(0, -1, 0);
	glVertex3f(1, -0.6, 1);
	glNormal3f(0, -1, 0);
	glVertex3f(-1, -0.6, -1);
	glEnd();
	//3
	glBegin(GL_TRIANGLES);
	glNormal3f(0, 0.96, -0.26);
	glVertex3f(-1, 0.4, 0.2);
	glNormal3f(0, 0.96, -0.26);
	glVertex3f(1, 0.6, 1);
	glNormal3f(0, 0.96, -0.26);
	glVertex3f(1, 0.4, 0.2);
	glEnd();
	//4
	glBegin(GL_TRIANGLES);
	glNormal3f(0, 0.96, -0.26);
	glVertex3f(-1, 0.4, 0.2);
	glNormal3f(0, 0.96, -0.26);
	glVertex3f(-1, 0.6, 1);
	glNormal3f(0, 0.96, -0.26);
	glVertex3f(1, 0.6, 1);
	glEnd();
	//5
	glBegin(GL_TRIANGLES);
	glNormal3f(1, 0, 0);
	glVertex3f(1, 0.4, 0.2);
	glNormal3f(1, 0, 0);
	glVertex3f(1, 0.6, 1);
	glNormal3f(1, 0, 0);
	glVertex3f(1, -0.6, 1);
	glEnd();
	//6
	glBegin(GL_TRIANGLES);
	glNormal3f(1, 0, 0);
	glVertex3f(1, -0.6, 1);
	glNormal3f(1, 0, 0);
	glVertex3f(1, -0.6, -1);
	glNormal3f(1, 0, 0);
	glVertex3f(1, -0.12, -0.6);
	glEnd();
	//7
	glBegin(GL_TRIANGLES);
	glNormal3f(1, 0, 0);
	glVertex3f(1, -0.12, -0.6);
	glNormal3f(1, 0, 0);
	glVertex3f(1, 0.4, 0.2);
	glNormal3f(1, 0, 0);
	glVertex3f(1, -0.6, 1);
	glEnd();
	//8
	glBegin(GL_TRIANGLES);
	glNormal3f(0, 0, 1);
	glVertex3f(1, 0.6, 1);
	glNormal3f(0, 0, 1);
	glVertex3f(-1, 0.6, 1);
	glNormal3f(0, 0, 1);
	glVertex3f(-1, -0.6, 1);
	glEnd();
	//9
	glBegin(GL_TRIANGLES);
	glNormal3f(0, 0, 1);
	glVertex3f(1, -0.6, 1);
	glNormal3f(0, 0, 1);
	glVertex3f(1, 0.6, 1);
	glNormal3f(0, 0, 1);
	glVertex3f(-1, -0.6, 1);
	glEnd();
	//10
	glBegin(GL_TRIANGLES);
	glNormal3f(-1, 0, 0);
	glVertex3f(-1, 0.4, 0.2);
	glNormal3f(-1, 0, 0);
	glVertex3f(-1, -0.12, -0.6);
	glNormal3f(-1, 0, 0);
	glVertex3f(-1, -0.6, 1);
	glEnd();
	//11
	glBegin(GL_TRIANGLES);
	glNormal3f(-1, 0, 0);
	glVertex3f(-1, -0.6, -1);
	glNormal3f(-1, 0, 0);
	glVertex3f(-1, -0.6, 1);
	glNormal3f(-1, 0, 0);
	glVertex3f(-1, -0.12, -0.6);
	glEnd();
	//12
	glBegin(GL_TRIANGLES);
	glNormal3f(-1, 0, 0);
	glVertex3f(-1, 0.6, 1);
	glNormal3f(-1, 0, 0);
	glVertex3f(-1, 0.4, 0.2);
	glNormal3f(-1, 0, 0);
	glVertex3f(-1, -0.6, 1);
	glEnd();
	//13
	glBegin(GL_TRIANGLES);
	glNormal3f(0, 0.6, -0.8);
	glVertex3f(1, -0.6, -1);
	glNormal3f(0, 0.6, -0.8);
	glVertex3f(-1, -0.6, -1);
	glNormal3f(0, 0.6, -0.8);
	glVertex3f(-1, -0.12, -0.6);
	glEnd();
	//14
	glBegin(GL_TRIANGLES);
	glNormal3f(0, 0.6, -0.8);
	glVertex3f(1, -0.12, -0.6);
	glNormal3f(0, 0.6, -0.8);
	glVertex3f(1, -0.6, -1);
	glNormal3f(0, 0.6, -0.8);
	glVertex3f(-1, -0.12, -0.6);
	glEnd();
	//15
	glBegin(GL_TRIANGLES);
	glNormal3f(0, 0.85, -0.53);
	glVertex3f(1, 0.4, 0.2);
	glNormal3f(0, 0.85, -0.53);
	glVertex3f(1, -0.12, -0.6);
	glNormal3f(0, 0.85, -0.53);
	glVertex3f(-1, -0.12, -0.6);
	glEnd();
	//16
	glBegin(GL_TRIANGLES);
	glNormal3f(0, 0.85, -0.53);
	glVertex3f(1, 0.4, 0.2);
	glNormal3f(0, 0.85, -0.53);
	glVertex3f(-1, -0.12, -0.6);
	glNormal3f(0, 0.85, -0.53);
	glVertex3f(-1, 0.4, 0.2);
	glEnd();

	glPopMatrix();

	_materialrodas.applyMaterial();
	glColor3f(0, 0, 0);
	for (int k = 0; k < 4; k++) {
		glPushMatrix();
		if (k == 0) {
			glTranslatef(5, -1.5, -5);
			glScalef(3, 3, 3);
		}
		if (k == 1) {
			glTranslatef(5, -1.5, 5);
			glScalef(3, 3, 3);
		}
		if (k == 2) {
			glTranslatef(-5, -1.5, -5);
			glScalef(4, 4, 4);
		}
		if (k == 3) {
			glTranslatef(-5, -1.5, 5);
			glScalef(4, 4, 4);
		}

		//1
		glBegin(GL_TRIANGLES);
		glNormal3f(0, 1, 0);
		glVertex3f(0, 1, 0.4);
		glNormal3f(0.865, 0.501, 0);
		glVertex3f(0.87, 0.5, 0.4);
		glNormal3f(0.865, 0.501, 0);
		glVertex3f(0.87, 0.5, -0.4);
		glEnd();
		//2
		glBegin(GL_TRIANGLES);
		glNormal3f(0, 1, 0);
		glVertex3f(0, 1, -0.4);
		glNormal3f(0, 1, 0);
		glVertex3f(0, 1, 0.4);
		glNormal3f(0.865, 0.501, 0);
		glVertex3f(0.87, 0.5, -0.4);
		glEnd();
		//3
		glBegin(GL_TRIANGLES);
		glNormal3f(0.865, 0.501, 0);
		glVertex3f(0.87, 0.5, -0.4);
		glNormal3f(0.865, 0.501, 0);
		glVertex3f(0.87, 0.5, 0.4);
		glNormal3f(0.865, -0.501, 0);
		glVertex3f(0.87, -0.5, 0.4);
		glEnd();
		//4
		glBegin(GL_TRIANGLES);
		glNormal3f(0.865, -0.501, 0);
		glVertex3f(0.87, -0.5, -0.4);
		glNormal3f(0.865, 0.501, 0);
		glVertex3f(0.87, 0.5, -0.4);
		glNormal3f(0.865, -0.501, 0);
		glVertex3f(0.87, -0.5, 0.4);
		glEnd();
		//5
		glBegin(GL_TRIANGLES);
		glNormal3f(0.865, -0.501, 0);
		glVertex3f(0.87, -0.5, -0.4);
		glNormal3f(0.865, -0.501, 0);
		glVertex3f(0.87, -0.5, 0.4);
		glNormal3f(0, -1, 0);
		glVertex3f(0, -1, -0.4);
		glEnd();
		//6
		glBegin(GL_TRIANGLES);
		glNormal3f(0, -1, 0);
		glVertex3f(0.87, -0.5, 0.4);
		glNormal3f(-0.865, -0.501, 0);
		glVertex3f(0, -1, 0.4);
		glNormal3f(-0.865, -0.501, 0);
		glVertex3f(0, -1, -0.4);
		glEnd();
		//7
		glBegin(GL_TRIANGLES);
		glNormal3f(0, -1, 0);
		glVertex3f(0, -1, 0.4);
		glNormal3f(-0.865, -0.501, 0);
		glVertex3f(-0.87, -0.5, 0.4);
		glNormal3f(-0.865, -0.501, 0);
		glVertex3f(-0.87, -0.5, -0.4);
		glEnd();
		//8
		glBegin(GL_TRIANGLES);
		glNormal3f(0, -1, 0);
		glVertex3f(0, -1, -0.4);
		glNormal3f(0, -1, 0);
		glVertex3f(0, -1, 0.4);
		glNormal3f(-0.865, -0.501, 0);
		glVertex3f(-0.87, -0.5, -0.4);
		glEnd();
		//9
		glBegin(GL_TRIANGLES);
		glNormal3f(0, 0, 1);
		glVertex3f(0, 1, 0.4);
		glNormal3f(0, 0, 1);
		glVertex3f(-0.87, -0.5, 0.4);
		glNormal3f(0, 0, 1);
		glVertex3f(0.87, -0.5, 0.4);
		glEnd();
		//10
		glBegin(GL_TRIANGLES);
		glNormal3f(0, 0, 1);
		glVertex3f(0.87, -0.5, 0.4);
		glNormal3f(0, 0, 1);
		glVertex3f(0.87, 0.5, 0.4);
		glNormal3f(0, 0, 1);
		glVertex3f(0, 1, 0.4);
		glEnd();
		//11
		glBegin(GL_TRIANGLES);
		glNormal3f(0, 0, 1);
		glVertex3f(0, 1, 0.4);
		glNormal3f(0, 0, 1);
		glVertex3f(-0.87, 0.5, 0.4);
		glNormal3f(0, 0, 1);
		glVertex3f(-0.87, -0.5, 0.4);
		glEnd();
		//12
		glBegin(GL_TRIANGLES);
		glNormal3f(0, 0, 1);
		glVertex3f(-0.87, -0.5, 0.4);
		glNormal3f(0, 0, 1);
		glVertex3f(0, -1, 0.4);
		glNormal3f(0, 0, 1);
		glVertex3f(0.87, -0.5, 0.4);
		glEnd();
		//13
		glBegin(GL_TRIANGLES);
		glNormal3f(-0.865, 0.501, 0);
		glVertex3f(-0.87, 0.5, 0.4);
		glNormal3f(0, 1, 0);
		glVertex3f(0, 1, 0.4);
		glNormal3f(0, 1, 0);
		glVertex3f(0, 1, -0.4);
		glEnd();
		//14
		glBegin(GL_TRIANGLES);
		glNormal3f(-0.865, 0.501, 0);
		glVertex3f(-0.87, 0.5, -0.4);
		glNormal3f(-0.865, 0.501, 0);
		glVertex3f(-0.87, 0.5, 0.4);
		glNormal3f(0, 1, 0);
		glVertex3f(0, 1, -0.4);
		glEnd();
		//15
		glBegin(GL_TRIANGLES);
		glNormal3f(-0.865, -0.501, 0);
		glVertex3f(-0.87, -0.5, 0.4);
		glNormal3f(-0.865, 0.501, 0);
		glVertex3f(-0.87, 0.5, 0.4);
		glNormal3f(-0.865, 0.501, 0);
		glVertex3f(-0.87, 0.5, -0.4);
		glEnd();
		//16
		glBegin(GL_TRIANGLES);
		glNormal3f(-0.865, -0.501, 0);
		glVertex3f(-0.87, -0.5, -0.4);
		glNormal3f(-0.865, -0.501, 0);
		glVertex3f(-0.87, -0.5, 0.4);
		glNormal3f(-0.865, 0.501, 0);
		glVertex3f(-0.87, 0.5, -0.4);
		glEnd();
		//17
		glBegin(GL_TRIANGLES);
		glNormal3f(0, 0, -1);
		glVertex3f(0.87, 0.5, -0.4);
		glNormal3f(0, 0, -1);
		glVertex3f(0, -1, -0.4);
		glNormal3f(0, 0, -1);
		glVertex3f(-0.87, 0.5, -0.4);
		glEnd();
		//18
		glBegin(GL_TRIANGLES);
		glNormal3f(0, 0, -1);
		glVertex3f(-0.87, 0.5, -0.4);
		glNormal3f(0, 0, -1);
		glVertex3f(0, 1, -0.4);
		glNormal3f(0, 0, -1);
		glVertex3f(0.87, 0.5, -0.4);
		glEnd();
		//19
		glBegin(GL_TRIANGLES);
		glNormal3f(0, 0, -1);
		glVertex3f(0.87, 0.5, -0.4);
		glNormal3f(0, 0, -1);
		glVertex3f(0.87, -0.5, -0.4);
		glNormal3f(0, 0, -1);
		glVertex3f(0, -1, -0.4);
		glEnd();
		//20
		glBegin(GL_TRIANGLES);
		glNormal3f(0, 0, -1);
		glVertex3f(0, -1, -0.4);
		glNormal3f(0, 0, -1);
		glVertex3f(-0.87, -0.5, -0.4);
		glNormal3f(0, 0, -1);
		glVertex3f(-0.87, 0.5, -0.4);
		glEnd();

		glPopMatrix();
	}

	glPopMatrix();

}

void Car::move( GLdouble accel, GLdouble delta_t){
	
	if (accel < 0 && _speed > 0) {
		_speed += accel*_break_accel*delta_t;
	}
	if (accel < 0 && fabs(_speed) < _max_reverse_speed) {
		_speed += accel*_accel*delta_t;
	}else if(accel > 0 && fabs(_speed) < _max_speed){
        _speed += accel*_accel*delta_t;
    }
    else if(_speed > 0 && accel == 0){
        _speed -= _friction*delta_t;
		if (_speed < 0) _speed = 0;
    }
	else if (_speed < 0 && accel == 0) {
		_speed += _friction*delta_t;
		if (_speed > 0) _speed = 0;
	}
	DynamicObject::move(delta_t);
}

void Car::turn(GLdouble turn, GLdouble delta_t) {
	if(fabs(_turn_velocity)<_max_turn_speed && fabs(_speed) >0)
		_turn_velocity += turn*_turnSpeed*delta_t*(1.2*_max_speed-_speed)*50;
	_turn_velocity *= _turn_friction;
	_angle += _turn_velocity;
	

	//_angle += turn * _turnSpeed * delta_t;
	_direction.set(cos((_angle*M_PI) / 180), 0, -sin((_angle*M_PI) / 180));
	_moving.set(cos((_angle*M_PI) / 180), 0, -sin((_angle*M_PI) / 180));
	_direction.normalize();
	_moving.normalize();

}

void Car::update(GLdouble delta_t) {
    if(_left_pressed == true && _right_pressed == false){
		turn(1, delta_t);
        _front_wheel_rotation = 50;
    }
    else if(_left_pressed == false && _right_pressed == true){
		turn(-1, delta_t);
		_front_wheel_rotation = -50;
	}
	else {
		_front_wheel_rotation = 0;
		turn(0, delta_t);
	}
    
    
    if(_up_pressed == true && _down_pressed == false){
        move(1, delta_t);
    }
	else if (_up_pressed == false && _down_pressed == true){
		move(-1, delta_t);
	}
	else {
		move(0, delta_t);
	}

	if (checkOutOfBounds() == true) {
        GameManager::getCurrentInstance()->GGWP();
	}
}

void Car::collide(GameObject *obj)
{
    obj->collideWith(this);
}

void Car::collideWith(Butter* butter)
{
    _speed = _speed * 0.7;

}

void Car::collideWith(Orange* orange)
{
    _speed = _speed*0.6;

}

void Car::collideWith(Cheerio* butter)
{
    _speed = _speed * 0.9;
    
}

void Car::reset(GLint lives)
{
	DynamicObject::reset();
	_angle = 0.0;
	_direction.set(1, 0, 0);
}

void Car::toggleSpotLight()
{
	_spot_on = !_spot_on;
	_light_l->setState(_spot_on);
}

void Car::setLight(GLboolean state)
{
	_spot_on = state;
	_light_l->setState(_spot_on);
}


