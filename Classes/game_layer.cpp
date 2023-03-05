#include "game_layer.h"
#include "duobao_login_scene.h"
#include "game_scene.h"

//using namespace cocos2d;

#include "cocostudio/CocoStudio.h"
using namespace cocostudio::timeline;

#include "ui/CocosGUI.h"

bool game_layer::init(){
	if (!Layer::init())
	{
		return false;
	}
	// 开启帧定时器
	this->scheduleUpdate();

	rootnode = CSLoader::createNode("res/cs_ui/game_layer.csb");

	this->init_func_model();

	return true;
}

void game_layer::init_layer_view(int type, int level){
	this->type = type;
	this->level = level;
	char map_name[128] = {};
	//sprintf(map_name, "Map/Map%d_%d.tmx", type, level);
	sprintf(map_name, "Map/Map%d_%d.tmx", type, 10);
	tmx_map = TMXTiledMap::create(map_name);
	this->addChild(tmx_map);

	key = Sprite::create("key.png");
	key->setAnchorPoint(Vec2(0, 0));
	this->addChild(key);
	auto object1 = tmx_map->getObjectGroup("object1");
	auto key_pos = object1->getObject("key");
	float key_x = key_pos["x"].asFloat();
	float key_y = key_pos["y"].asFloat();
	key->setPosition(key_x, key_y);

	
	exit = Sprite::create("trandoor/exit_1.png");
	exit->setScale(70.0 / 440.0);
	exit->setAnchorPoint(Vec2(0, 0));
	this->addChild(exit);
	auto exit_pos = object1->getObject("exit");
	float exit_x = exit_pos["x"].asFloat();
	float exit_y = exit_pos["y"].asFloat();
	exit->setPosition(exit_x, exit_y);
	Animation * exit_ani = Animation::create();
	for (int i = 1; i < 12; i++)
	{
		char exit_szName[128] = {};
		sprintf(exit_szName, "trandoor/exit_%d.png", i);
		exit_ani->addSpriteFrameWithFileName(exit_szName);
	}
	exit_ani->setDelayPerUnit(0.1);
	exit_ani->setRestoreOriginalFrame(true);
	auto exit_animate = Animate::create(exit_ani);
	auto exit_repeatForever = RepeatForever::create(exit_animate);
	exit->runAction(exit_repeatForever);

	if (type == 1)
	{
		auto sp_forest_box = rootnode->getChildByName("sp_forest_box");
		sp_forest_box->setOpacity(255);

		box[0] = Sprite::create("box1.png");
		box[1] = Sprite::create("box1.png");
		box[2] = Sprite::create("box1.png");
	}
	else if (type == 2)
	{
		auto sp_desert_box = rootnode->getChildByName("sp_desert_box");
		sp_desert_box->setOpacity(255);

		box[0] = Sprite::create("box0.png");
		box[1] = Sprite::create("box0.png");
		box[2] = Sprite::create("box0.png");
	}
	else if (type == 3)
	{
		auto sp_iceland_box = rootnode->getChildByName("sp_iceland_box");
		sp_iceland_box->setOpacity(255);

		box[0] = Sprite::create("box2.png");
		box[1] = Sprite::create("box2.png");
		box[2] = Sprite::create("box2.png");
	}
	for (int i = 0; i < 3; i++)
	{
		box[i]->setAnchorPoint(Vec2(0, 0));
		this->addChild(box[i]);
		auto object2 = tmx_map->getObjectGroup("object2");
		char box_name[128] = {};
		sprintf(box_name, "%s%i", "box_", i + 1);
		auto box_pos = object2->getObject(box_name);
		float box_x = box_pos["x"].asFloat();
		float box_y = box_pos["y"].asFloat();
		box[i]->setPosition(box_x, box_y);
	}

	role = Sprite::create("player/PlayerStop.png");
	role->setScale(70.0 / 96.0);
	role->setAnchorPoint(Vec2(0, 0));
	this->addChild(role);
	auto object0 = tmx_map->getObjectGroup("object0");
	auto player = object0->getObject("player");
	float role_x = player["x"].asFloat();
	float role_y = player["y"].asFloat();
	role->setPosition(role_x, role_y);

	this->addChild(rootnode);

	this->init_monster_obj_view(type);
}

