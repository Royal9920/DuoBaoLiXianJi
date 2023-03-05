#include "duobao_login_layer.h"
#include "big_choose_scene.h"

using namespace cocos2d;

//����cocosStudio��ͷ�ļ�
#include "cocostudio/CocoStudio.h"
using namespace cocostudio::timeline;

#include "ui/CocosGUI.h"

bool duobao_login_layer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->init_layer_view();

	this->init_func_model();

	return true;
}

void duobao_login_layer::init_layer_view(){
	rootnode = CSLoader::createNode("res/cs_ui/duobao_login_layer.csb");
	this->addChild(rootnode);

	// �Ȳ���̫������ת���ӽڵ�
	auto sp_sun = rootnode->getChildByName("sp_sun");
	// ʵ����ת
	auto rotateBy = RotateBy::create(120, 360);
	auto refRotateBy = RepeatForever::create(rotateBy);
	sp_sun->runAction(refRotateBy);
}

void duobao_login_layer::change_scene_view(){
	auto local_big_choose_scene = big_choose_scene::createScene();
	Director::getInstance()->replaceScene(local_big_choose_scene);
}

//model�����
void duobao_login_layer::init_func_model(){
	// ��ʼ�� ��ť�¼�

	// �Ȳ��Ұ�ť���ӽڵ�
	auto btn_login = (cocos2d::ui::Button *) rootnode->getChildByName("btn_login");
	btn_login->addClickEventListener([=](Ref*){
		this->change_scene_view();
	});
}

void duobao_login_layer::ctr_(){
	// ��ʼ�� ctr�����
}
