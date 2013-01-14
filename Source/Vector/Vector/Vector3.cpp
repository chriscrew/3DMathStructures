#include "Vector3.h"
#include <math.h>

Vector3::Vector3()
{
	mX = 0;
	mY = 0;
}

Vector3::Vector3(float x, float y, float z)
{
	mX = x;
	mY = y;
	mZ = z;
}


float Vector3::X()
{
	return mX;
}

float Vector3::Y()
{
	return mY;
}

float Vector3::Z()
{
	return mZ;
}


void Vector3::SetX(float x)
{
	mX = x;
}

void Vector3::SetY(float y)
{
	mY = y;
}

void Vector3::SetZ(float z)
{
	mZ = z;
}


float Vector3::Length()
{
	return sqrt(pow(mX, 2) + pow(mY, 2) + pow(mZ, 2));
}

float Vector3::LengthSquared()
{
	return pow(mX, 2) + pow(mY, 2) + pow(mZ, 2);
}


float Vector3::Distance(Vector3 other)
{
	return sqrt(pow(other.X() - mX, 2) + pow(other.Y() - mY, 2) + pow(other.Z() - mZ, 2));
}

float Vector3::DistanceSquared(Vector3 other)
{
	return pow(other.X() - mX, 2) + pow(other.Y() - mY, 2) + pow(other.Z() - mZ, 2);
}


float Vector3::Dot(Vector3 other)
{
	return (mX * other.X()) + (mY * other.Y()) + (mZ * other.Z());
}

Vector3 Vector3::Cross(Vector3 other)
{
	Vector3 result;

	result.SetX((mY * other.Z()) - (other.Y() * mZ));
	result.SetY((mZ * other.X()) - (other.Z() * mX));
	result.SetZ((mX * other.Y()) - (other.X() * mY));

	return result;
}


void Vector3::Normalize()
{
	float length = Length();

	mX = mX/length;
	mY = mY/length;
	mZ = mZ/length;
}

Vector3 Vector3::Normalized()
{
	Vector3 result;
	float length = Length();

	result.SetX(mX/length);
	result.SetY(mY/length);
	result.SetZ(mZ/length);

	return result;
}

Vector3 Vector3::operator+(const Vector3 &rhs)
{
	Vector3 vector = *this;
	vector += rhs;
	return vector;
}

Vector3& Vector3::operator+=(const Vector3 &rhs)
{
	mX += rhs.mX;
	mY += rhs.mY;
	mZ += rhs.mZ;
	return *this;
}

Vector3 Vector3::operator-(const Vector3 &rhs)
{
	Vector3 vector = *this;
	vector -= rhs;
	return vector;
}

Vector3& Vector3::operator-=(const Vector3 &rhs)
{
	mX -= rhs.mX;
	mY -= rhs.mY;
	mZ -= rhs.mZ;
	return *this;
}

Vector3 Vector3::operator*(const int &rhs)
{
	Vector3 vector = *this;
	vector *= rhs;
	return vector;
}

Vector3& Vector3::operator*=(const int &rhs)
{
	mX *= rhs;
	mY *= rhs;
	mZ *= rhs;
	return *this;
}

Vector3 Vector3::operator/(const int &rhs)
{
	Vector3 vector = *this;
	vector /= rhs;
	return vector;
}

Vector3& Vector3::operator/=(const int &rhs)
{
	mX /= rhs;
	mY /= rhs;
	mZ /= rhs;
	return *this;
}