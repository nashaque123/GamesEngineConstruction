#include "Rectangle.h"

Rectangle::Rectangle()
{
}

Rectangle::Rectangle(int w, int h) : right(w), bottom(h)
{
}

Rectangle::~Rectangle()
{
}

//Clips a rectangle's values to the other
void Rectangle::ClipTo(const Rectangle &other)
{
	left = std::max(left, other.left);
	right = std::min(right, other.right);
	top = std::max(top, other.top);
	bottom = std::min(bottom, other.bottom);
}

//Translates rectangle values to x and y position
void Rectangle::Translate(int posX, int posY)
{
	left += posX;
	right += posX;
	top += posY;
	bottom += posY;
}

//Clips triangle to screen
void Rectangle::ClipBlit(const Rectangle &screenRect, Rectangle &textureRect, const int posX, const int posY) const 
{
	textureRect.Translate(posX, posY);
	textureRect.ClipTo(screenRect);
	textureRect.Translate(-posX, -posY);
}

//Checks if the other rectangle is completely inside the rectangle calling the function
bool Rectangle::CompletelyContains(const Rectangle &other) const
{
	if (left < other.left && right > other.right && top > other.top && bottom < other.bottom)
		return true;
	else
		return false;
}

//Checks if there is no overlap between two rectangles
bool Rectangle::CompletelyOutside(const Rectangle &other) const
{
	if (left > other.right || right < other.left || top > other.bottom || bottom < other.top)
		return true;
	else
		return false;
}