#pragma once
#include "cocos2d.h"
#include <stdlib.h>
#include <vector>
#include<list>

#define BORDER_HEIGHT 1040
#define BORDER_WIDTH 1880
#define BORDER_Y_ORIGIN 40
#define BORDER_X_ORIGIN 40

#define VERSION 0.87

#define NUMBER_OF_POLIMORFS 26

typedef cocos2d::RandomHelper Random;

class GameBridge
{
private:
	cocos2d::Node* mainScene;

public:
	GameBridge() {};

	GameBridge(const GameBridge&) = delete;


	cocos2d::Node* GetMainScene() { return mainScene; };
	void SetMainScene(cocos2d::Node* mainScene) { this->mainScene = mainScene; };


	static GameBridge& getInstance()
	{
		static GameBridge instance;
		return instance;
	}

};

