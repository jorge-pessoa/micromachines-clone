//
//  Material.h
//  CGProj
//

#ifndef __CGProj__Material__
#define __CGProj__Material__

#include "Common.h"

class Material {
private:
    GLfloat _amb[4] = {0.0, 0.0, 0.0, 0.0},
            _diff[4] = {0.0, 0.0, 0.0, 0.0},
            _spec[4] = {0.0, 0.0, 0.0, 0.0},
            _shine = 0.0;
public:
	Material();
    Material(GLfloat amb[4], GLfloat diff[4], GLfloat spec[4], GLfloat shine);
	~Material();
	void applyMaterial();
    void setValues(GLfloat amb[4], GLfloat diff[4], GLfloat spec[4], GLfloat shine);
};

#endif /* defined(__CGProj__Material__) */