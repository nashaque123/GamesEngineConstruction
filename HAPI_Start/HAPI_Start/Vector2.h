#pragma once
class Vector2
{
public:
	float posX{ 0 }, posY{ 0 };

	Vector2();
	Vector2(float x, float y);
	Vector2(const Vector2& other);
	~Vector2();

	Vector2 operator+=(const Vector2& rhs);
	Vector2 operator+=(const float& rhs);
	Vector2 operator-=(const Vector2& rhs);
	Vector2 operator-=(const float& rhs);

	float Length();
	float Normalise();
};

//Function to add 2 Vector2 values
inline Vector2 operator+(Vector2 lhs, const Vector2& rhs)
{
	lhs.posX += rhs.posX;
	lhs.posY += rhs.posY;
	return lhs;
}

//Add a Vector2 and a float 
inline Vector2 operator+(Vector2 lhs, const float& rhs)
{
	lhs.posX += rhs;
	lhs.posY += rhs;
	return lhs;
}

//Function to subtract 2 Vector2 values
inline Vector2 operator-(Vector2 lhs, const Vector2& rhs)
{
	lhs.posX -= rhs.posX;
	lhs.posY -= rhs.posY;
	return lhs;
}

//Subtract a Vector2 and a float
inline Vector2 operator-(Vector2 lhs, const float& rhs)
{
	lhs.posX -= rhs;
	lhs.posY -= rhs;
	return lhs;
}

//Multiply a Vector2 by a float value
inline Vector2 operator*(Vector2 lhs, float rhs)
{
	lhs.posX *= rhs;
	lhs.posY *= rhs;
	return lhs;
}

//Divide a Vector 2 by a float value
inline Vector2 operator/(Vector2 lhs, float rhs)
{
	lhs.posX /= rhs;
	lhs.posY /= rhs;
	return lhs;
}

//Function to compare two Vector2 values and output if they're equal
inline bool operator==(const Vector2& lhs, const Vector2& rhs)
{
	if (lhs.posX == rhs.posX && lhs.posY == rhs.posY)
		return true;
	else
		return false;
}

//Function to compare two Vector2 values and output if they're not equal
inline bool operator!=(const Vector2& lhs, const Vector2& rhs)
{
	if (lhs.posX == rhs.posX && lhs.posY == rhs.posY)
		return false;
	else
		return true;
}