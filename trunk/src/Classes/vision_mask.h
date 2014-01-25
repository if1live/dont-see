#pragma once

class VisionMask : public cocos2d::CCLayer {
public:
	VisionMask();
	virtual ~VisionMask();

	virtual bool init();
	static cocos2d::CCScene *scene();
	
	void enableLight(bool light);

	CREATE_FUNC(VisionMask);

private:
	//캐릭터 자리를 밝게 만들기 위한 마스킹 + 부채꼴
	cocos2d::CCSprite *centerMasking;
	//한쪽 방향이 순간적으로 밝아질때의 마스킹
	cocos2d::CCSprite *lightMasking;

	bool lightEnabled;
};