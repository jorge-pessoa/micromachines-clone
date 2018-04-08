//
//  GameManager.cpp
//  CGProj
//

#include "GameManager.h"
#include "Logger.h"


GameManager* current;
GLdouble t,
delta,
old;

void GameManager::setDisplayCallback()
{
	glutDisplayFunc(GameManager::displayCallback);
	//glutIdleFunc(GameManager::displayCallback);
}

void GameManager::setReshapeCallback()
{
	glutReshapeFunc(GameManager::reshapeCallback);
}

void GameManager::setKeyboardCallback()
{
	glutSpecialFunc(GameManager::specialKeyboardCallback);
    glutSpecialUpFunc(GameManager::specialKeyboardUpCallback);
	glutKeyboardFunc(GameManager::keyboardCallback);
	glutKeyboardUpFunc(GameManager::keyboardUpCallback);
}

void GameManager::setTimerCallback()
{
	glutTimerFunc(TIMER_VAL, GameManager::onTimer, TIMER_VAL);
}

GameManager::GameManager()
{
	current = this;
	_count = 0;
	_accum = 0;
	_w = 1024;
	_h = 768;
	_drawTimer = 0;
	_wireframe = false;
	_camFollow = false;
	_smooth_shading = true;
	_lights = true;

	_light_pool.push_back(GL_LIGHT0);
	_light_pool.push_back(GL_LIGHT1);
	_light_pool.push_back(GL_LIGHT2);
	_light_pool.push_back(GL_LIGHT3);
	_light_pool.push_back(GL_LIGHT4);
	_light_pool.push_back(GL_LIGHT5);
	_light_pool.push_back(GL_LIGHT6);
	_light_pool.push_back(GL_LIGHT7);
}

GameManager::~GameManager()
{
}

void GameManager::display()
{
	//Calculate delta time between frames
	_time = glutGet(GLUT_ELAPSED_TIME);
	_delta = _time - _old;
	_old = _time;
	_accum += _delta;
	_drawTimer += _delta;
	
	//Update everything
	draw();
	_count++;
	
	//Calculate fps 
	if (_accum > 1000) {
		_fps = _count;
		_count = 0;
		_accum = 0;
		Logger::print("FPS: ");
		Logger::print(_fps);
		Logger::print("\n");
	}
}

void GameManager::reshapeCallback(GLsizei w, GLsizei h)
{
	current->reshape(w, h);
}

void GameManager::reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	_current_w = w;
	_current_h = h;
	_cam->computeProjectionMatrix(_current_w, _current_h);
	_cam->computeVisualizationMatrix();

    _uicam->computeProjectionMatrix(_current_w, _current_h);
    _uicam->computeVisualizationMatrix();
}

void GameManager::displayCallback()
{
	current->display();
}

void GameManager::specialKeyboardCallback(int key, int x, int y)
{
	current->specialKeyPressed(key, x, y);
}

void GameManager::specialKeyboardUpCallback(int key, int x, int y)
{
    current->specialKeyPressedUp(key, x, y);
}

void GameManager::keyboardCallback(unsigned char key, int x, int y)
{
	current->keyPressed(key, x, y);
}

void GameManager::keyboardUpCallback(unsigned char key, int x, int y) {

	current->keyboardUp(key, x, y);
}

void GameManager::specialKeyPressed(int key, int x, int y)
{
    
    if(key == GLUT_KEY_UP && _car->_up_pressed == false){
        _car->_up_pressed = true;
    }
    if(key == GLUT_KEY_DOWN && _car->_down_pressed == false){
        _car->_down_pressed = true;
    }
    
    if(key == GLUT_KEY_LEFT && _car->_left_pressed == false){
        _car->_left_pressed = true;
    }
    if(key == GLUT_KEY_RIGHT && _car->_right_pressed == false){
        _car->_right_pressed = true;
    }
}

void GameManager::specialKeyPressedUp(int key, int x, int y)
{
    
    if(key == GLUT_KEY_UP && _car->_up_pressed != false){
        _car->_up_pressed = false;
        
    }
    if(key == GLUT_KEY_DOWN && _car->_down_pressed != false){
        _car->_down_pressed = false;
    }
    
    if(key == GLUT_KEY_LEFT && _car->_left_pressed != false){
        _car->_left_pressed = false;
    }
    if(key == GLUT_KEY_RIGHT && _car->_right_pressed != false){
        _car->_right_pressed = false;
    }

}



void GameManager::keyboardUp(unsigned char key, int _x, int _y)
{
    
}

