#include "Cell.h"

void CellSpawner::Update()
{

	
	ChangeShapeRandom();
	

	cicles_ -= 1;
	if (cicles_ <= 0)
	{
		DestroySelf();
	}
}

void CellSpawner::ChangeShapeRandom()
{
	if (cell)
		cell.reset();
	
	
	const int maxRandValueForSwitch = 2;
	switch (static_cast<CellShapes>(RandNewShapeID(maxRandValueForSwitch)))
	{
	case CellShapes::shell:
		cell = std::make_unique<CellShell>(CellShell(location));
		break;

	case CellShapes::strike:
		cell = std::make_unique<CellStrike>(CellStrike(location));
		break;

	case CellShapes::open:
		cell = std::make_unique<CellOpen>(CellOpen(location));
		break;

	default:
		cell = std::make_unique<CellOpen>(CellOpen(location));
		break;
	}

	if(cell)
		cell->Create();

}

int CellSpawner::RandNewShapeID(int max)
{
	cocos2d::RandomHelper rand;
	
	int randIndex = lastShape;
	while (randIndex == lastShape)
	{
		randIndex = rand.random_int<int>(0, max);
	}
	lastShape = randIndex;
	return randIndex;
}

void CellSpawner::DestroySelf()
{
	

	cocos2d::Director::getInstance()->getActionManager()->removeAction(life);
	delete this;
}

void CellSpawner::Init()
{
	if (life == nullptr)
	{
		cicles_ = cocos2d::RandomHelper().random_int<int>(CELL_MIN_LIFE_CYCLES, CELL_MAX_LIFE_CYCLES);

		Update();

		life = cocos2d::CCRepeatForever::create(cocos2d::Sequence::create(
			cocos2d::DelayTime::create(CELL_SHAPE_CHANGE_DELAY),
			cocos2d::CallFunc::create(std::bind(&CellSpawner::Update, this)),
			nullptr));



		auto scene = GameBridge::getInstance().GetMainScene();

		if (scene != nullptr)
			scene->runAction(life);
		else
			delete this;
	}
}


void Cell::ClearShape()
{
	if (shape != nullptr)
	{
		shape->clear();
		shape->cleanup();
		getCurrentScene()->removeChild(shape);
		shape = nullptr;
	}
}



void CellShell::Create()
{
	const int size = 30;
	cocos2d::Point verties[4] = {
		cocos2d::Vec2(location.x,location.y), 
		cocos2d::Vec2(location.x,location.y-size),
		cocos2d::Vec2(location.x+size,location.y-size), 
		cocos2d::Vec2(location.x +size,location.y) };
	Cell::shape = cocos2d::DrawNode::create();

	Cell::shape->drawPolygon(verties, 4, cocos2d::Color4F(1,1,1,0), 1.4, cocos2d::Color4F::BLUE);
	
	Cell::getCurrentScene()->addChild(Cell::shape,1);

}






void CellStrike::Create()
{
	const int size = 25;
	cocos2d::Point verties[3] = { 
		cocos2d::Vec2(location.x,location.y),
		cocos2d::Vec2(location.x - size,location.y + size) ,
		cocos2d::Vec2(location.x + size,location.y + size) };
	Cell::shape = cocos2d::DrawNode::create();

	Cell::shape->drawPolygon(verties, 3, cocos2d::Color4F(1,1,1,0), 1.4, cocos2d::Color4F::RED);
	
	Cell::getCurrentScene()->addChild(Cell::shape, 1);

}






void CellOpen::Create()
{

	Cell::shape = cocos2d::DrawNode::create();

	const int radius = 20;
	const int segments = 30;
	Cell::shape->drawCircle(cocos2d::Point(location.x, location.y), radius, 0, segments, 0, cocos2d::Color4F::GREEN);
	
	Cell::getCurrentScene()->addChild(Cell::shape, 1);

}







