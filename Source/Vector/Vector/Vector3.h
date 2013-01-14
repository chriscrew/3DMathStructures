#pragma once

//A class for representing a 3d vector or point in space
//written by Kyle Marchev
class Vector3
{
public:
	Vector3();
	Vector3(float x, float y, float z);

	float X();
	float Y();
	float Z();

	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);

	float Length();
	float LengthSquared();

	float Distance(Vector3 other);
	float DistanceSquared(Vector3 other);

	float Dot(Vector3 other);
	Vector3 Cross(Vector3 other);

	void Normalize();
	Vector3 Normalized();

	Vector3 operator+(const Vector3 &rhs);
	Vector3& operator+=(const Vector3 &rhs);
	Vector3 operator-(const Vector3 &rhs);
	Vector3& operator-=(const Vector3 &rhs);
	Vector3 operator*(const int &rhs);
	Vector3& operator*=(const int &rhs);
	Vector3 operator/(const int &rhs);
	Vector3& operator/=(const int &rhs);

private:

	float mX;
	float mY;
	float mZ;
};
