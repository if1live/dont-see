#ifndef __CUSTOM_ACTION__
#define __CUSTOM_ACTION_

class Custom_action
{
public:
	Custom_action();
	~Custom_action();

	void Update(float dt);
	bool TryDecreaseSpecialCount();
	int GetSpecialCount();
	float GetSpecialGap();

	bool TrySpecialSound();
private:
	const int specialCountMax;
	const float specialGapMax;

	int specialCount;
	float specialGap;
	bool specialSoundFlag;
};


#endif