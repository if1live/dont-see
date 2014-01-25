#pragma once

enum Keys
{
	KeyW = 1 << 0,
	KeyA = 1 << 1,
	KeyS = 1 << 2,
	KeyD = 1 << 3,
};

class KeyboardDevice
{
public:
	static KeyboardDevice* sharedDirector() {
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
	m_keys = currentKeys;
}
