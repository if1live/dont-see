#pragma once

class MouseDevice
{
public:
	static MouseDevice* sharedDevice() {
		static MouseDevice device;
		return &device;
	}

	MouseDevice() {
#ifdef _DEBUG
		m_hwnd = FindWindow(0, L"HelloCpp - 1024x768 - 1.00");
#else
		m_hwnd = FindWindow(0, L"HelloCpp");
#endif
	}

	void Update();

	inline POINT GetMousePos() const
	{
		return m_point;
	}

private:
	HWND m_hwnd;
	POINT m_point;
};

inline void MouseDevice::Update() {
	GetCursorPos(&m_point);
	//CCLOG("CursorPos:%d, %d", m_point.x, m_point.y);
	ScreenToClient(m_hwnd, &m_point);
	//CCLOG("RelativePos:%d, %d", m_point.x, abs(768 - m_point.y));

	m_point.x = m_point.x - (SCREEN_WIDTH / 2);
	m_point.y = abs(768 - m_point.y) - (SCREEN_HEIGHT / 2);

	//CCLOG("CalcPos:%d, %d", m_point.x, m_point.y);
}
