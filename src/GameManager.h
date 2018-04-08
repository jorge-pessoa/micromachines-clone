//
//  GameManager.h
//  CGProj
//

#ifndef __CGProj__GameManager__
#define __CGProj__GameManager__

#include "Common.h"
#include "GameObject.h"
#include "Camera.h"
#include "Car.h"
#include "CollisionSystem.h"
#include "LightSource.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "DirectionalLight.h"
#include "DynamicObject.h"
#include "InterfaceElement.h"
#include "SOIL.h"

#define TIMER_VAL 8
#define MAX_LIVES 5

#if defined(__APPLE__) || defined(MACOSX)
#define _UIGAMEOVERPATH "/Users/Administrador/Documents/DEV/GameDev/CG/Assets/GameOver.png"
#define _UIPAUSEPATH "/Users/Administrador/Documents/DEV/GameDev/CG/Assets/Pause.png"
#else
#define _UIGAMEOVERPATH "assets\\GameOver.png"
#define _UIPAUSEPATH "assets\\Pause.png"
#endif

class Camera;
class CollisionSystem;
class Spotlight;

class GameManager {
private:

	std::vector<GameObject*> _gobjs;
	std::vector<LightSource*> _light_sources;
	std::vector<GLenum> _light_pool;
	Camera *_cam1,
		   *_cam2, 
		   *_cam,
           *_uicam;

	Car* _car, *_uicar;
    
    InterfaceElement _uigameover,
                     _uipause;
    
	DirectionalLight* sun_light;
    CollisionSystem* _collision_system;

	GLdouble _time,
			 _delta,
			 _old,
			 _fps,
			 _count,
			 _accum,
			 _drawTimer;

	GLdouble _w,
			 _h;

	GLsizei	_current_w,
			_current_h;
	
	GLboolean _wireframe,
			  _camFollow,
              _smooth_shading,
			  _lights,
              _gameover,
              _pause;
    
    
    GLint   _lives;
    
	void setDisplayCallback();
	void setReshapeCallback();
	void setKeyboardCallback();
	void setTimerCallback();
public:
	GameManager();
	~GameManager();

	static void reshapeCallback(GLsizei w, GLsizei h);
	static void displayCallback();
	static void specialKeyboardCallback(int key, int x, int y);
    static void specialKeyboardUpCallback(int key, int x, int y);
	static void keyboardCallback(unsigned char key, int x, int y);
	static void keyboardUpCallback(unsigned char key, int x, int y);
	static void onTimer(int value);

	void reshape(GLsizei w, GLsizei h);
	void display();
	void specialKeyPressed(int key, int x, int y);
    void specialKeyPressedUp(int key, int x, int y);
	void keyPressed(unsigned char key, int x, int y);
    void keyboardUp(unsigned char key, int x, int y);

	void idle();

	void update(GLdouble delta_t);
	void draw();
    void overlay();

	void init(int argc, char* argv[]);
	void start();

	void addGameObject(GameObject* obj);
	void setCamera(Camera* cam);
	void setCameras(Camera* cam1, Camera* cam2, Camera* uicam);
	void setCar(Car * car);
    void setUICar(Car* uicar);
    void setCollisionSystem(CollisionSystem* collisionSystem);
    
	PointLight* createPointLight();
	DirectionalLight* createDirectionalLight();
	SpotLight* createSpotLight();
	void deleteLight(LightSource* light);
	void updateLights();

	GLboolean wireframe();
    void GGWP();
	
	void toggleLights();
	void createSunLight();
	void toggleSunLight();
	void toggleCandles();

	static GameManager* getCurrentInstance();
    GLboolean isRunning();
};

#endif /* defined(__CGProj__GameManager__) */
