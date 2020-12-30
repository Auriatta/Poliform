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

	Exposition = std::make_unique<TurnEveryPoliform>(
		TurnEveryPoliform(&polimorf, 42, 6, NUMBER_OF_POLIMORFS, 0.23));



    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	

	runBackgroundColorAnimation();


	std::string title = "(https://github.com/Auriatta/Poliform)";
    auto label1 = Label::createWithTTF(title, "fonts/arial.ttf", 24);
	
    if (label1 == nullptr)
    {
        problemLoading("'fonts/fontawesome-webfont.ttf'");
    }
    else
    {
		label1->setOpacity(140);
        // position the label on the center of the screen
        label1->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + 100));
		

        // add the label as a child to this layer
        this->addChild(label1, 1);
    }





	
	GameBridge::getInstance().SetMainScene(this);

	this->scheduleUpdate();
	


    return true;
}

void MainScene::update(float delta)
{
	if(Exposition)
	Exposition->Update(delta);
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

}
