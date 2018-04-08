//
//  PointLight.h
//  CGProj
//

#ifndef __CGProj__PointLight__
#define __CGProj__PointLight__

#include "Common.h"
#include "LightSource.h"
#include "Vector3.h"


class PointLight : public LightSource {
private:
public:

	PointLight(GLenum num);
	~PointLight();
	void setAttenuation(GLdouble constant, GLdouble linear, GLdouble quadric);
};

#endif /* defined(__CGProj__PointLight__) */