void game_layer::change_scene_view(int x){
	if (x == 0)
	{
		auto local_login_scene = duobao_login_scene::createScene();
		Director::getInstance()->replaceScene(local_login_scene);
	}
	else if (x == 1)
	{
		auto local_game_scene = game_scene::createScene(this->type, this->level);
		Director::getInstance()->replaceScene(local_game_scene);
	}
}

void game_layer::role_move_view(int direction, Vec2 target_pos) {
	char * dir_name = "";
	if (direction == 8)
	{
		dir_name = "player/PlayerUp_";
	}
	else if (direction == 2)
	{
		dir_name = "player/PlayerDown_";
	}
	else if (direction == 4)
	{
		dir_name = "player/PlayerLeft_";
	}
	else if (direction == 6)
	{
		dir_name = "player/PlayerLeft_";
	}
	Animation * role_ani = Animation::create();
	for (int i = 0; i < 4; i++)
	{
		char role_szName[128] = {};
		sprintf(role_szName, "%s%d.png",dir_name, i);
		role_ani->addSpriteFrameWithFileName(role_szName);
	}
	role_ani->setDelayPerUnit(0.1);
	role_ani->setRestoreOriginalFrame(true);
	auto role_animate = Animate::create(role_ani);
	auto role_repeatForever = RepeatForever::create(role_animate);
	
	auto move_time = this->get_move_time_model(target_pos);

	auto role_move_to = MoveTo::create(move_time, target_pos);
	role_move_to->setTag(66);
	if (role->getActionByTag(66) == NULL)
	{
		role->stopAllActions();
		role->setFlipX(false);
		role->runAction(role_repeatForever);
		if (direction == 6)
		{
			role->setFlipX(true);
		}
		role->runAction(role_move_to);
	}
}

void game_layer::init_monster_obj_view(int type){
	//获取树精怪物（定点怪物）
	auto object3 = tmx_map->getObjectGroup("object3");
	//获取哥布林怪物（移动怪物）
	auto object4 = tmx_map->getObjectGroup("object4");

	if (object3 != NULL)
	{
		//有树精怪物
		for (int i = 0; i < 3; i++)
		{
			char trap_name[32] = {};
			sprintf(trap_name, "trap_%i", i);
			auto trap_obj = object3->getObject(trap_name);
			if (trap_obj.size() != 0)
			{
				//有怪物
				Sprite * sp;
				if (type == 1)
				{
					sp = Sprite::create("forest_trap.png");
					sp->setScale(0.8);
				}
				else if (type == 2)
				{
					sp = Sprite::create("desert_trap.png");
					sp->setScale(1.2);
				}
				else if (type == 3)
					sp = Sprite::create("iceland_trap.png");
				this->addChild(sp);
				trap_arr.push_back(sp);
				auto x = trap_obj["x"].asFloat();
				auto y = trap_obj["y"].asFloat();
				sp->setPosition(x, y);
				sp->setAnchorPoint(Vec2(0, 0));

				auto scale_by_1 = ScaleBy::create(0.5, 1.6);
				auto scale_by_2 = ScaleBy::create(0.5, 0.625);
				auto seq = Sequence::create(scale_by_1, scale_by_2, NULL);
				auto act = RepeatForever::create(seq);
				sp->runAction(act);
			}
		}
	}
	if (object4 != NULL)
	{
		//有哥布林怪物
		for (int i = 0; i < 3; i++)
		{
			char monster_name[32] = {};
			sprintf(monster_name, "monster_%i", i);
			auto monster_obj = object4->getObject(monster_name);
			if (monster_obj.size() != 0)
			{
				//有怪物
				Sprite * sp;
				if (type == 1)
				{
					sp = Sprite::create("Monster/gebulin_down1.png");
				}
				else if (type == 2)
				{
					sp = Sprite::create("Monster/feiniao_down1.png");
				}
				else if (type == 3)
					sp = Sprite::create("Monster/bjx_down1.png");
				sp->setScale(0.7);
				this->addChild(sp);
				monster_arr.push_back(sp);
				auto x = monster_obj["x"].asFloat();
				auto y = monster_obj["y"].asFloat();
				sp->setPosition(x, y);
				sp->setAnchorPoint(Vec2(0, 0));
				//获取运动方向
				auto dirX = monster_obj["dirX"].asInt();
				auto dirY = monster_obj["dirY"].asInt();
				auto dis = monster_obj["dis"].asInt();

				auto target_dir1 = Vec2(0, 0);
				auto target_dir2 = Vec2(0, 0);

				auto dir1 = 0;
				auto dir2 = 0;
				if (dirX == 1)
				{
					//x 正
					target_dir1.x = dis * 70;
					target_dir2.x = -dis * 70;
					dir1 = 6;
					dir2 = 4;
				}
				else if (dirX == -1)
				{
					//x 负
					target_dir1.x = -dis * 70;
					target_dir2.x = dis * 70;
					dir1 = 4;
					dir2 = 6;
				}
				else if (dirY == 1)
				{
					//y 正
					target_dir1.y = dis * 70;
					target_dir2.y = -dis * 70;
					dir1 = 8;
					dir2 = 2;
				}
				else if (dirY == -1)
				{
					//y 负
					target_dir1.y = -dis * 70;
					target_dir2.y = dis * 70;
					dir1 = 2;
					dir2 = 8;
				}

				auto cc_call_func1 = CCCallFunc::create([=](){
					this->gbl_ani_view(dir1, type, sp);
				});
				auto cc_call_func2 = CCCallFunc::create([=](){
					this->gbl_ani_view(dir2, type, sp);
				});
				auto seq = Sequence::create(cc_call_func1, MoveBy::create(dis / 2, target_dir1), cc_call_func2, MoveBy::create(dis / 2, target_dir2), NULL);
				auto act = RepeatForever::create(seq);
				sp->runAction(act);
			}
		}
	}
}

