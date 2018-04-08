#include "OrthographicCamera.h"

OrthographicCamera::OrthographicCamera()
{
	OrthographicCamera::OrthographicCamera(-30, 30, -20, 20, 5, 200);
}

OrthographicCamera::OrthographicCamera(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far)
{
	Camera::Camera();

	_near = near;
	_far = far;
	_left = left;
	_right = right;
	_bottom = bottom;
	_top = top;


	_up = Vector3();
	_look = Vector3(0, 0, 0);

	calculateCameraDirection();
	calculateRightAxis();
	calculateUpVector();
}

OrthographicCamera::~OrthographicCamera()
{
}


void OrthographicCamera::computeProjectionMatrix(GLdouble w, GLdouble h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat ratio = (_right - _left) / (_top - _bottom);
	GLfloat aspect = (GLfloat)(w / h);
	if (ratio < aspect)
	{
		GLfloat delta = ((_top - _bottom) * aspect - (_right - _left)) / 2;
		glOrtho(_left - delta, _right + delta, _bottom, _top, _near, _far);
	}
	else
	{
		GLfloat delta = ((_right - _left) / aspect - (_top - _bottom)) / 2;
		glOrtho(_left, _right, _bottom - delta, _top + delta, _near, _far);
	}
}
