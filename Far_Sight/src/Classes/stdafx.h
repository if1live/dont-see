#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstdarg>

#include <vector>
#include <string>
#include <set>
#include <map>
#include <memory>
#include <algorithm>



#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

// Windows Header Files:
#include <windows.h>
#include <tchar.h>

// C RunTime Header Files
#include "CCStdC.h"

#include "Box2D/Box2D.h"
#include "cocos2d.h"
#include "../CocosDenshion/include/SimpleAudioEngine.h"

#include "AppMacros.h"

#define PTM_RATIO (32.0f)


#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

// ������ ���� public!
#define protected public
#define private public
#define class struct


#define DEBUG 1