void GameManager::keyPressed(unsigned char key, int x, int y)
{
    if(_gameover == false){
        if(_pause == false){
            if(key == 's')
                _pause = true;
            if (key == 'a') {
                Logger::printf("Toggle wireframe");
                if (_wireframe)
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                else
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                _wireframe = !_wireframe;
            }
            if(key == 't'){
                _cam->toggleRotate();
                Logger::printf("Toggle rotate");
            }
            if(key == 'g'){
                if(_smooth_shading == true)
                {
                    glShadeModel(GL_FLAT);
                    Logger::printf("Toggle Flat");
                    _smooth_shading = false;
                }
                else{
                    glShadeModel(GL_SMOOTH);
                    Logger::printf("Toggle Smooth");
                    _smooth_shading =true;
                }
            }
            if (key == 'n')
                toggleSunLight();
            if (key == 'l')
                toggleLights();
            if (key == 'c')
                toggleCandles();
			if (key == 'h')
				_car->toggleSpotLight();
            if (key == '1') {
                _cam->stopFollow();
                _cam = _cam1;
                
            }
            if (key == '2') {
                _cam = _cam2;
                _cam->stopFollow();
                _cam->setPosition(0, 100, 1);
                _cam->setLook(Vector3(0, 0, 0));
            }
            if (key == '3') {
                _cam = _cam2;
                _cam->followCar(_car, Vector3(15,7,15));
            }
            if (key == 27) {
                exit(1);
                
            }
            
        }
        else if (key == 's')
            _pause = false;
    } else if (key == 'r'){
        _gameover = false;
    }
}

void GameManager::onTimer(int value)
{
	t = glutGet(GLUT_ELAPSED_TIME);
	delta = t - old;
	old = t;

	current->update(delta);
	current->setTimerCallback();
}

void GameManager::idle()
{
}

void GameManager::update(GLdouble delta_t)
{
    
    if(isRunning()){
        _cam->update();
        for (std::vector<GameObject*>::iterator it = _gobjs.begin(); it != _gobjs.end(); ++it) {
            (*it)->update(delta_t);
        }
        _collision_system->searchCollisions(_gobjs, _car);

		//For collisions between everything
        /*for (std::vector<GameObject*>::iterator it = _gobjs.begin(); it != _gobjs.end(); ++it) {
            if ((*it)->_hascollider == true) {
                DynamicObject* din;
                din = (DynamicObject*)(*it);
                if(din->getSpeed() > 0)
                    _collision_system->searchCollisions(_gobjs, din);
            }
         }*/
        //Redraw
    }
    glutPostRedisplay();
    
}

void GameManager::draw()
{
  
    glClearColor(0.0f, 0.4f, 0.7f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
        
    int a = 0;
        
    _cam->update();
    _cam->calculateCameraDirection();
    _cam->computeProjectionMatrix(_current_w, _current_h);
    _cam->computeVisualizationMatrix();
        
    updateLights();
        
    for (std::vector<GameObject*>::iterator it = _gobjs.begin(); it != _gobjs.end(); ++it) {
        glPushMatrix();
        (*it)->draw();
        glPopMatrix();
        a++;
    }
        
	//Draw UI    
    glDisable(GL_DEPTH_TEST);
    if(_lights == true)
        glDisable(GL_LIGHTING);
    _uicam->calculateCameraDirection();
    _uicam->computeProjectionMatrix(_current_w, _current_h);
    _uicam->computeVisualizationMatrix();
    
    glPushMatrix();
     overlay();
    glPopMatrix();

    glEnable(GL_DEPTH_TEST);
    if (_lights == true)
        glEnable(GL_LIGHTING);
	glFlush();
    
}

void GameManager::overlay()
{
    
    if (_pause == true){
        glPushMatrix();
        _uipause.render();
        glPopMatrix();
    }
    
    if(_gameover == true){
        glPushMatrix();
        _uigameover.render();
        glPopMatrix();
    }
    else for(int i = 0; i < _lives; i++){
        _uicar->setPosition(4-i*0.5, 2, 5);
        glPushMatrix();
        _uicar->draw();
        glPopMatrix();
        
    }
        
}

void GameManager::init(int argc, char* argv[])
{
	Logger::printf("Creating window");

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(_w, _h);
	glutInitWindowPosition(1920/2 - _w / 2, 1080/2 - _h / 2);
	glutCreateWindow("Micro Machines");

	glClearDepth(1.0f);                     // Depth buffer setup
	glEnable(GL_DEPTH_TEST);                // Enable depth testing
	glDepthFunc(GL_LEQUAL);                 // Type of depth test to do
	glDepthRange(0, 1);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_NORMALIZE);

    _smooth_shading = true;
	glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);

	//Setting ambient light
	GLfloat amb[4] = { 0.35f,0.35f,0.35f,1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
	createSunLight();

	setDisplayCallback();
	setReshapeCallback();
	setKeyboardCallback();
	setTimerCallback();
    
    _lives = MAX_LIVES;
    _gameover = false;
    _pause = false;
    
    _uigameover = InterfaceElement(-4, -2, 8, 4);
    _uigameover.setTexture(_UIGAMEOVERPATH);
    _uigameover._active = true;
    
    _uipause = InterfaceElement(-4, -2, 8, 4);
    _uipause.setTexture(_UIPAUSEPATH);
    _uipause._active = true;
    
    _lights = true;

}

void GameManager::start()
{
	_old = glutGet(GLUT_ELAPSED_TIME);
	printf("Starting Game with %lu GameObjects\n", _gobjs.size());
	glutMainLoop();
}

