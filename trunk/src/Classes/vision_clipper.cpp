#include "stdafx.h"
#include "vision_clipper.h"

using namespace cocos2d;


cocos2d::CCScene *VisionClipper::testScene()
{
	CCScene *scene = CCScene::create();
	
	CCSprite *sprite = CCSprite::create("texture/HelloWorld.png");
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint center(winSize.width / 2, winSize.height / 2);
	sprite->setScale(3);

	CCClippingNode *clipper = VisionClipper::create();
	clipper->setPosition(center);
	clipper->addChild(sprite);

	scene->addChild(clipper);
	//scene->addChild(sprite);
	sprite->setPosition(center);

	return scene;

}

CCClippingNode *VisionClipper::create()
{
	CCNode *stencil = shape();

	CCClippingNode *clipper = CCClippingNode::create();
    clipper->setStencil(stencil);
    return clipper;
}


CCDrawNode* VisionClipper::shape()
{
	const int circlePoint = 16;
	const float innerRadius = 50;
	const float outerRadius = 100;

    CCDrawNode *shape = CCDrawNode::create();

	std::vector<CCPoint> pointList;
	for(int i = 1 ; i < circlePoint - 1 ; i++) {
		float segment = 360.0f / circlePoint;
		float angle = segment * i + 90;
		float rad = CC_DEGREES_TO_RADIANS(angle);
		float sinVal = sin(rad);
		float cosVal = cos(rad);
		float x = cosVal * innerRadius;
		float y = sinVal * innerRadius;

		pointList.push_back(ccp(x, y));
	}

    static ccColor4F green = {0, 1, 0, 1};
	shape->drawPolygon(pointList.data(), pointList.size(), green, 0, green);
    return shape;
}
