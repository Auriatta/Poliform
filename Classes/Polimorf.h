#pragma once
#include "Cell.h"
#include "Include.h"
#include "AI.h"





class Polimorf
{
private:
	std::unique_ptr<AI> behavior;

	std::vector<std::shared_ptr<CellSpawner>> cell_spawners;


	void Update();
	void Create_Spawner(cocos2d::Point);

	cocos2d::Point getRandomPositionInBordersBox();

public:
	Polimorf()
		: behavior(std::make_unique<AI_Basic>(AI_Basic(getRandomPositionInBordersBox())))
	{
		cell_spawners.clear();

	};


	void Run();

};








