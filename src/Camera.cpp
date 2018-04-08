//
//  Camera.cpp
//  CGProj
//

#include "Camera.h"
#include "Logger.h"
#include "Car.h"


Camera::Camera() {
	_rotate = false;
	_to_follow = false;
}

Camera::~Camera(){
}

void Camera::update()
{
	if (_to_follow) {
		setPosition(_follow->getPosition()._x - _follow->getDirection()._x * _follow_offset._x,
					_follow->getPosition()._y + _follow_offset._y, 
					_follow->getPosition()._z - _follow->getDirection()._z * _follow_offset._z);
		setLook(Vector3(_follow->getPosition()._x + _follow->getDirection()._x * 50,
						_follow->getPosition()._y, 
						_follow->getPosition()._z + _follow->getDirection()._z * 50));
	}
}

void Camera::updateMatrix(GLdouble w, GLdouble h){
    //glViewport(0, 0, w, h);
	calculateCameraDirection();
	computeProjectionMatrix(w, h);
	computeVisualizationMatrix();
}

void Camera::computeProjectionMatrix(GLdouble w, GLdouble h){
}

double rotator = 0;	
void Camera::computeVisualizationMatrix(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (_rotate) {
		rotator++;
		setPosition(50*cos(rotator/30.0), _position._y, 50*sin(rotator/30.0));
		calculateCameraDirection();
		calculateRightAxis();
		gluLookAt(_position._x,
			_position._y,
			_position._z,
			_position._x - _direction._x,
			_position._y - _direction._y,
			_position._z - _direction._z,
			0, 1, 0);
	}else {
		gluLookAt(_position._x,
			_position._y,
			_position._z,
			_position._x - _direction._x,
			_position._y - _direction._y,
			_position._z - _direction._z,
			0, 1, 0);
	}
}

void Camera::toggleRotate(){
    _rotate = !_rotate;
}

void Camera::calculateCameraDirection()
{
	Vector3 t = Vector3(_position);
	_direction = t - _look;
	_direction.normalize();
}

void Camera::calculateRightAxis()
{
    Vector3 vector = Vector3(0,1,0);
	Vector3::crossProduct(vector, _direction, _rightaxis);
}

void Camera::calculateUpVector() {
	Vector3::crossProduct(_direction, _rightaxis, _up);
}

void Camera::setDirection(Vector3& dir) {
	_direction.set(dir._x, dir._y, dir._z);
}

void Camera::setLook(Vector3 look) {
	_look.set(look._x, look._y, look._z);
}

void Camera::followCar(Car* gobj, Vector3 offset)
{
	std::cout << "folow";
	_follow = gobj;
	_to_follow = true;
	_follow_offset = offset;
}

void Camera::stopFollow()
{
	_to_follow = false;
	_follow = NULL;
}


