#pragma once

namespace Crystal
{
	typedef enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0            = 0,
		Button1            = 1,
		Button2            = 2,
		Button3            = 3,
		Button4            = 4,
		Button5            = 5,
		Button6            = 6,
		Button7            = 7,

		ButtonLast         = Button7,
		ButtonLeft         = Button0,
		ButtonRight        = Button1,
		ButtonMiddle       = Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

// From glfw3.h
#define CR_MOUSE_BUTTON_1         ::Crystal::MouseButtonEvent::Button0
#define CR_MOUSE_BUTTON_2         ::Crystal::MouseButtonEvent::Button1
#define CR_MOUSE_BUTTON_3         ::Crystal::MouseButtonEvent::Button2
#define CR_MOUSE_BUTTON_4         ::Crystal::MouseButtonEvent::Button3
#define CR_MOUSE_BUTTON_5         ::Crystal::MouseButtonEvent::Button4
#define CR_MOUSE_BUTTON_6         ::Crystal::MouseButtonEvent::Button5
#define CR_MOUSE_BUTTON_7         ::Crystal::MouseButtonEvent::Button6
#define CR_MOUSE_BUTTON_8         ::Crystal::MouseButtonEvent::Button7
#define CR_MOUSE_BUTTON_LAST      ::Crystal::MouseButtonEvent::ButtonLast
#define CR_MOUSE_BUTTON_LEFT      ::Crystal::MouseButtonEvent::ButtonLeft
#define CR_MOUSE_BUTTON_RIGHT     ::Crystal::MouseButtonEvent::ButtonRight
#define CR_MOUSE_BUTTON_MIDDLE    ::Crystal::MouseButtonEvent::ButtonMiddle