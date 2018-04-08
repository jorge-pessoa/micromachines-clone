#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(GLenum num) : LightSource(num)
{
	_w = 0.0;
}

DirectionalLight::~DirectionalLight()
{
}
