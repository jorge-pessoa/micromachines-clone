//
//  Car.h
//  CGProj
//

#ifndef __CGProj__Car__
#define __CGProj__Car__

#include "Common.h"
#include "DynamicObject.h"
#include "Vector3.h"
#include "Orange.h"
#include "Butter.h"
#include "Cheerio.h"
#include "SpotLight.h"

class Car : public DynamicObject {
private:
	GLboolean checkOutOfBounds();
	Vector3 _moving;
    Material _materialmotor,
             _materialrodas,
             _materialcapota;
	SpotLight *_light_l,
				*_light_r;
public:
	GLdouble _turnSpeed,
			_angle,
			_facing_angle,
			_max_speed,
			_break_accel,
			_max_reverse_speed,
			_turn_friction,
			_turn_velocity,
			_max_turn_speed,
			_max_facing_angle,
			_drift,
			_front_wheel_rotation;

    GLboolean _left_pressed,
			  _right_pressed, 
			  _down_pressed, 
			  _up_pressed,
			  _spot_on;

    Car();
    Car(GLdouble posx, GLdouble posy, GLdouble posz,
           GLdouble rotangle=0, GLdouble rotx=0, GLdouble roty=0, GLdouble rotz=0,
           GLdouble scalex=1, GLdouble scaley=1, GLdouble scalez=1);
    ~Car();
    void init();
    void render();
    void move(GLdouble accel, GLdouble delta_t);
    void turn(GLdouble turn, GLdouble delta_t);
    void update(GLdouble delta_t);
    
    void collide(GameObject* obj);
	void collideWith(Butter* butter);
    void collideWith(Orange* orange);
    void collideWith(Cheerio* butter);

	void reset(GLint lives);
	void toggleSpotLight();
	void setLight(GLboolean state);
};

#endif /* defined(__CGProj__Car__) */
