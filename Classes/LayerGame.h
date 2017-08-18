#ifndef __LayerGame_H__
#define __LayerGame_H__

#include "Util.h"
#include "LayerModel.h"
#include "LayerAI.h"
#include "LayerCtrl.h"

/* 026. ”Œœ∑≥°æ∞ */
class LayerGame : public Layer
{
public:
	CREATE_FUNC(LayerGame);

	bool init();

	LayerModel*		_model;
	LayerAI*		_ai;
	LayerCtrl*		_ctrl;
    
    void addCtrl();
    void moveLeft(CCObject*);
    void moveRight(CCObject*);
    void Jump(CCObject*);
    void addJumpFireMenuCtrl();
    CCTexture2D* _textureDirNone;
    CCTexture2D* _textureDirLeft;
    CCTexture2D* _textureDirRight;
    CCSprite* _menuShow;
};

#endif

