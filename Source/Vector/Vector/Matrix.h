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

	Vector3 TransformPoint(Vector3 point);

	float* GetPtr();

	static Matrix GenTranslation(Vector3 pos);
	static Matrix GenTranslation(float x, float y, float z);

	static Matrix GenRotation(Vector3 eulerAngles);
	static Matrix GenRotation(float x, float y, float z);

	static Matrix GenLookAt(Vector3 target, Vector3 position, Vector3 up);

	static Matrix GenProjection(float fov, float aspectRatio, float near, float far);

	Matrix operator*(const Matrix &rhs);
	Matrix& operator*=(const Matrix &rhs);
	
private:

	///////////////
	// 0 4 8  12 //
	// 1 5 9  13 //
	// 2 6 10 14 //
	// 3 7 11 15 //
	///////////////
	float mValues[16];

	static int TwoDimToOneDim(int x, int y, int width);
};