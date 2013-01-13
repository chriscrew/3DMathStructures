#pragma once

#include "Vector3.h"

class Matrix
{
public:
	Matrix();
	~Matrix();

	void SetValue(int x, int y, float value);
	float GetValue(int x, int y);

	void SetRow(int row, float x, float y, float z, float w);
	void SetCollumm(int collumn, float x, float y, float z, float w);

	float* GetPtr();

	static Matrix GenTranslaion(Vector3 pos);
	static Matrix GenTranslaion(float x, float y, float z);

	static Matrix GenRotation(Vector3 eulerAngles);
	static Matrix GenRotation(float x, float y, float z);

	Matrix& operator*(const Matrix &rhs);
	
private:

	///////////////
	// 1 5 9  13 //
	// 2 6 10 14 //
	// 3 7 11 15 //
	// 4 8 12 16 //
	///////////////
	float mValues[16];

	static int TwoDimToOneDim(int x, int y);
};