#pragma once
#include "Include.h"

#define CELL_MAX_LIFE_CYCLES	50
#define CELL_MIN_LIFE_CYCLES	20
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
	bool isDestroyed;

public:
		Cell(cocos2d::Point location)
			:location(location), shape(nullptr), isDestroyed(false)
		{}
	virtual void Create()=0;
	bool IsDestroyed();
	void Destroy();
	void InstDestroy();
	~Cell();

};




class CellShell
	:public Cell
{

public:
	CellShell(cocos2d::Point location)
		: Cell(location)
	{
		this->isDestroyed = false;
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
	cocos2d::Action* life;
	int lastShape;
	std::list<std::unique_ptr<Cell>> cell_list;


	void Update();

	void ChangeShapeRandom();
	void ClearUnusedPtrs();
	
	int RandNewShapeID(int max);
	void DestroySelf();

public:
	CellSpawner(cocos2d::Point location)
		: cicles_(0), location(location), lastShape(-1), life(nullptr)
	{
		Init();
	};

	void Init();
};