void game_layer::gbl_ani_view(int dir, int type, Sprite * gbl){
	auto ani = Animation::create();
	char * dir_name = "";
	switch (dir)
	{
	case 8:
		if (type == 1)
			dir_name = "Monster/gebulin_up";
		else if (type == 2)
			dir_name = "Monster/feiniao_up";
		else if (type == 3)
			dir_name = "Monster/bjx_up";
		break;
	case 2:
		if (type == 1)
			dir_name = "Monster/gebulin_down";
		else if (type == 2)
			dir_name = "Monster/feiniao_down";
		else if (type == 3)
			dir_name = "Monster/bjx_down";
		break;
	case 4:
		if (type == 1)
			dir_name = "Monster/gebulin_left";
		else if (type == 2)
			dir_name = "Monster/feiniao_left";
		else if (type == 3)
			dir_name = "Monster/bjx_left";
		break;
	case 6:
		if (type == 1)
			dir_name = "Monster/gebulin_right";
		else if (type == 2)
			dir_name = "Monster/feiniao_right";
		else if (type == 3)
			dir_name = "Monster/bjx_right";
		break;
	}
	for (int i = 1; i < 5; i++)
	{
		char szName[128] = {};
		sprintf(szName, "%s%i.png", dir_name, i);
		ani->addSpriteFrameWithFileName(szName);
	}
	ani->setDelayPerUnit(0.1);
	ani->setRestoreOriginalFrame(true);
	
	auto act = RepeatForever::create(Animate::create(ani));
	act->setTag(387);
	gbl->stopActionByTag(387);
	gbl->runAction(act);
}

