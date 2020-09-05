/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include <iomanip>

USING_NS_CC;

Scene* MainScene::createScene()
{
    return MainScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	

	runBackgroundColorAnimation();


	std::string title = "Polimorf v" + std::to_string(VERSION);
    auto label = Label::createWithTTF(title.substr(0,13), "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }





	
	GameBridge::getInstance().SetMainScene(this);
	

	for (int i = 0; i < NUMBER_OF_POLIMORFS; i++)
	{
		polimorf.push_front(Polimorf());
		polimorf.front().Run();
	}



    return true;
}

void MainScene::runBackgroundColorAnimation()
{
	auto screen_size = Director::getInstance()->getVisibleSize();
	cocos2d::Color4B bg_color = Color4B(50, 50, 50,255);
	
	cocos2d::LayerColor* screen_layer = LayerColor::create(
		bg_color,
		screen_size.width,
		screen_size.height);
	
	this->addChild(screen_layer,0);

	screen_layer->runAction(RepeatForever::create(
		Sequence::create(
			DelayTime::create(4),
			TintTo::create(1.5, Color3B(67,67,67)),
			TintTo::create(1.5, Color3B(50, 50, 50)),
			nullptr )));
			
	bg_color = Color4B::BLUE;
}
