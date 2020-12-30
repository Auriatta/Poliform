#include "Cell.h"

void CellSpawner::Update()
{

	ClearUnusedPtrs();
	ChangeShapeRandom();
	

	cicles_--;
	if (cicles_ <= 0)
	{
		DestroySelf();
	}
}

void CellSpawner::ChangeShapeRandom()
{
	if(!cell_list.empty() && !cell_list.front()->IsDestroyed())
	cell_list.front()->Destroy();
	
	const int maxRandValueForSwitch = 2;
	switch (static_cast<CellShapes>(RandNewShapeID(maxRandValueForSwitch)))
	{

	case CellShapes::shell:
		cell_list.push_back(std::make_unique<CellShell>(CellShell(location)));
		break;

	case CellShapes::strike:
		cell_list.push_back(std::make_unique<CellStrike>(CellStrike(location)));
		break;


	case CellShapes::open:
		cell_list.push_back(std::make_unique<CellOpen>(CellOpen(location)));
		break;

	default:
		cell_list.push_back(std::make_unique<CellOpen>(CellOpen(location)));
		break;
	}
	
	if(cell_list.front() && !cell_list.front()->IsDestroyed())
		cell_list.front()->Create();

}

void CellSpawner::ClearUnusedPtrs()
{
	if (!cell_list.empty())
	{
		std::list<std::unique_ptr<Cell>>::iterator it;
		for (it = cell_list.begin(); it != cell_list.end(); it++)
		{
			if (!(*it))
				cell_list.erase(it);
		}
	}
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


bool Cell::IsDestroyed()
{
	return isDestroyed;
}

void Cell::Destroy()
{
	if (shape != nullptr && !isDestroyed&& shape->getNumberOfRunningActions()==0)
	{
		isDestroyed = true;
		shape->runAction(cocos2d::Sequence::create(cocos2d::FadeOut::create(1),
			cocos2d::CallFunc::create([this]() {
				if (shape != nullptr)
				{
					shape->clear();
					shape->cleanup();
					getCurrentScene()->removeChild(shape);
					shape = nullptr;
					this->~Cell();
				}
				}),
			nullptr));
	}
}

Cell::~Cell()
{
	if (shape != nullptr)
	{
		shape->clear();
		shape->cleanup();
		shape->stopAllActions();
		getCurrentScene()->removeChild(shape);
		shape = nullptr;
	}
}



void CellShell::Create()
{
	const int size = 30;
	cocos2d::Point verties[4] = {
		cocos2d::Vec2(0,0), 
		cocos2d::Vec2(0,(-size)),
		cocos2d::Vec2(size,(-size)), 
		cocos2d::Vec2(size,0) };
	Cell::shape = cocos2d::DrawNode::create();

	cocos2d::Color3B color;
	if (Random::random_int(0, 1) == 0)
		color = cocos2d::Color3B::WHITE;
	else
		color = cocos2d::Color3B(221, 158, 205);

	const cocos2d::Vec2 newPosition = location +
		cocos2d::Vec2(Random::random_int(-30, 30), Random::random_int(-30, 30));

	Cell::shape->setPosition(newPosition);
	Cell::shape->drawPolygon(verties, 4, cocos2d::Color4F(1,1,1,0), 1.4, cocos2d::Color4F(color));
	
	Cell::getCurrentScene()->addChild(Cell::shape,1);

}






void CellStrike::Create()
{
	const int size = 25;
	cocos2d::Point verties[3] = { 
		cocos2d::Vec2(0,0),
		cocos2d::Vec2((- size),size) ,
		cocos2d::Vec2(size,size) };
	Cell::shape = cocos2d::DrawNode::create();


	cocos2d::Color3B color;
	if (Random::random_int(0, 1) == 0)
		color = cocos2d::Color3B::WHITE;
	else
		color = cocos2d::Color3B(221, 158, 205);

	const cocos2d::Vec2 newPosition = location +
		cocos2d::Vec2(Random::random_int(-25, 25), Random::random_int(-25, 25));

	Cell::shape->setPosition(newPosition);
	Cell::shape->drawPolygon(verties, 3, cocos2d::Color4F(1,1,1,0), 1.4, cocos2d::Color4F(color));
	

	Cell::getCurrentScene()->addChild(Cell::shape, 1);

}






void CellOpen::Create()
{

	Cell::shape = cocos2d::DrawNode::create();

	const int radius = 20;
	const int segments = 4000;


	cocos2d::Color3B color;
	if (Random::random_int(0, 1) == 0)
		color = cocos2d::Color3B::WHITE;
	else
		color = cocos2d::Color3B(221, 158, 205);

	const cocos2d::Vec2 newPosition = location +
		cocos2d::Vec2(Random::random_int(-25, 25), Random::random_int(-25, 25));

	Cell::shape->setLineWidth(3);
	Cell::shape->drawCircle(newPosition, radius, 0, segments, 0,
		cocos2d::Color4F(color));
	Cell::getCurrentScene()->addChild(Cell::shape, 0);

}