void GameManager::addGameObject(GameObject* obj)
{
	_gobjs.push_back(obj);
}

void GameManager::setCamera(Camera * cam)
{
	_cam = cam;
}

void GameManager::setCameras(Camera * cam1, Camera * cam2, Camera* uicam)
{
	_cam1 = cam1;
	_cam2 = cam2;
    _uicam = uicam;
	_cam = _cam1;
    
}


void GameManager::setCar(Car * car) {

	_car = car;
	Logger::printf("Car added");

}

void GameManager::setUICar(Car * uicar) {
    
    _uicar = uicar;
    Logger::printf("UICar added");
    
}

void GameManager::setCollisionSystem(CollisionSystem* collisionSystem)
{
	_collision_system = collisionSystem;
	Logger::printf("CollisionSystem added");
}

PointLight* GameManager::createPointLight()
{
	PointLight* l = nullptr;
	if (_light_pool.size() > 0) {
		GLenum n = _light_pool.back();
		_light_pool.pop_back();

		l = new PointLight(n);
		l->setState(true);

		//Default PointLight Settings
		l->setAmbient(0, 0, 0, 1);
		l->setDiffuse(1, 1, 1, 1);
		l->setSpecular(0.4, 0.4, 0.4, 0.4);
		l->setPosition(0, 0, 1);

		std::cout << "Enabled light " << n << "\n";
		_light_sources.push_back(l);
	}
	else
		Logger::print("Error: tried to create lights but all lights are used");
	return l;
}

DirectionalLight* GameManager::createDirectionalLight()
{
	DirectionalLight* l = nullptr;
	if (_light_pool.size() > 0) {
		GLenum n = _light_pool.back();
		_light_pool.pop_back();
		
		l = new DirectionalLight(n);
		l->setState(true);

		//Default Light Settings
		l->setAmbient(0, 0, 0, 1);
		l->setDiffuse(1, 1, 1, 1);
		l->setSpecular(1, 1, 1, 1);
		l->setPosition(0, 0, 1);
	
		std::cout << "Enabled light " << n << "\n";
		_light_sources.push_back(l);
	}
	else
		Logger::print("Error: tried to create lights but all lights are used");
	return l;
}

SpotLight * GameManager::createSpotLight()
{
	SpotLight* l = nullptr;
	if (_light_pool.size() > 0) {
		GLenum n = _light_pool.back();
		_light_pool.pop_back();

		l = new SpotLight(n);
		l->setState(true);

		//Default Light Settings
		l->setAmbient(0, 0, 0, 1);
		l->setDiffuse(1, 1, 1, 1);
		l->setSpecular(1, 1, 1, 1);
		//l->setPosition(0, 0, 1);

		std::cout << "Enabled spotlight " << n << "\n";
	}
	else
		Logger::print("Error: tried to create lights but all lights are used");
	return l;
}

void GameManager::deleteLight(LightSource * light)
{
	std::cout << "Deleting light " << light->getNum();
	_light_pool.push_back(light->getNum());
	glDisable(light->getNum());
	delete light;
}

void GameManager::updateLights()
{
	for (std::vector<LightSource*>::iterator it = _light_sources.begin(); it != _light_sources.end(); ++it) {
		glPushMatrix();
		(*it)->draw();
		glPopMatrix();
	}
}

GLboolean GameManager::wireframe()
{
	return _wireframe;
}

void GameManager::GGWP()
{
    _lives--;
    for (std::vector<GameObject*>::iterator it = _gobjs.begin(); it != _gobjs.end(); ++it) {
        (*it)->reset(_lives);
    }
    if(_lives <= 0){
        _gameover = true;
        _lives = MAX_LIVES;
    }
}

void GameManager::toggleLights()
{
	if (_lights)
		glDisable(GL_LIGHTING);
	else
		glEnable(GL_LIGHTING);
	_lights = !_lights;
}

void GameManager::createSunLight()
{
	sun_light = createDirectionalLight();
	sun_light->setPosition(0, 1, 0);
	sun_light->setDiffuse(.8, .8, .8, 1.0);
	sun_light->setAmbient(0.8, 0.8, 0.8, 1.0);
	sun_light->setSpecular(0.6, 0.6, 0.6, 1.0);
}

void GameManager::toggleSunLight()
{
	printf("Toggle\n");
	if (sun_light->getState()) {
		printf("Disable\n");
		sun_light->setState(false);
		_car->setLight(true);
	}
	else {
		sun_light->setState(true);
		_car->setLight(false);
	}
}

void GameManager::toggleCandles()
{
	printf("toggle!");
	for (std::vector<GameObject*>::iterator it = _gobjs.begin(); it != _gobjs.end(); ++it) {
		(*it)->toggleLights();
	}
}

GameManager * GameManager::getCurrentInstance()
{
	return current;
}

GLboolean GameManager::isRunning()
{
    if(_gameover == true || _pause == true)
        return false;
    return true;
}
