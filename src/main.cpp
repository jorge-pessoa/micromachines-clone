//
//  main.cpp
//  CGProj
//

#include "Common.h"
#include "GameManager.h"
#include "Logger.h"
#include "Car.h"
#include "Table.h"
#include "Roadside.h"
#include "Orange.h"
#include "butter.h"
#include "OrthographicCamera.h"		
#include "PerspectiveCamera.h"
#include "PointLight.h"
#include "Candle.h"
#include <time.h>

#define NUM_ORANGES 3
#define NUM_BUTTERS 5

int main(int argc, char * argv[]) {
	
    srand (static_cast <unsigned> (time(0)));

    int posx,posy,posz,angle,rotx=0,roty=0,rotz=0;
    float scale;
    
	GameManager* gameMgr = new GameManager();
	gameMgr->init(argc, argv);

	Car* car = new Car(-16,-1.5,-24,0,0,1,0,.5f,.5f,.5f);
    Car* uicar = new Car(0,0,0,-90,1,0,0,0.1f,0.1f,0.1f);
    Table* table = new Table(0,0.0,0);

    Roadside* roadside = new Roadside(0,0,0);
	//Center left
	Candle* candle1 = new Candle(-20,0,-5);
	//Center right
	//Candle* candle5 = new Candle(30, 0,-5);
	//bottom right
	Candle* candle2 = new Candle( 47, 0, 32);
	//top right
	Candle* candle3 = new Candle( 47, 0, -32);
	//bottom left
	Candle* candle4 = new Candle( -40, 0, 33);
	//top left
	Candle* candle6 = new Candle( -40, 0, -33);

	Logger::printf("Initializing Game Manager");

	OrthographicCamera* cam = new OrthographicCamera(-50, 55, -30, 30, 5, 300);
	cam->setPosition(0, 125, 1);
    cam->calculateCameraDirection();
    OrthographicCamera* uicam = new OrthographicCamera(-10, 10, -5,5, -5, 5);
    uicam->setPosition(0, 5, 1);
	uicam->calculateCameraDirection();
	PerspectiveCamera* cam2 = new PerspectiveCamera(45.0, 5, 300);
	cam2->setPosition(0, 125, 1);
	cam2->calculateCameraDirection();

	gameMgr->setCameras(cam,cam2, uicam);

	gameMgr->setCar(car);
    gameMgr->setUICar(uicar);
    
	gameMgr->addGameObject(car); 
    gameMgr->addGameObject(table);
    gameMgr->addGameObject(roadside);
	gameMgr->addGameObject(candle1);
	gameMgr->addGameObject(candle2);
	gameMgr->addGameObject(candle3);
	gameMgr->addGameObject(candle4);
	//gameMgr->addGameObject(candle5);
	gameMgr->addGameObject(candle6);

	table->addChild(car);
	table->addChild(roadside);

	/*PointLight* light = gameMgr->createPointLight();
	light->setPosition(-10, 0.1, -10);
	light->setAttenuation(0.0000, 0.00, 0.004);
	light->setDiffuse(0.6, 0.6, 0.6, 1.0);
    */

	GameObject* temp;

    //Orange Generator
    for(long i = 0; i < NUM_ORANGES; i++){
        posx =((std::rand() % (60 -0 + 1)))-30;
        posy = 0;
        posz = (std::rand() % (60-0 + 1))-30;
        roty = 1;
        angle = (std::rand() % (360-0 + 1));
        scale = 0.8+(std::rand() % (40-0 + 1))/100.0f;
		temp = new Orange(posx, posy, posz 
			, angle, rotx, roty, rotz
			, scale, scale, scale);
        gameMgr->addGameObject(temp);
		table->addChild(temp);
    }
    //Butter Generator
    for(long i = 0; i < NUM_BUTTERS; i++){
        posx =((std::rand() % (60 -0 + 1)))-30;
        posy = -1;
        posz = (std::rand() % (60-0 + 1))-30;
        roty = 1;
        angle = (std::rand() % (360-0 + 1));
        scale = 0.8+(std::rand() % (20-0 + 1))/100.0f;
		temp = new Butter(posx, posy, posz
			, angle, rotx, roty, rotz
			, scale, scale, scale);
        gameMgr->addGameObject(temp);
		table->addChild(temp);
    }
    
    
	gameMgr->start();
	
	return 0;

}
