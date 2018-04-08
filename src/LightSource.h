//
//  LightSource.h
//  CGProj
//

#ifndef __CGProj__LightSource__
#define __CGProj__LightSource__

#include "Common.h"
#include "Vector3.h"
#include "GameObject.h"

class GameObject;

class LightSource {
protected:
	Vector3 _position,
			_direction;
	GLfloat _ambient[4] = { 0.0, 0.0, 0.0, 1.0 },
			 _diffuse[4] = { 0.0, 0.0, 0.0, 1.0 },
			 _specular[4] = { 0.0, 0.0, 0.0, 1.0 };

	GLfloat _cut_off,
			 _exponent,

			 _w;
	GLenum _num;
	GLboolean _state,
			  _attached;

	GameObject* _parent;

	virtual void setExponent(GLfloat exp);
	virtual void setCutoff(GLfloat cutoff);
	virtual void setAttenuation(GLfloat constant, GLfloat linear, GLfloat quadric);
	virtual void setDirection(GLfloat x, GLfloat y, GLfloat z);
	virtual void setDirection(Vector3& dir);

public:
	LightSource();
	LightSource(GLenum num);
	~LightSource();

	GLboolean getState();
	void setState(GLboolean state);
	GLenum getNum();

	Vector3& getPosition();
	void setPosition(GLfloat x, GLfloat y, GLfloat z);
	void setPosition(Vector3& vec);
	void updatePosition();
	void updateDirection();

	void setAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	void setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	void setSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

	void attach(GameObject* parent);
	void detach();

	void draw();
};

#endif /* defined(__CGProj__LightSource__) */
