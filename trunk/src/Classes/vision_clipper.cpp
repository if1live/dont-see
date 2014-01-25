#include "stdafx.h"
#include "vision_clipper.h"

using namespace cocos2d;

VisionClipper::VisionClipper()
{
	/*
	CCNode *stencil = this->shape();
    stencil->setPosition( ccp(50, 50) );

	CCClippingNode *clipper = CCClippingNode::create();
    clipper->setAnchorPoint(ccp(0.5, 0.5));
    clipper->setPosition(ccp(s.width / 2 - 50, s.height / 2 - 50) );
    clipper->setStencil(stencil);
    this->addChild(clipper);
	*/
}

VisionClipper::~VisionClipper()
{
}

CCDrawNode* VisionClipper::shape()
{
    CCDrawNode *shape = CCDrawNode::create();
    static CCPoint triangle[3];
    triangle[0] = ccp(-100, -100);
    triangle[1] = ccp(100, -100);
    triangle[2] = ccp(0, 100);

    static ccColor4F green = {0, 1, 0, 1};
    shape->drawPolygon(triangle, 3, green, 0, green);
    return shape;
}

