#pragma once

enum Keys
{
	KeyW = 1 << 0,
	KeyA = 1 << 1,
	KeyS = 1 << 2,
	KeyD = 1 << 3,
	Key1 = 1 << 4,	// for debugging
	Key2 = 1 << 5,	// for clipping
	KeyLButton = 1 << 6,
	KeyRButton = 1 << 7,
};

class KeyboardDevice
{
public:
	static KeyboardDevice* sharedDevice() {
		static KeyboardDevice device;
		return &device;
	}

	KeyboardDevice()
		: m_keys(0) {}

	void Update();

	int GetKeys() const {
		return m_keys;
	}

private:
	int m_keys;
};

inline void KeyboardDevice::Update() {
	int currentKeys = 0;
	if (GetAsyncKeyState('W') & 0x8000) currentKeys |= KeyW;
	if (GetAsyncKeyState('A') & 0x8000) currentKeys |= KeyA;
	if (GetAsyncKeyState('S') & 0x8000) currentKeys |= KeyS;
	if (GetAsyncKeyState('D') & 0x8000) currentKeys |= KeyD;
	if (GetAsyncKeyState('1') & 0x8000) currentKeys |= Key1;
	if (GetAsyncKeyState('2') & 0x8000) currentKeys |= Key2;
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) currentKeys |= KeyLButton;
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000) currentKeys |= KeyRButton;
	m_keys = currentKeys;
}
