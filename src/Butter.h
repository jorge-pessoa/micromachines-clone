//
//  Butter.h
//  CGProj
//

#ifndef __CGProj__Butter__
#define __CGProj__Butter__

#include "Common.h"
#include "Obstacle.h"
#include "Car.h"

class Butter : public Obstacle{
private:
	GLboolean checkOutOfBounds();
public:
	Butter();
    Butter(GLdouble posx, GLdouble posy, GLdouble posz,
           GLdouble rotangle=0, GLdouble rotx=0, GLdouble roty=0, GLdouble rotz=0,
           GLdouble scalex=1, GLdouble scaley=1, GLdouble scalez=1);
	~Butter();
	void render();
	void update(GLdouble delta_t);

	void collide(GameObject* obj);
    void collideWith(Car* car);
    void reset(GLint lives);
    
};
#endif /* defined(__CGProj__Butter__) */
