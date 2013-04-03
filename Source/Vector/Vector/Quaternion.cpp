#include "Quaternion.h"	
#include <math.h>

Quaternion::Quaternion()
{
	r = 1;
	i = 0;
	j = 0;
	k = 0;
}

Quaternion::Quaternion(float R, float I, float J, float K)
{
	r = R;
	i = I;
	j = J;
	k = K;
}

Quaternion::~Quaternion()
{
}

float Quaternion::R()
{
	return r;
}

float Quaternion::I()
{
	return i;
}

float Quaternion::J()
{
	return j;
}

float Quaternion::K()
{
	return k;
}

void Quaternion::Set(float R, float I, float J, float K)
{
	r = R;
	i = I;
	j = J;
	k = K;
}

void Quaternion::SetFromEuler(float x, float y, float z)
{
	const float toRad = 3.14159f / 180.0f;
 
	//float zRot = (z * toRad) / 2;
	//float yRot = (y * toRad) / 2;
	//float xRot = (x * toRad) / 2;
 //
	//float sinZ = sin(zRot);
	//float cosZ = cos(zRot);
	//float sinY = sin(yRot);
	//float cosY = cos(yRot);
	//float sinX = sin(xRot);
	//float cosX = cos(xRot);
 //
	//r = cosZ * cosY * cosX + sinZ * sinY * sinX;
	//i = sinZ * cosY * cosX - cosZ * sinY * sinX;
	//j = cosZ * sinY * cosX + sinZ * cosY * sinX;
	//k = cosZ * cosY * sinX - sinZ * sinY * cosX;

	float xRot = (x * toRad) / 2.0f;
	float yRot = (y * toRad) / 2.0f;
	float zRot = (z * toRad) / 2.0f;
 
	float sinX = sin(xRot);
	float sinY = sin(yRot);
	float sinZ = sin(zRot);
	float cosX = cos(xRot);
	float cosY = cos(yRot);
	float cosZ = cos(zRot);
 
	i = sinZ * cosX * cosY - cosZ * sinX * sinY;
	j = cosZ * sinX * cosY + sinZ * cosX * sinY;
	k = cosZ * cosX * sinY - sinZ * sinX * cosY;
	r = cosZ * cosX * cosY + sinZ * sinX * sinY;

	Normalize();
}

void Quaternion::SetFromEuler(Vector3& euler)
{
	SetFromEuler(euler.X(), euler.Y(), euler.Z());
}

void Quaternion::Normalize()
{
	float d = r * r + i * i + j * j + k * k;

	if(d == 0)
	{
		r = 1;
		return;
	}

	d = 1.0f/sqrt(d);
	r *= d;
	i *= d;
	j *= d;
	k *= d;
}

void Quaternion::Rotate(Vector3& rotation)
{
	Quaternion temp(0, rotation.X(), rotation .Y(), rotation.Z());
	(*this) *= temp;
}

void Quaternion::RotateByEuler(Vector3& rotation)
{
	Quaternion temp;
	temp.SetFromEuler(rotation);

	*this *= temp;
}

void Quaternion::RotateByEuler(float x, float y, float z)
{
	Quaternion temp;
	temp.SetFromEuler(x, y, z);

	*this *= temp;
}

Quaternion Quaternion::operator*(const Quaternion &rhs)
{
	Quaternion quaternion = *this;
	quaternion *= rhs;
	return quaternion;
}

Quaternion& Quaternion::operator*=(const Quaternion &rhs)
{
	Quaternion temp = *this;

	r = temp.r * rhs.r - temp.i * rhs.i - temp.j * rhs.j - temp.k * rhs.k;
	i = temp.r * rhs.i - temp.i * rhs.r - temp.j * rhs.k - temp.k * rhs.j;
	j = temp.r * rhs.j - temp.j * rhs.r - temp.k * rhs.i - temp.i * rhs.k;
	k = temp.r * rhs.k - temp.k * rhs.r - temp.i * rhs.j - temp.j * rhs.i;

	return *this;
}

Quaternion& Quaternion::operator+=(const Vector3 &rhs)
{
	Quaternion temp(0, rhs.X(), rhs.Y(), rhs.Z());
	temp *= (*this);

	r += temp.r * 0.5f;
	i += temp.i * 0.5f;
	j += temp.j * 0.5f;
	k += temp.k * 0.5f;

	return *this;
}