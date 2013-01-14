#include "Vector2.h"
#include <math.h>

Vector2::Vector2()
{
	mX = 0;
	mY = 0;
}

Vector2::Vector2(float x, float y)
{
	mX = x;
	mY = y;
}


float Vector2::X()
{
	return mX;
}

float Vector2::Y()
{
	return mY;
}


void Vector2::SetX(float x)
{
	mX = x;
}

void Vector2::SetY(float y)
{
	mY = y;
}


float Vector2::Length()
{
	return sqrt(pow(mX, 2) + pow(mY, 2));
}

float Vector2::LengthSquared()
{
	return pow(mX, 2) + pow(mY, 2);
}


float Vector2::Distance(Vector2 other)
{
	return sqrt(pow(other.X() - mX, 2) + pow(other.X() - mY, 2));
}

float Vector2::DistanceSquared(Vector2 other)
{
	return pow(other.X() - mX, 2) + pow(other.X() - mY, 2);
}


float Vector2::Dot(Vector2 other)
{
	return (mX * other.X()) + (mY * other.Y());
}


void Vector2::Normalize()
{
	float length = Length();

	mX = mX/length;
	mY = mY/length;
}

Vector2 Vector2::Normalized()
{
	Vector2 result;
	float length = Length();

	result.SetX(mX/length);
	result.SetY(mY/length);

	return result;
}

Vector2 Vector2::operator+(const Vector2 &rhs)
{
	Vector2 vector = *this;
	vector += rhs;
	return vector;
}

Vector2& Vector2::operator+=(const Vector2 &rhs)
{
	mX += rhs.mX;
	mY += rhs.mY;
	return *this;
}

Vector2 Vector2::operator-(const Vector2 &rhs)
{
	Vector2 vector = *this;
	vector -= rhs;
	return vector;
}

Vector2& Vector2::operator-=(const Vector2 &rhs)
{
	mX -= rhs.mX;
	mY -= rhs.mY;
	return *this;
}

Vector2 Vector2::operator*(const int &rhs)
{
	Vector2 vector = *this;
	vector *= rhs;
	return vector;
}

Vector2& Vector2::operator*=(const int &rhs)
{
	mX *= rhs;
	mY *= rhs;
	return *this;
}

Vector2 Vector2::operator/(const int &rhs)
{
	Vector2 vector = *this;
	vector /= rhs;
	return vector;
}

Vector2& Vector2::operator/=(const int &rhs)
{
	mX /= rhs;
	mY /= rhs;
	return *this;
}