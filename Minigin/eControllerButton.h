#pragma once
enum class eControllerButton
{
	ButtonA = 0x1000,
	ButtonB = 0x2000,
	ButtonX = 0x4000,
	ButtonY = 0x8000,

	DpadUp = 0x0001,
	DpadDown = 0x0002,
	DpadLeft = 0x0004,
	DpadRight = 0x0008,

	Start = 0x0010,
	Back = 0x0020,

	LeftTrigger = 0x0040,
	RightTrigger = 0x0080,

	LeftShoulder = 0x0100,
	RightShoulder = 0x0200,

};

