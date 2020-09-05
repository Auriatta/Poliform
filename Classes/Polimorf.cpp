#include "Polimorf.h"


void Polimorf::Create_Spawner(cocos2d::Point location)
{
	/*
	I created this object via 'new'
	because it will release itself anyway
	*/
	CellSpawner* cell_spawner = new CellSpawner(location);
}

void Polimorf::Update()
{
	behavior->update();

	Create_Spawner(behavior->getPosition());
}


cocos2d::Point Polimorf::getRandomPositionInBordersBox()
{
	return cocos2d::Point(
		Random::random_int<int>(BORDER_X_ORIGIN, BORDER_WIDTH),
		Random::random_int<int>(BORDER_Y_ORIGIN, BORDER_HEIGHT));
}


void Polimorf::Run()
{
	const float refreshRate = 0.5;
	cocos2d::Director::getInstance()->getScheduler()->schedule(
		cocos2d::ccSchedulerFunc( std::bind(&Polimorf::Update,this)),
		this, refreshRate, 0, "MainPoliformUpdate");


	
}


