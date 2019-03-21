#include "Vector2.h"
#include <cmath>

//Default constructor with x and y values staying at 0
Vector2::Vector2()
{
}

//Constructor passing in values for x and y
Vector2::Vector2(float x, float y) : posX(x), posY(y)
{
}

//Copy constructor to take values
Vector2::Vector2(const Vector2& other)
{
	posX = other.posX;
	posY = other.posY;
}

Vector2::~Vector2()
{
}

//Function to use operator += with Vector2
Vector2 Vector2::operator+=(const Vector2& rhs)
{
	this->posX += rhs.posX;
	this->posY += rhs.posY;

	return Vector2(posX, posY);
}

//Use operator += with float
Vector2 Vector2::operator+=(const float& rhs)
{
	this->posX += rhs;
	this->posY += rhs;

	return Vector2(posX, posY);
}

//Function to use operator -= with Vector2
Vector2 Vector2::operator-=(const Vector2& rhs)
{
	this->posX -= rhs.posX;
	this->posY -= rhs.posY;

	return Vector2(posX, posY);
}

//Use operator -= with float
Vector2 Vector2::operator-=(const float& rhs)
{
	this->posX -= rhs;
	this->posY -= rhs;

	return Vector2(posX, posY);
}

//Function finding length of a Vector2
float Vector2::Length()
{
	float length = 0.f;
	length += this->posX;
	length += this->posY;
	return length;
}

//Function to find direction of Vector2
float Vector2::Normalise()
{
	float value = 0;
	value += (this->posX * this->posX);
	value += (this->posY * this->posY);
	value = std::sqrt(value);
	return value;
}