#include "LayerGame.h"
#include "MenuCtrl.h"
#include "Common.h"
bool LayerGame::init()
{
	Layer::init();

	/* 027. 三个子层，层次图见：
	3.LayerGame的渲染树和继承关系图*/
	_model = LayerModel::create();
	addChild(_model);

	_ai = LayerAI::create(_model);
	addChild(_ai);

//	_ctrl = LayerCtrl::create(_model);
    addCtrl();
//	addChild(_ctrl);

	return true;
}

void LayerGame::addCtrl()
{
    // 控制按钮的背景图片
    CCSprite* sprite = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->addImage("controlUI.png"));
    addChild(sprite);
    sprite->setPosition(ccp(0, 0));
    sprite->setAnchorPoint(ccp(0, 0));
    
    // 显示在菜单位置的纹理
    _textureDirNone = CCTextureCache::sharedTextureCache()->addImage("backKeyImage.png");
    _textureDirLeft = CCTextureCache::sharedTextureCache()->addImage("backKeyLeft.png");
    _textureDirRight = CCTextureCache::sharedTextureCache()->addImage("backKeyRight.png");
    
    _menuShow = CCSprite::createWithTexture(_textureDirNone);
    addChild (_menuShow);
    CCPoint ptmenuShowPos = ccp(70, 50);
    _menuShow->setPosition(ptmenuShowPos);
    
    // 定制菜单：每个帧循环都会触发的菜单
    // 菜单项是透明的，菜单的样式由别的精灵来显示
    MenuCtrl* menu = MenuCtrl::create();
    addChild(menu);
    
    CCSprite* left1 = CCSprite::create();
    CCSprite* left2 = CCSprite::create();
    left1->setContentSize(CCSizeMake(_textureDirNone->getContentSize().width / 2, _textureDirNone->getContentSize().height));
    left2->setContentSize(CCSizeMake(_textureDirNone->getContentSize().width / 2, _textureDirNone->getContentSize().height));
    CCMenuItemSprite* left = CCMenuItemSprite::create(left1, left2, this, menu_selector(LayerGame::moveLeft));
    menu->addChild(left);
    
    CCSprite* right1 = CCSprite::create();
    CCSprite* right2 = CCSprite::create();
    right1->setContentSize(CCSizeMake(_textureDirNone->getContentSize().width / 2, _textureDirNone->getContentSize().height));
    right2->setContentSize(CCSizeMake(_textureDirNone->getContentSize().width / 2, _textureDirNone->getContentSize().height));
    CCMenuItemSprite* right = CCMenuItemSprite::create(right1, right2, this, menu_selector(LayerGame::moveRight));
    menu->addChild(right);
    
    left->setPosition(ccp(ptmenuShowPos.x - winSize.width / 2, ptmenuShowPos.y - winSize.height / 2));
    right->setPosition(ccp(ptmenuShowPos.x - winSize.width / 2, ptmenuShowPos.y - winSize.height / 2));
    Common::moveNode(left, ccp(-_menuShow->getContentSize().width / 4, 0));
    Common::moveNode(right, ccp(_menuShow->getContentSize().width / 4, 0));
    
//    _marioDir = Common::NONE;
    
    // 跳跃，发射子弹，菜单
    addJumpFireMenuCtrl();
}
void LayerGame::addJumpFireMenuCtrl()
{
    CCMenu* menu = CCMenu::create();
    addChild(menu);
    
    CCTexture2D* textureAB_Normal = CCTextureCache::sharedTextureCache()->addImage("AB_normal.png");
    CCTexture2D* textureAB_Select = CCTextureCache::sharedTextureCache()->addImage("AB_select.png");
    CCSprite* jumpNormal = CCSprite::createWithTexture(textureAB_Normal);
    CCSprite* jumpSelect = CCSprite::createWithTexture(textureAB_Select);
    CCMenuItemSprite* jump = CCMenuItemSprite::create(jumpNormal, jumpSelect, this, menu_selector(LayerGame::Jump));
    menu->addChild(jump);
    Common::moveNode(jump, ccp(192, -125));
}
void LayerGame::Jump(CCObject*)
{
    _model->jump();
//    if (_mario->_autoRun) return;
    
//    _mario->jump();
}
void LayerGame::moveLeft(CCObject*)
{
    _menuShow->setTexture(this->_textureDirLeft);
    _model->moveLeft();
//    _marioDir = Common::LEFT;
}

void LayerGame::moveRight(CCObject*)
{
    _menuShow->setTexture(this->_textureDirRight);
    _model->moveRight();
//    _marioDir = Common::RIGHT;
}