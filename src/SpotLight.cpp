#include "SpotLight.h"

SpotLight::SpotLight(GLenum num) : LightSource(num)
{
	_w = 1.0;
	//setCutoff(60.0);
	//setExponent(12.0);
	//setDirection(0, 0, 0);
}

SpotLight::~SpotLight()
{
}

void SpotLight::setExponent(GLfloat exp)
{
	LightSource::setExponent(exp);
}

void SpotLight::setCutoff(GLfloat cutoff)
{
	LightSource::setCutoff(cutoff);
}

void SpotLight::setDirection(GLfloat x, GLfloat y, GLfloat z)
{
	LightSource::setDirection(x, y, z);
}

void SpotLight::setDirection(Vector3 & dir)
{
	LightSource::setDirection(dir);
}

void SpotLight::setAttenuation(GLfloat constant, GLfloat linear, GLfloat quadric)
{
	LightSource::setAttenuation(constant, linear, quadric);
}
