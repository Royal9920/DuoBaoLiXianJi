#ifndef __GAME_SCENE__
#define __GAME_SCENE__

#include "cocos2d.h"

class game_scene : public cocos2d::Scene
{
public:
	static cocos2d::Scene * createScene(int type, int level);
private:

};

#endif