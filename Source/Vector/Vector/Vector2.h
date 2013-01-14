#pragma once

//A class for representing a 2d vector or point in space
//written by Kyle Marchev
class Vector2
{
public:
	Vector2();
	Vector2(float x, float y);

	float X();
	float Y();

	void SetX(float x);
	void SetY(float y);

	float Length();
	float LengthSquared();

	float Distance(Vector2 other);
	float DistanceSquared(Vector2 other);

	float Dot(Vector2 other);

	void Normalize();
	Vector2 Normalized();

	Vector2 operator+(const Vector2 &rhs);
	Vector2& operator+=(const Vector2 &rhs);
	Vector2 operator-(const Vector2 &rhs);
	Vector2& operator-=(const Vector2 &rhs);
	Vector2 operator*(const int &rhs);
	Vector2& operator*=(const int &rhs);
	Vector2 operator/(const int &rhs);
	Vector2& operator/=(const int &rhs);

private:
	float mX;
	float mY;
};
