#include "game_scene.h"
#include "game_layer.h"

cocos2d::Scene * game_scene::createScene(int type, int level){
	auto local_game_scene = cocos2d::Scene::create();
	auto local_game_layer = game_layer::create();
	local_game_layer->init_layer_view(type, level);
	local_game_scene->addChild(local_game_layer);

	return local_game_scene;
}