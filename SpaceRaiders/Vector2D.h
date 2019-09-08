#pragma once
#include <xtgmath.h>

struct Vector2D
{
public:
	Vector2D() : x(0), y(0) {};

	Vector2D(const Vector2D& vector)
	{
		x = vector.x;
		y = vector.y;
	}

	Vector2D(float x, float y) : x(x), y(y) {};
	~Vector2D() {}

	bool IntCmp(const Vector2D& vec) { return int(x) == int(vec.x) && int(y) == int(vec.y); }
	void Normalize() 
	{
		float length = static_cast<float>(sqrt(x*x + y * y));
		x /= length;
		y /= length;
	}

	float x;
	float y;
	
	// Operator overloading
	Vector2D Vector2D::operator+(const Vector2D& other)
	{
		return Vector2D(x + other.x, y + other.y);
	}

	Vector2D Vector2D::operator*(const float other)
	{
		return Vector2D(x * other, y * other);
	}

	Vector2D Vector2D::operator/(const float other)
	{
		return Vector2D(x/ other, y/other);
	}

	Vector2D Vector2D::operator-(const Vector2D& other)
	{
		return Vector2D(x-other.x, y-other.y);
	}

	float Vector2D::operator*(const Vector2D& other)
	{
		return x * other.x + y * other.y;
	}

	bool Vector2D::operator==(const Vector2D& other) const
	{
		return (x == other.x && y == other.y);
	}

	bool Vector2D::operator!=(const Vector2D& other)
	{
		return !(x == other.x && y == other.y);
	}

	float Vector2D::length()
	{
		return static_cast<float>(sqrt(x * x + y * y));
	}

};


