#pragma once
#pragma execution_character_set("utf-8")

#ifndef __SMALL_CHOOSE_LAYER__
#define __SMALL_CHOOSE_LAYER__

#include "cocos2d.h"

class small_choose_layer : public cocos2d::Layer
{
public:
	Node * rootnode;

	virtual bool init();

	void init_layer_view(int type);

	void change_scene_view(int type, int level);

	void init_func_model(int type);

	CREATE_FUNC(small_choose_layer);
private:

};

#endif