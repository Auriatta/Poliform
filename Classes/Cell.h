#pragma once
#include "Include.h"

#define CELL_MAX_LIFE_CYCLES	7
#define CELL_MIN_LIFE_CYCLES	3
#define CELL_SHAPE_CHANGE_DELAY	0.4

enum class CellShapes : int
{
	shell = 0,
	open = 1,
	strike = 2

};



class Cell
{
protected:
	cocos2d::Point location;
	cocos2d::DrawNode* shape;

	cocos2d::Node* getCurrentScene() { return GameBridge::getInstance().GetMainScene(); };
	
	void ClearShape();

public:
		Cell(cocos2d::Point location)
			:location(location), shape(nullptr)
		{}
	virtual void Create()=0;
	


	~Cell() { ClearShape(); }
};




class CellShell
	:public Cell
{

public:
	CellShell(cocos2d::Point location)
		: Cell(location)
	{
		this->location = location;
	}

	void Create() override;

};

class CellStrike 
	:public Cell
{
public:
	CellStrike(cocos2d::Point location)
		: Cell(location)
	{
		this->location = location;
	}
	void Create() override;

};


class CellOpen
	:public Cell
{
public:
	CellOpen(cocos2d::Point location)
		:Cell(location)
	{
		this->location = location;
	}
	void Create() override;

};



class CellSpawner
{
private:
	cocos2d::Point location;
	int cicles_;
	std::unique_ptr<Cell> cell;
	cocos2d::Action* life;
	int lastShape;
	

	void Update();

	void ChangeShapeRandom();
	int RandNewShapeID(int max);
	void DestroySelf();

public:
	CellSpawner(cocos2d::Point location)
		: cicles_(0), location(location), lastShape(0), life(nullptr)
	{
		Init();
	};

	void Init();
};


