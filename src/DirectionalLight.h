//
//  DirectionalLight.h
//  CGProj
//

#ifndef __CGProj__DirectionalLight__
#define __CGProj__DirectionalLight__

#include "Common.h"
#include "LightSource.h"
#include "Vector3.h"


class DirectionalLight : public LightSource {
private:
public:
	DirectionalLight(GLenum num);
	~DirectionalLight();
};

#endif /* defined(__CGProj__DirectionalLight__) */
