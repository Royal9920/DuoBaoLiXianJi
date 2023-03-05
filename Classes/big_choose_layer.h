#pragma once
#pragma execution_character_set("utf-8")

#ifndef __BIG_CHOOSE_LAYER__
#define __BIG_CHOOSE_LAYER__

#include "cocos2d.h"

class big_choose_layer : public cocos2d::Layer
{
public:
	Node * rootnode;

	virtual bool init();

	CREATE_FUNC(big_choose_layer);

	//view ²ã´úÂë
	void init_layer_view();

	void change_scene_view(int type);

	//model
	void init_func_model();

	//CTROL
	void ctr_();
private:

};

#endif