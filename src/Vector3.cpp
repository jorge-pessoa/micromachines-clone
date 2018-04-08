//
//  Vector3.cpp
//  CGProj
//

#include "Vector3.h"

Vector3::Vector3(){
    Vector3(0,0,0);
}

Vector3::Vector3 (GLdouble x, GLdouble y, GLdouble z) : _x(x), _y(y), _z(z) {
}

Vector3::~Vector3(){
}

GLdouble Vector3::getX() {
    return _x;
}

GLdouble Vector3::getY() {
	return _y;
}

GLdouble Vector3::getZ() {
	return _z;
}

GLdouble Vector3::getSize2D()
{
	GLdouble size = sqrt(pow(_x, 2) + pow(_z, 2));
	return size;
}

void Vector3::set(GLdouble x, GLdouble y, GLdouble z){
    _x = x;
    _y = y;
    _z = z;
}

void Vector3::set(Vector3 v)
{
	_x = v._x;
	_y = v._y;
	_z = v._z;
}

Vector3& Vector3::operator=(const Vector3& vec){
	this->set(vec._x, vec._y, vec._z);
	return *this;
}
Vector3& Vector3::operator+(const Vector3& vec){
	this->set(_x + vec._x, _y + vec._y, _z + vec._z);
	return *this;
}
Vector3& Vector3::operator-(const Vector3& vec){
	this->set(_x - vec._x, _y - vec._y, _z - vec._z);
	return *this;
}
Vector3& Vector3::operator*(double d){
	this->set(_x*d, _y*d, _z*d);
	return *this;
}

void Vector3::normalize()
{
	GLdouble size = sqrt(_x*_x +
		_y*_y +
		_z*_z);
	set(_x / size, _y / size, _z / size);
}

void Vector3::normalize2D()
{
	GLdouble size = sqrt(_x*_x +
		_z*_z);
	set(_x / size, _y, _z / size);
}

void Vector3::crossProduct(Vector3& v1, Vector3& v2, Vector3& res)
{
	res.set(v1._y*v2._z - v1._z*v2._y,
		v1._z*v2._x - v1._x*v2._z,
		v1._x*v2._y - v1._y*v2._x);
}

std::ostream& operator<<(std::ostream& os, const Vector3& v) {
	os << "< " << v._x << " , " << v._y << " , " << v._z << " >";
	return os;
}

void Vector3::rotate2D(GLfloat angle) {
	GLfloat x, z;
	x = _x;
	z = _z;
	_x = x*cos(angle) - z*sin(angle);
	_z = x*cos(angle) + z*sin(angle);
	std::cout << "x " << _x << " , y " << _z << "\n";

	//normalize2D();
}

GLfloat Vector3::dotProduct2D(Vector3 v1, Vector3 v2) {
	GLfloat result;
	result = v1._x * v2._x + v1._z * v2._z;
	return result;
}

GLfloat Vector3::angleBetweenVector2D(Vector3 v1, Vector3 v2) {
	GLfloat result = dotProduct2D(v1, v2);
	result /= (v1.getSize2D()*v2.getSize2D());
	result = acos(result);
	return result;
}