#include "Candle.h"

Candle::Candle()
{
	Candle(0, 0, 0);
}

Candle::Candle(GLdouble posx, GLdouble posy, GLdouble posz)
	: GameObject(posx, posy, posz)
{

	PointLight* _light;
	_light = GameManager::getCurrentInstance()->createPointLight();
	_light->setPosition(_position._x, _position._y+5,_position._z);
	_light->setAttenuation(0.0, 0.005, 0.0016);
	_light->setDiffuse(0.3, 0.3, 0.3, 1.0);
	_light->setAmbient(0.0, 0.0, 0.0, 1.0);
	_light->setSpecular(0.3, 0.3, 0.3, 1.0);
	_light->setState(true);
	addLight(_light);

	GLfloat amb[4] = { 0.0f,0.0f,0.0f,1.0f },
		diff[4] = { 0.25f,0.120f,0.01f,1.0f },
		spec[4] = { 0.0f,0.0f,0.0f,1.0f },
		shine = 0.0f;	
	_material_lamp.setValues(amb, diff, spec, shine);
	GLfloat ambp[4] = { 0.00f,0.0f,0.0f,1.0f },
		diffp[4] = { 0.05,0.05,0.05f,1.0f },
		specp[4] = { 0.0f,0.0f,0.0f,1.0f },
		shinep = 0;	
	setMaterial(ambp, diffp, specp, shinep);

}

Candle::~Candle()
{
}

void Candle::render()
{
	glPushMatrix();
	glColor3f(0.3, 0.08, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glScalef(0.5, 0.5, 0.5);
	glutSolidTorus(0.4, 0.9, 4, 10);
	glColor3f(0.15, 0.15, 0.15);
	_material_lamp.applyMaterial();
	glutSolidCone(2.0, 3.0, 4, 4);
	glScalef(1.0, 1.0, 8.0);
	glTranslatef(0.0,0.0,-0.5);
	glutSolidCube(1.0);
	glPopMatrix();
}


