#pragma once
#include "cocos2d.h"
#include <stdlib.h>
#include<vector>

#define BORDER_HEIGHT 400
#define BORDER_WIDTH 400
#define BORDER_Y_ORIGIN 40
#define BORDER_X_ORIGIN 40

#define VERSION 0.6



class GlobalRefs
{
private:
	cocos2d::Node* mainScene;

public:
	GlobalRefs() {};

	GlobalRefs(const GlobalRefs&) = delete;


	cocos2d::Node* GetMainScene() { return mainScene; };
	void SetMainScene(cocos2d::Node* mainScene) { this->mainScene = mainScene; };


	static GlobalRefs& getInstance()
	{
		static GlobalRefs instance;
		return instance;
	}

};

