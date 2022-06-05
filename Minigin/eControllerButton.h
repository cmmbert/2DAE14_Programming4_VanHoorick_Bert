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
enum class eKeyboardButton
{
	Shift = 0x10,
	Control = 0x11,
	Enter = 0x0D,

	Up = 0x26,
	Right = 0x27,
	Down = 0x28,
	Left = 0x25,


	//https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	A = 0x41,
	B = 0x42,
	C = 0x43,
	D = 0x44,
	E = 0x45,
	F = 0x46,
	//..
	Q = 0x51,
	S = 0x53,
	W = 0x57,
	Z = 0x5A
	//etc...

};

