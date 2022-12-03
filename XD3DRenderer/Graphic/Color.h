#pragma once

struct XColor
{
public:
	XColor() = default;

	XColor(float Value)
		:R(Value), G(Value), B(Value), A(Value)
	{}

	XColor(float InR, float InG, float InB, float InA = 1.0f)
		:R(InR), G(InG), B(InB), A(InA)
	{}

public:
	static const XColor Black;
	static const XColor White;
	static const XColor Red;
	static const XColor Green;
	static const XColor Blue;
	static const XColor Yellow;
	static const XColor Cyan;
	static const XColor Magenta;

public:
	float R = 0;
	float G = 0;
	float B = 0;
	float A = 0;
};
