//
//  Cheerio.h
//  CGProj
//

#ifndef __CGProj__Cheerio__
#define __CGProj__Cheerio__

#include "Common.h"
#include "Obstacle.h"
#include "Vector3.h"
#include "Car.h"

class Cheerio : public Obstacle {
private:
public:

	Cheerio();
	Cheerio(GLdouble posx, GLdouble posy, GLdouble posz,
		GLdouble rotangle = 0, GLdouble rotx = 0, GLdouble roty = 0, GLdouble rotz = 0,
		GLdouble scalex = 1, GLdouble scaley = 1, GLdouble scalez = 1);

	~Cheerio();
	void render();
    
    void collide(GameObject* obj);
    void collideWith(Car* car);
    void collideWith(Butter* car);
    void collideWith(Cheerio* car);
    void reset(GLint lives);
};

#endif /* defined(__CGProj__Orange__) */
