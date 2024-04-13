#pragma once

#include "engine/core/KeyCode.h"
#include "engine/core/MouseCode.h"
#include "engine/util/Math.h"

class Input
{
public:
	static bool PressedKey(Key key);
	static bool PressedMouseButton(MouseButton mouseButton);
	static Vec2 GetScroll() { return _Scroll; }
	static Vec2 GetMousePosition();
private:
	static Vec2 _Scroll;
	friend class Window;
	friend class Application;
};
