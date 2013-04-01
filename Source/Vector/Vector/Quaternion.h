#pragma once

#include "Vector3.h"

class Quaternion
{
public:
	Quaternion();
	Quaternion(float R, float I, float J, float K);
	~Quaternion();

	float R();
	float I();
	float J();
	float K();

	void Set(float R, float I, float J, float K);
	void SetFromEuler(float x, float y, float z);
	void SetFromEuler(Vector3& euler);

	void Normalize();
	void Rotate(Vector3& rotation);
	void RotateByEuler(Vector3& rotation);
	void RotateByEuler(float x, float y, float z);

	Quaternion operator*(const Quaternion &rhs);
	Quaternion& operator*=(const Quaternion &rhs);
	Quaternion& operator+=(const Vector3 &rhs);

private:
	float r;
	float i;
	float j;
	float k;
};