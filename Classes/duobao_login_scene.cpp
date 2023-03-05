#include "duobao_login_scene.h"
#include "duobao_login_layer.h"

cocos2d::Scene * duobao_login_scene::createScene()
{
	auto local_login_scene = cocos2d::Scene::create();
	auto local_login_layer = duobao_login_layer::create();
	local_login_scene->addChild(local_login_layer);

	return local_login_scene;
}