#pragma once
#include "Include.h"

#define CELL_MAX_LIFE_CYCLES	20
#define CELL_MIN_LIFE_CYCLES	5
#define CELL_SHAPE_CHANGE_DELAY	0.5




class Cell
{
protected:
	cocos2d::Point location;
	cocos2d::DrawNode* shape;

	cocos2d::Node* getCurrentScene() { return GlobalRefs::getInstance().GetMainScene(); };
	void ClearShape();

public:
		Cell(cocos2d::Point location)
			:location(location)
		{}
	virtual void Create()=0;
	virtual void Destroy()=0;

	~Cell() {};
};




class ShapeShell
	:public Cell
{

public:
	ShapeShell(cocos2d::Point location)
		: Cell(location)
	{
		this->location = location;
	}

	void Create();
	void Destroy();

};

class ShapeStrike 
	:public Cell
{
public:
	ShapeStrike(cocos2d::Point location)
		: Cell(location)
	{
		this->location = location;
	}
	void Create();
	void Destroy();

};


class ShapeOpen
	:public Cell
{
public:
	ShapeOpen(cocos2d::Point location)
		:Cell(location)
	{
		this->location = location;
	}
	void Create();
	void Destroy();

};



class CellMutation
{
private:
	cocos2d::Point location;
	int cicles_;
	Cell* cell_;
	cocos2d::Action* life;
	int lastShape;
	

	void ChangeShape();



public:
	CellMutation(cocos2d::Point location)
		: cell_(nullptr), cicles_(0), location(location), lastShape(0)
	{
		Init();
	};

	void Init();
};


