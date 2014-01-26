#ifndef __SOUND_MANAGER__
#define __SOUND_MANAGER__

enum EFFECT_SOUND
{
	EFFECT_DOG,
	EFFECT_SPECIAL_INC,
	EFFECT_MAN_SCREAM,
	EFFECT_TRASH_CRASH,
	EFFECT_WATER,
	EFFECT_STICK,
	EFFECT_GAMEOVER,
	EFFECT_ENDING,
	EFFECT_MAX
};

enum BG_SOUND
{
	BG_TITLE,
	BG_MAIN,
	BG_MAX
};


class SoundManager
{
public:
	static SoundManager* sharedManager();


	SoundManager();
	~SoundManager();

	void PlayEffect(int index);
	void Update(float dt);

	void PlayBG(int index);
private:

	float effectSoundInterval[EFFECT_MAX];
	float effectSoundState[EFFECT_MAX];
	int effectSoundID[EFFECT_MAX];
	char effectSoundFile[EFFECT_MAX][128];


	int bg_index;
};
#endif
