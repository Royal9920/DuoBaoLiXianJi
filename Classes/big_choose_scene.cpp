#include "big_choose_scene.h"
#include "big_choose_layer.h"

cocos2d::Scene * big_choose_scene::createScene()
{
	auto local_big_choose_scene = cocos2d::Scene::create();
	auto local_big_choose_layer = big_choose_layer::create();
	local_big_choose_scene->addChild(local_big_choose_layer);
	
	return local_big_choose_scene;
}