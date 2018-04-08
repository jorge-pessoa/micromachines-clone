#ifndef __CGProj__PerspectiveCamera__
#define __CGProj__PerspectiveCamera__

#include "Common.h"
#include "Vector3.h"
#include "Camera.h"

class PerspectiveCamera : public Camera {
private:
	GLfloat _aspect, 
			_fov;
public:
	PerspectiveCamera();
	PerspectiveCamera(GLfloat fov, GLfloat near, GLfloat far);
	~PerspectiveCamera();

	void computeProjectionMatrix(GLdouble w, GLdouble h);

};

#endif /* defined(__CGProj__Camera__) */
