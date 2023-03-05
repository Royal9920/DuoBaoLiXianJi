#pragma once
#pragma execution_character_set("utf-8")

#ifndef __GAME_LAYER__
#define __GAME_LAYER__

#include "cocos2d.h"
#include <vector>
USING_NS_CC;

class game_layer : public cocos2d::Layer
{
public:
	int type;
	int level;
	Node * rootnode;
	Sprite * role;
	Sprite * key;
	Sprite * exit;
	Sprite * box[3];
	TMXTiledMap * tmx_map;
	std::vector<Sprite*> trap_arr;
	std::vector<Sprite*> monster_arr;

	virtual bool init();

	void init_layer_view(int type, int level);
	void change_scene_view(int x);
	void role_move_view(int direction, Vec2 target_pos);
	void init_monster_obj_view(int type);
	void gbl_ani_view(int dir, int type, Sprite * gbl);

	void init_func_model();
	Vec2 get_target_pos_model(int director);
	Vec2 cover_to_wp_model(Vec2 pos);
	Vec2 cover_to_descartes_model(Vec2 pos);
	float get_move_time_model(Vec2 target_pos);
	//Åö×²¼ì²â
	bool player_collision(Sprite * obj);

	//Ö¡¶¨Ê±Æ÷º¯Êý
	void update(float dt);

	CREATE_FUNC(game_layer);
private:

};

#endif