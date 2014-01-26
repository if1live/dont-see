#pragma once

class Custom_action;

class VisionMask : public cocos2d::CCLayer {
public:
	VisionMask();
	virtual ~VisionMask();

	virtual bool init();
	static cocos2d::CCScene *scene();
	
	void enableLight(bool light);
	void Update();

	CREATE_FUNC(VisionMask);

private:
	//ĳ���� �ڸ��� ��� ����� ���� ����ŷ + ��ä��
	cocos2d::CCSprite *centerMasking;
	//���� ������ ���������� ��������� ����ŷ
	cocos2d::CCSprite *lightMasking;

	bool lightEnabled;

	Custom_action *customAction;
	float lightTime;
};