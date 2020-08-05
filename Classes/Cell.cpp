#include "Cell.h"

void CellMutation::ChangeShape()
{
	cocos2d::RandomHelper rand;

	if (cell_ != nullptr)
	{
		cell_->Destroy();
		delete cell_;
		
	}
	
	
	int randIndex = lastShape;
	while (randIndex == lastShape)
	{
		randIndex = rand.random_int<int>(1, 3);
	}
	lastShape = randIndex;



	switch (randIndex)
	{
	case 1:
		cell_ = new ShapeShell(location);
		break;
	case 2:
		cell_ = new ShapeStrike(location);
		break;
	case 3:
		cell_ = new ShapeOpen(location);
		break;
	default:
		cell_ = new ShapeOpen(location);
		break;
	}
	cell_->Create();


	cicles_ -= 1;
	if (cicles_ <= 0)
	{
		cell_->Destroy(); // I need it to make sure that last cell shape is cleaned from screen
		delete cell_;

		cocos2d::Director::getInstance()->getActionManager()->removeAction(life);
		delete this;
	}
}

void CellMutation::Init()
{
	cicles_ = cocos2d::RandomHelper().random_int<int>(CELL_MIN_LIFE_CYCLES, CELL_MAX_LIFE_CYCLES);

	ChangeShape();

	life = cocos2d::CCRepeatForever::create(cocos2d::Sequence::create(
		cocos2d::DelayTime::create(CELL_SHAPE_CHANGE_DELAY),
		cocos2d::CallFunc::create(std::bind(&CellMutation::ChangeShape, this)),
		nullptr));
	


	auto scene = GlobalRefs::getInstance().GetMainScene();
	
	if (scene != nullptr)
		scene->runAction(life);
	else
		delete this;
}






void ShapeShell::Create()
{
	cocos2d::Point verties[4] = {
		cocos2d::Vec2(location.x,location.y), cocos2d::Vec2(location.x,location.y-20),
		cocos2d::Vec2(location.x+20,location.y-20), cocos2d::Vec2(location.x +20,location.y) };
	shape = cocos2d::DrawNode::create();

	shape->drawPolygon(verties, 4, cocos2d::Color4F::BLUE, 1.4, cocos2d::Color4F::BLUE);
	
	Cell::getCurrentScene()->addChild(shape,1);

}

void ShapeShell::Destroy()
{
	Cell::ClearShape();
	
}




void ShapeStrike::Create()
{
	cocos2d::Point verties[3] = { 
		cocos2d::Vec2(location.x,location.y),
		cocos2d::Vec2(location.x - 20,location.y + 20) ,
		cocos2d::Vec2(location.x + 20,location.y + 20) };
	shape = cocos2d::DrawNode::create();

	shape->drawPolygon(verties, 3, cocos2d::Color4F::RED, 1.4, cocos2d::Color4F::RED);
	
	Cell::getCurrentScene()->addChild(shape, 1);

}

void ShapeStrike::Destroy()
{

	Cell::ClearShape();
	
}





void ShapeOpen::Create()
{

	shape = cocos2d::DrawNode::create();

	shape->drawCircle(cocos2d::Point(location.x-10, location.y), 20, 0, 30, 0, cocos2d::Color4F::GREEN);
	
	Cell::getCurrentScene()->addChild(shape, 1);

}

void ShapeOpen::Destroy()
{
	Cell::ClearShape();
}





void Cell::ClearShape()
{
	shape->clear();
	shape->cleanup();
	getCurrentScene()->removeChild(shape);
}
