#pragma once
#pragma execution_character_set("utf-8")

#ifndef __DUOBAO_LOGIN_LAYER__
#define __DUOBAO_LOGIN_LAYER__

#include"cocos2d.h"

class duobao_login_layer : public cocos2d::Layer
{
public:
	Node * rootnode;

	virtual bool init();

	CREATE_FUNC(duobao_login_layer);

	//view  ²ã´úÂë
	void init_layer_view();

	void change_scene_view();

	//model
	void init_func_model();

	//CTROL
	void ctr_();
private:

};

#endif