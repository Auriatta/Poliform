#include "Polimorf.h"

void Polimorf::Generate_Cell()
{
	cocos2d::Point location = cocos2d::Point(
		cocos2d::RandomHelper().random_int<int>(BORDER_X_ORIGIN, BORDER_WIDTH),
		cocos2d::RandomHelper().random_int<int>(BORDER_Y_ORIGIN, BORDER_HEIGHT));


	CellMutation* cell = new CellMutation(location);
}


void Polimorf::Run()
{
	auto creation = cocos2d::RepeatForever::create(cocos2d::Sequence::create(
		cocos2d::DelayTime::create(CELL_SHAPE_CHANGE_DELAY),
		cocos2d::CallFunc::create(std::bind(&Polimorf::Generate_Cell,this)),
		nullptr));
	
	auto scene = GlobalRefs::getInstance().GetMainScene();

	if (scene != nullptr)
		scene->runAction(creation);

	
}
