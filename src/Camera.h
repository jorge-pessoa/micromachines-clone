//
//  Camera.h
//  CGProj
//

#ifndef __CGProj__Camera__
#define __CGProj__Camera__

#include "Common.h"
#include "Vector3.h"
#include "GameObject.h"
#include "Car.h"

class Camera : public GameObject{
protected:
	GLfloat _near,
			_far;
	Vector3 _up,
			_look,
			_direction,
			_rightaxis,
			_follow_offset;
    GLboolean _rotate,
			  _to_follow;
	Car* _follow;

public:
	Camera();
	~Camera();
	virtual void update();
	virtual void updateMatrix(GLdouble w, GLdouble h);
	virtual void computeProjectionMatrix(GLdouble w, GLdouble h);
	virtual void computeVisualizationMatrix();

    void toggleRotate();

	void calculateCameraDirection();
	void calculateRightAxis();
	void calculateUpVector();

	void setDirection(Vector3& dir);
	void setLook(Vector3 look);

	void followCar(Car* gobj, Vector3 offset);
	void stopFollow();
};

#endif /* defined(__CGProj__Camera__) */
