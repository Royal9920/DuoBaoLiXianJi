#include "small_choose_layer.h"
#include "big_choose_scene.h"
#include "game_scene.h"

using namespace cocos2d;

#include"cocostudio/CocoStudio.h"
using namespace cocostudio::timeline;

#include "ui/CocosGUI.h"

bool small_choose_layer::init(){
	if (!Layer::init())
	{
		return false;
	}
	this->rootnode = CSLoader::createNode("res/cs_ui/small_choose_layer.csb");

	return true;
}

void small_choose_layer::init_layer_view(int type){
	if (type == 1)
	{
		auto sp_map_forest = rootnode->getChildByName("sp_map_forest");
		sp_map_forest->setOpacity(255);
	}
	else if (type == 2)
	{
		auto sp_map_desert = rootnode->getChildByName("sp_map_desert");
		sp_map_desert->setOpacity(255);
	}
	else if (type == 3)
	{
		auto sp_map_iceland = rootnode->getChildByName("sp_map_iceland");
		sp_map_iceland->setOpacity(255);
	}
	for (int i = 2; i < 31; i++)
	{
		char btn_name[128] = {};
		sprintf(btn_name, "Button_%d", i);
		auto btn_level = (cocos2d::ui::Button *)rootnode->getChildByName(btn_name);
		btn_level->setEnabled(false);
	}

	this->addChild(rootnode);
}

void small_choose_layer::change_scene_view(int type, int level) {
	if (level == 0)
	{
		auto local_big_choose_scene = big_choose_scene::createScene();
		Director::getInstance()->replaceScene(local_big_choose_scene);
	}
	else {
		auto local_game_scene = game_scene::createScene(type, level);
		Director::getInstance()->replaceScene(local_game_scene);
	}
}

void small_choose_layer::init_func_model(int type){
	auto btn_back = (cocos2d::ui::Button *)rootnode->getChildByName("btn_back");
	btn_back->addClickEventListener([=](Ref*){
		this->change_scene_view(type, 0);
	});
	for (int i = 1; i < 31; i++)
	{
		char btn_name[128] = {};
		sprintf(btn_name, "Button_%d", i);
		auto btn_level = (cocos2d::ui::Button*)rootnode->getChildByName(btn_name);
		btn_level->addTouchEventListener([=](Ref* ref, cocos2d::ui::Widget::TouchEventType type1){
			auto btn = (cocos2d::ui::Button*)ref;
			switch (type1)
			{
			case cocos2d::ui::Widget::TouchEventType::BEGAN:
				btn->setSize(Size(152*1.1, 152*1.1));
				break;
			case cocos2d::ui::Widget::TouchEventType::MOVED:
				break;
			case cocos2d::ui::Widget::TouchEventType::ENDED:
				btn->setSize(Size(152*1, 152*1));
				this->change_scene_view(type, i);
				break;
			case cocos2d::ui::Widget::TouchEventType::CANCELED:
				btn->setSize(Size(152*1, 152*1));
				break;
			default:
				break;
			}
		});
	}
}
