#include "small_choose_scene.h"
#include "small_choose_layer.h"

cocos2d::Scene * small_choose_scene::createScene(int type){
	auto local_small_choose_scene = cocos2d::Scene::create();
	auto local_small_choose_layer = small_choose_layer::create();
	local_small_choose_layer->init_layer_view(type);
	local_small_choose_layer->init_func_model(type);
	local_small_choose_scene->addChild(local_small_choose_layer);

	return local_small_choose_scene;
}