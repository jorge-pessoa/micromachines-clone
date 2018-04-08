//
//  SpotLight.h
//  CGProj
//

#ifndef __CGProj__SpotLight__
#define __CGProj__SpotLight__

#include "Common.h"
#include "LightSource.h"
#include "Vector3.h"


class SpotLight : public LightSource {
private:
public:
	SpotLight(GLenum num);
	~SpotLight();
	virtual void setExponent(GLfloat exp);
	virtual void setCutoff(GLfloat cutoff);
	virtual void setDirection(GLfloat x, GLfloat y, GLfloat z);
	virtual void setDirection(Vector3& dir);
	virtual void setAttenuation(GLfloat constant, GLfloat linear, GLfloat quadric);
};

#endif /* defined(__CGProj__DirectionalLight__) */
