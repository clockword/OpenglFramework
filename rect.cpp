#include "rect.h"

Rect::Rect()
{
	Left = 0.0f;
	Right = 0.0f;
	Top = 0.0f;
	Bottom = 0.0f;
}

Rect::Rect(float left, float right, float top, float bottom)
{
	Left = left;
	Right = right;
	Top = top;
	Bottom = bottom;
}
