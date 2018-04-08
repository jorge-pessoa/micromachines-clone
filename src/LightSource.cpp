#include "LightSource.h"

LightSource::LightSource()
{
	_position = Vector3(0,0,0);
	_direction = Vector3(0,0,0);
	setPosition(0, 0, 0);
	setDirection(0, 0, 1);
	_state = true;
	_attached = false;
	_w = 0.0;
}

LightSource::LightSource(GLenum num)
{
	_num = num;
}

LightSource::~LightSource()
{
}

GLboolean LightSource::getState()
{
	return _state;
}

void LightSource::setState(GLboolean state)
{
	printf("state\n");
	_state = state;
	if (state) {
		glEnable(_num);
		printf("Enable light\n");
	}
	else {
		printf("Disable light\n");
		glDisable(_num);
	}
}

GLenum LightSource::getNum()
{
	return _num;
}

Vector3 & LightSource::getPosition()
{
	return _position;
}

void LightSource::setPosition(GLfloat x, GLfloat y, GLfloat z)
{
	_position.set(x, y, z);
	//updatePosition();
}

void LightSource::setPosition(Vector3 & vec)
{
	_position.set(vec);
	/*GLfloat pos[4] = { (GLfloat)_position._x,
					   (GLfloat)_position._y,
					   (GLfloat)_position._z,
					   _w};
	glLightfv(_num, GL_POSITION, pos);*/
}

void LightSource::updatePosition()
{
	GLfloat pos[4] = { _position._x, _position._y, _position._z, _w };
	if (_attached == true) {
		pos[0] += _parent->_position._x;
		pos[1] += _parent->_position._y;
		pos[2] += _parent->_position._z;
	}
	glLightfv(_num, GL_POSITION, pos);
}

void LightSource::updateDirection()
{
	GLfloat dir[4] = { _direction._x ,_direction._y ,_direction._z ,0.0 };
	glLightfv(_num, GL_SPOT_DIRECTION, dir);
}

void LightSource::setDirection(GLfloat x, GLfloat y, GLfloat z)
{
	_direction.set(x, y, z);
}

void LightSource::setDirection(Vector3 & dir)
{
	_direction.set(dir);
	GLfloat vec[4] = { (GLfloat) _direction._x,
                       (GLfloat) _direction._y,
                       (GLfloat) _direction._z,
                       0.0 };
	glLightfv(_num, GL_SPOT_DIRECTION, vec);
}

void LightSource::setAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	_ambient[0] = r;
	_ambient[1] = g;
	_ambient[2] = b;
	_ambient[3] = b;
	glLightfv(_num, GL_AMBIENT, _ambient);
}

void LightSource::setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	_diffuse[0] = r;
	_diffuse[1] = g;
	_diffuse[2] = b;
	_diffuse[3] = b;
	glLightfv(_num, GL_DIFFUSE, _diffuse);
}
 
void LightSource::setSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	_specular[0] = r;
	_specular[1] = g;
	_specular[2] = b;
	_specular[3] = b;
	glLightfv(_num, GL_SPECULAR, _specular);
}

void LightSource::attach(GameObject * parent)
{
	_attached = true;
	_parent = parent;
}

void LightSource::detach()
{
	_attached = false;
}

void LightSource::setExponent(GLfloat exp)
{
	_exponent = exp;
	GLfloat val[1] = { exp };
	glLightfv(_num, GL_SPOT_EXPONENT, val);
}

void LightSource::setCutoff(GLfloat cutoff)
{
	_cut_off = cutoff;
	GLfloat val[1] = { cutoff };
	glLightfv(_num, GL_SPOT_CUTOFF, val);
}

void LightSource::setAttenuation(GLfloat constant, GLfloat linear, GLfloat quadric)
{
	GLfloat val[1] = { constant };
	glLightfv(_num, GL_CONSTANT_ATTENUATION, val);
	val[0] = linear;
	glLightfv(_num, GL_LINEAR_ATTENUATION, val);
	val[0] = quadric;
	glLightfv(_num, GL_QUADRATIC_ATTENUATION, val);
}

void LightSource::draw()
{	
	updatePosition();
	updateDirection();
	//(_direction);
	//setExponent(_exponent);
}
