#include "big_choose_layer.h"
#include "duobao_login_scene.h"
#include "small_choose_scene.h"

using namespace cocos2d;

//����cocosStudio��ͷ�ļ�
#include "cocostudio/CocoStudio.h"
using namespace cocostudio::timeline;

#include "ui/CocosGUI.h"

bool big_choose_layer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->init_layer_view();

	this->init_func_model();

	return true;
}

void big_choose_layer::init_layer_view(){
	rootnode = CSLoader::createNode("res/cs_ui/big_choose_layer.csb");
	this->addChild(rootnode);

	//���ӵı���ʵ��
	//��������
	auto sp_rabbit = rootnode->getChildByName("sp_rabbit");
	//����֡����
	Animation * r_ani = Animation::create();
	for (int i = 1; i < 11; i++)
	{
		char szName[128] = {};
		sprintf(szName, "rabbit/rabbit%d.png", i);
		r_ani->addSpriteFrameWithFileName(szName);
	}
	//���û�ͼƬʱ��
	r_ani->setDelayPerUnit(0.1);
	//�Ƿ�ӵ�һ��ͼƬ��ʼ
	r_ani->setRestoreOriginalFrame(true);
	//����animate
	auto r_animate = Animate::create(r_ani);
	//����10�ζ�����10����ƶ�ʱ���ƽ
	auto r_re = Repeat::create(r_animate, 10);
	//�ƶ�
	auto r_moveBy = MoveBy::create(10, Vec2(1734, -300));
	//�ص���������λ��
	CallFunc * r_call = CallFunc::create([=](){
		sp_rabbit->setPosition(-200, 360);
	});
	//������ʮ���֡�������ƶ�������Ϊͬʱ����
	auto r_spawn = Spawn::create(r_re, r_moveBy,NULL);
	//�������ͬʱ�����ͻص�������Ϊ��϶���
	auto r_seq = Sequence::create(r_call, r_spawn,DelayTime::create(3), NULL);
	//�����϶�����Ϊ�����ظ�����
	auto r_act = RepeatForever::create(r_seq);
	//����ִ�ж���
	sp_rabbit->runAction(r_act);

	//��ť������ʵ��
	auto btn_forest = (cocos2d::ui::Button*) this->rootnode->getChildByName("btn_forest");
	auto f_scaleBy_big = ScaleBy::create(2.5, 1.2);
	auto f_scaleBy_small = ScaleBy::create(2.5, 1 / 1.2);
	auto f_fadeTo_shallow = FadeTo::create(2.5, 155);
	auto f_fadeTo_deep = FadeTo::create(2.5, 255);
	auto f_spawn_go = Spawn::create(f_scaleBy_big, f_fadeTo_shallow, NULL);
	auto f_spawn_back = Spawn::create(f_scaleBy_small, f_fadeTo_deep, NULL);
	auto f_seq = Sequence::create(f_spawn_go, f_spawn_back, NULL);
	auto f_act = RepeatForever::create(f_seq);

	auto btn_desert = this->rootnode->getChildByName("btn_desert");
	auto d_scaleBy_big = ScaleBy::create(2.5, 1.2);
	auto d_scaleBy_small = ScaleBy::create(2.5, 1 / 1.2);
	auto d_fadeTo_shallow = FadeTo::create(2.5, 155);
	auto d_fadeTo_deep = FadeTo::create(2.5, 255);
	auto d_spawn_go = Spawn::create(d_scaleBy_big, d_fadeTo_shallow, NULL);
	auto d_spawn_back = Spawn::create(d_scaleBy_small, d_fadeTo_deep, NULL);
	auto d_seq = Sequence::create(d_spawn_go, d_spawn_back, NULL);
	auto d_act = RepeatForever::create(d_seq);

	auto btn_iceland = this->rootnode->getChildByName("btn_iceland");
	auto i_scaleBy_big = ScaleBy::create(2.5, 1.2);
	auto i_scaleBy_small = ScaleBy::create(2.5, 1 / 1.2);
	auto i_fadeTo_shallow = FadeTo::create(2.5, 155);
	auto i_fadeTo_deep = FadeTo::create(2.5, 255);
	auto i_spawn_go = Spawn::create(i_scaleBy_big, i_fadeTo_shallow, NULL);
	auto i_spawn_back = Spawn::create(i_scaleBy_small, i_fadeTo_deep, NULL);
	auto i_seq = Sequence::create(i_spawn_go, i_spawn_back, NULL);
	auto i_act = RepeatForever::create(i_seq);

	btn_forest->runAction(f_act);
	btn_desert->runAction(d_act);
	btn_iceland->runAction(i_act);

}

void big_choose_layer::change_scene_view(int type){
	if (type == 0)
	{
		auto local_login_scene = duobao_login_scene::createScene();
		Director::getInstance()->replaceScene(local_login_scene);
	}
	/*else if (type == 1)
	{
		auto local_small_choose_scene = small_choose_scene::createScene(1);
		Director::getInstance()->replaceScene(local_small_choose_scene);
	}
	else if (type == 2)
	{
		auto local_small_choose_scene = small_choose_scene::createScene(2);
		Director::getInstance()->replaceScene(local_small_choose_scene);
	}
	else if (type == 3)
	{
		auto local_small_choose_scene = small_choose_scene::createScene(3);
		Director::getInstance()->replaceScene(local_small_choose_scene);
	}*/
	auto local_small_choose_scene = small_choose_scene::createScene(type);
	Director::getInstance()->replaceScene(local_small_choose_scene);
}


void big_choose_layer::init_func_model(){
	auto btn_back = (cocos2d::ui::Button *)rootnode->getChildByName("btn_back");
	btn_back->addClickEventListener([=](Ref*){
		this->change_scene_view(0);
	});
	auto btn_forest = (cocos2d::ui::Button *)rootnode->getChildByName("btn_forest");
	btn_forest->addClickEventListener([=](Ref*){
		this->change_scene_view(1);
	});
	auto btn_desert = (cocos2d::ui::Button *)rootnode->getChildByName("btn_desert");
	btn_desert->addClickEventListener([=](Ref*){
		this->change_scene_view(2);
	});
	auto btn_iceland = (cocos2d::ui::Button *)rootnode->getChildByName("btn_iceland");
	btn_iceland->addClickEventListener([=](Ref*){
		this->change_scene_view(3);
	});
}

void big_choose_layer::ctr_(){

}