//
//  Vector3.h
//  CGProj
//

#ifndef __CGProj__Vector3__
#define __CGProj__Vector3__

#include "Common.h"
#include <memory>

class Vector3 {
private:
public:
	GLfloat _x,
			 _y,
			 _z;
	Vector3();
    Vector3(GLdouble x, GLdouble y, GLdouble z);
    ~Vector3();
    
	GLdouble getX() ;
    GLdouble getY() ;
    GLdouble getZ() ;
	GLdouble getSize2D();

	void set(GLdouble x, GLdouble y, GLdouble z);
	void set(Vector3 v);
    Vector3& operator=(const Vector3& vec);
    Vector3& operator+(const Vector3& vec);
    Vector3& operator-(const Vector3& vec);
    Vector3& operator*(double d);
	friend std::ostream& operator<<(std::ostream& os, const Vector3& v);

	void normalize();
	void normalize2D();
	void rotate2D(GLfloat angle);

	static void crossProduct(Vector3& v1, Vector3& v2, Vector3& res);
	static GLfloat dotProduct2D(Vector3 v1, Vector3 v2);
	static GLfloat angleBetweenVector2D(Vector3 v1, Vector3 v2);
};
#endif /* defined(__CGProj__Vector3__) */
