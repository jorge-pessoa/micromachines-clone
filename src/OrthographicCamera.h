#ifndef __CGProj__OrthographicCamera__
#define __CGProj__OrtographicCamera__

#include "Common.h"
#include "Vector3.h"
#include "Camera.h"

class OrthographicCamera : public Camera {
private:
	GLfloat _left,
			_right,
			_bottom,
			_top;
public:
	OrthographicCamera();
	OrthographicCamera(GLfloat left, GLfloat right, GLfloat top, GLfloat bottom, GLfloat near, GLfloat far);
	~OrthographicCamera();

	void computeProjectionMatrix(GLdouble w, GLdouble h);

};

#endif /* defined(__CGProj__Camera__) */
