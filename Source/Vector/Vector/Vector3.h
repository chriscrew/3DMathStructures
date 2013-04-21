#pragma once

//A class for representing a 3d vector or point in space
//written by Kyle Marchev
class Vector3
{
public:
	Vector3();
	Vector3(float x, float y, float z);

	float X() const;
	float Y() const;
	float Z() const;

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
	Vector3 operator*(const float &rhs);
	Vector3& operator*=(const float &rhs);
	Vector3 operator/(const float &rhs);
	Vector3& operator/=(const float &rhs);

	float operator [](int i) const
	{
		switch(i)
		{
			case 0:
				return mX;
				break;

			case 1:
				return mY;
				break;

			default:
				return mZ;
				break;
		}
	}

	float & operator [](int i) 
	{
		switch(i)
		{
			case 0:
				return mX;
				break;

			case 1:
				return mY;
				break;

			default:
				return mZ;
				break;
		}
	}

private:

	float mX;
	float mY;
	float mZ;
};
