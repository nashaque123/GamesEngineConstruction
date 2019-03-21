	#pragma once
#include <HAPI_lib.h>
#include <algorithm>

using namespace HAPISPACE;

class Rectangle
{
public:
	Rectangle();
	Rectangle(int w, int h);
	~Rectangle();

	int left{ 0 }, right{ 0 }, top{ 0 }, bottom{ 0 };

	int Width() const { return right - left; }
	int Height() const { return bottom - top; }

	void ClipTo(const Rectangle &other);

	void ClipBlit(const Rectangle &screenRect, Rectangle &textureRect, const int posX, const int posY) const;
	void Translate(int posX, int posY);

	bool CompletelyContains(const Rectangle &other) const;
	bool CompletelyOutside(const Rectangle &other) const;
};

