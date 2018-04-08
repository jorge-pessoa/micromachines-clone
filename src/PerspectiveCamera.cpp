#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera()
{
	PerspectiveCamera::PerspectiveCamera(45.0, 5, 200);
}

PerspectiveCamera::PerspectiveCamera(GLfloat fov, GLfloat near, GLfloat far)
{
	Camera::Camera();
	_fov = fov;
	_near = near;
	_far = far;
	_aspect = 4.0 / 3.0;
	_up = Vector3();
	_look = Vector3(0, 0, 0);
	setPosition(0, 125, 1);
	calculateCameraDirection();
	calculateRightAxis();
	calculateUpVector();
}

PerspectiveCamera::~PerspectiveCamera()
{
}


void PerspectiveCamera::computeProjectionMatrix(GLdouble w, GLdouble h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat ratio = (GLfloat)(w / h);
	if (ratio > _aspect) {													// Horizontal stretch
		GLfloat delta;
		if (ratio < 2 * _aspect) {
			delta = (1.0 / 4.0)*_fov*(ratio - _aspect);
			gluPerspective(_fov - delta, ratio, _near, _far);

		}
		else {
			delta = (1.0 / 24.0)*_fov*(ratio - _aspect);
			gluPerspective(_fov + delta, ratio, _near, _far);

		}
	}else{
		GLfloat delta = (6.0/4.0)*_fov*(_aspect - ratio);
		gluPerspective(_fov + delta, ratio, _near, _far);
	}
}