void game_layer::init_func_model(){
	auto btn_restart = (cocos2d::ui::Button *)rootnode->getChildByName("btn_restart");
	btn_restart->addClickEventListener([=](Ref*){
		this->change_scene_view(1);
	});

	auto btn_back = (cocos2d::ui::Button *)rootnode->getChildByName("btn_back");
	btn_back->addClickEventListener([=](Ref*){
		this->change_scene_view(0);
	});

	auto event_lis_touch_began = EventListenerTouchOneByOne::create();
	event_lis_touch_began->onTouchBegan = [=](Touch * touch, Event * event){
		auto touch_pos = touch->getLocation();
		auto role_pos = role->getPosition();
		float val_x, val_y;
		auto target_pos = Vec2(0, 0);
		if (touch_pos.x - role_pos.x < 0)
			val_x = -(touch_pos.x - role_pos.x);
		else
			val_x = touch_pos.x - role_pos.x;
		if (touch_pos.y - role_pos.y < 0)
			val_y = -(touch_pos.y - role_pos.y);
		else
			val_y = touch_pos.y - role_pos.y;
		if (val_x >= val_y)
		{
			if (touch_pos.x >= role_pos.x)
			{
				target_pos = this->get_target_pos_model(6);
				this->role_move_view(6, target_pos);
			}
			else
			{
				target_pos = this->get_target_pos_model(4);
				this->role_move_view(4, target_pos);
			}
		}
		else
		{
			if (touch_pos.y >= role_pos.y)
			{
				target_pos = this->get_target_pos_model(8);
				this->role_move_view(8, target_pos);
			}
			else
			{
				target_pos = this->get_target_pos_model(2);
				this->role_move_view(2, target_pos);
			}
		}
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(event_lis_touch_began, this);
}

Vec2 game_layer::get_target_pos_model(int direction){
	auto walk_layer = tmx_map->getLayer("walkLayer");
	auto pos = role->getPosition();
	Vec2 dis = Vec2(0, 0);
	switch (direction)
	{
	case 8:
		//上
		dis.y--;
		break;
	case 2:
		//下
		dis.y++;
		break;
	case 4:
		//左
		dis.x--;
		break;
	case 6:
		//右
		dis.x++;
		break;
	}
	auto wp_pos = this->cover_to_wp_model(pos);
	while (true)
	{
		wp_pos += dis;
		auto gid = walk_layer->tileGIDAt(wp_pos);
		if (gid != 0)
		{
			wp_pos -= dis;
			auto target_pos = this->cover_to_descartes_model(wp_pos);
			return (target_pos);
		}
	}
}

Vec2 game_layer::cover_to_wp_model(Vec2 pos){
	auto pos1 = Vec2(pos.x / 70, pos.y / 70);
	auto pos2 = Vec2(pos1.x, 9 - pos1.y);
	return pos2;
}

Vec2 game_layer::cover_to_descartes_model(Vec2 pos){
	auto pos1 = Vec2(pos.x, 9 - pos.y);
	auto pos2 = Vec2(pos1.x * 70, pos1.y * 70);
	return pos2;
}

float game_layer::get_move_time_model(Vec2 target_pos)
{
	auto pos = role->getPosition();
	if (pos.x == target_pos.x)
	{
		if (pos.y >= target_pos.y)
			return ((pos.y - target_pos.y) / 700);
		else
			return ((target_pos.y - pos.y) / 700);
	}
	else
	{
		if (pos.x >= target_pos.x)
			return ((pos.x - target_pos.x) / 700);
		else
			return ((target_pos.x - pos.x) / 700);
	}
}

bool game_layer::player_collision(Sprite * obj){
	if (obj != NULL){
		float xDis = role->getPosition().x - obj->getPosition().x;
		float yDis = role->getPosition().y - obj->getPosition().y;
		if (abs(xDis) < 40 && abs(yDis) < 40){
			return true;
		}
	}
	return false;
}

void game_layer::update(float dt){
	//碰撞检测
	auto trap_size = trap_arr.size();
	for (int i = 0; i < trap_size; i++){
		if (this->player_collision(trap_arr.at(i))){
			auto local_game_scene = game_scene::createScene(this->type, this->level);
			Director::getInstance()->replaceScene(local_game_scene);
		}	
	}
	auto monster_size = monster_arr.size();
	for (int i = 0; i < monster_size; i++)
	{
		if (this->player_collision(monster_arr.at(i))){
			auto local_game_scene = game_scene::createScene(this->type, this->level);
			Director::getInstance()->replaceScene(local_game_scene);
		}
	}
}