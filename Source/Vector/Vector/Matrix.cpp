#include "Matrix.h"
#include <math.h>

Matrix::Matrix()
{
	for(int i = 0; i < 16; i++)
	{
		mValues[i] = 0;
	}
}

Matrix::~Matrix()
{
	for(int i = 0; i < 16; i++)
	{
		mValues[i] = 0;
	}
}

void Matrix::SetValue(int x, int y, float value)
{
	x -= 1;
	y -= 1;
	mValues[Matrix::TwoDimToOneDim(x, y)] = value;
}

float Matrix::GetValue(int x, int y)
{
	x -= 1;
	y -= 1;
	return mValues[Matrix::TwoDimToOneDim(x, y)];
}

void Matrix::SetRow(int row, float x, float y, float z, float w)
{
	row -= 1;
	mValues[(row * 4)    ] = x;
	mValues[(row * 4) + 1] = y;
	mValues[(row * 4) + 2] = z;
	mValues[(row * 4) + 3] = w;
}

void Matrix::SetCollumm(int collumn, float x, float y, float z, float w)
{
	collumn -=1;
	mValues[collumn     ] = x;
	mValues[collumn + 4 ] = y;
	mValues[collumn + 8 ] = z;
	mValues[collumn + 12] = w;
}

float* Matrix::GetPtr()
{
	return mValues;
}

Matrix Matrix::GenTranslaion(Vector3 pos)
{
	Matrix matrix;
	matrix.SetRow(1, 1.0f, 0.0f, 0.0f, pos.X());
	matrix.SetRow(2, 0.0f, 1.0f, 0.0f, pos.Y());
	matrix.SetRow(3, 0.0f, 0.0f, 1.0f, pos.Z());
	matrix.SetRow(4, 0.0f, 0.0f, 0.0f, 1.0);
	return matrix;
}

Matrix Matrix::GenTranslaion(float x, float y, float z)
{
	Matrix matrix;
	matrix.SetRow(1, 1.0f, 0.0f, 0.0f, x);
	matrix.SetRow(2, 0.0f, 1.0f, 0.0f, y);
	matrix.SetRow(3, 0.0f, 0.0f, 1.0f, z);
	matrix.SetRow(4, 0.0f, 0.0f, 0.0f, 1.0f);
	return matrix;
}

Matrix Matrix::GenRotation(Vector3 eulerAngles)
{
	Matrix matrixX;
	matrixX.SetRow(1, 1.0f     , 0.0f    , 0.0f     , 0.0f);
	matrixX.SetRow(2, 0.0f     , cos(eulerAngles.X()), sin(eulerAngles.X()), 0.0f);
	matrixX.SetRow(3, 0.0f     ,-sin(eulerAngles.X()), cos(eulerAngles.X()), 0.0f);
	matrixX.SetRow(4, 0.0f     , 0.0f   , 0.0f     , 1.0f);

	Matrix matrixY;
	matrixY.SetRow(1, cos(eulerAngles.Y()), 0.0f     ,-sin(eulerAngles.Y()), 0.0f);
	matrixY.SetRow(2, 0.0f     , 1.0f     , 0.0f     , 0.0f);
	matrixY.SetRow(3, sin(eulerAngles.Y()), 0.0f     , cos(eulerAngles.X()), 0.0f);
	matrixY.SetRow(4, 0.0f     , 0.0f     , 0.0f     , 1.0f);

	Matrix matrixZ;
	matrixZ.SetRow(1, cos(eulerAngles.Z()), sin(eulerAngles.Z()), 0.0f     , 0.0f);
	matrixZ.SetRow(2,-sin(eulerAngles.Z()), cos(eulerAngles.Z()), 0.0f     , 0.0f);
	matrixZ.SetRow(3, 0.0f     , 0.0f     , 1.0f     , 0.0f);
	matrixZ.SetRow(4, 0.0f     , 0.0f     , 0.0f     , 1.0f);

	return matrixX * matrixY * matrixZ;
}

Matrix Matrix::GenRotation(float x, float y, float z)
{
	Matrix matrixX;
	matrixX.SetRow(1, 1.0f   , 0.0f   , 0.0f  , 0.0f);
	matrixX.SetRow(2, 0.0f   ,  cos(x), sin(x), 0.0f);
	matrixX.SetRow(3, 0.0f   , -sin(x), cos(x), 0.0f);
	matrixX.SetRow(4, 0.0f   , 0.0f   , 0.0f  , 1.0f);

	Matrix matrixY;
	matrixY.SetRow(1, cos(y), 0.0f   ,-sin(y), 0.0f);
	matrixY.SetRow(2, 0.0f  , 1.0f   , 0.0f  , 0.0f);
	matrixY.SetRow(3, sin(y), 0.0f   , cos(x), 0.0f);
	matrixY.SetRow(4, 0.0f  , 0.0f   , 0.0f  , 1.0f);

	Matrix matrixZ;
	matrixZ.SetRow(1, cos(z), sin(z), 0.0f   , 0.0f);
	matrixZ.SetRow(2,-sin(z), cos(z), 0.0f   , 0.0f);
	matrixZ.SetRow(3, 0.0f  , 0.0f  , 1.0f   , 0.0f);
	matrixZ.SetRow(4, 0.0f  , 0.0f  , 0.0f   , 1.0f);

	return matrixX * matrixY * matrixZ;
}

int Matrix::TwoDimToOneDim(int x, int y)
{
	return (y * 10) + x;
}

Matrix& Matrix::operator*(const Matrix &rhs)
{
	mValues[Matrix::TwoDimToOneDim(0,0)] = mValues[Matrix::TwoDimToOneDim(0,0)] * rhs.mValues[Matrix::TwoDimToOneDim(0,0)] + mValues[Matrix::TwoDimToOneDim(0,1)] * rhs.mValues[Matrix::TwoDimToOneDim(1,0)] + mValues[Matrix::TwoDimToOneDim(0,2)] * rhs.mValues[Matrix::TwoDimToOneDim(2,0)] + mValues[Matrix::TwoDimToOneDim(0,3)] * rhs.mValues[Matrix::TwoDimToOneDim(3,0)]; 
	mValues[Matrix::TwoDimToOneDim(0,1)] = mValues[Matrix::TwoDimToOneDim(0,0)] * rhs.mValues[Matrix::TwoDimToOneDim(0,1)] + mValues[Matrix::TwoDimToOneDim(0,1)] * rhs.mValues[Matrix::TwoDimToOneDim(1,1)] + mValues[Matrix::TwoDimToOneDim(0,2)] * rhs.mValues[Matrix::TwoDimToOneDim(2,1)] + mValues[Matrix::TwoDimToOneDim(0,3)] * rhs.mValues[Matrix::TwoDimToOneDim(3,1)]; 
	mValues[Matrix::TwoDimToOneDim(0,2)] = mValues[Matrix::TwoDimToOneDim(0,0)] * rhs.mValues[Matrix::TwoDimToOneDim(0,2)] + mValues[Matrix::TwoDimToOneDim(0,1)] * rhs.mValues[Matrix::TwoDimToOneDim(1,2)] + mValues[Matrix::TwoDimToOneDim(0,2)] * rhs.mValues[Matrix::TwoDimToOneDim(2,2)] + mValues[Matrix::TwoDimToOneDim(0,3)] * rhs.mValues[Matrix::TwoDimToOneDim(3,2)]; 
	mValues[Matrix::TwoDimToOneDim(0,3)] = mValues[Matrix::TwoDimToOneDim(0,0)] * rhs.mValues[Matrix::TwoDimToOneDim(0,3)] + mValues[Matrix::TwoDimToOneDim(0,1)] * rhs.mValues[Matrix::TwoDimToOneDim(1,3)] + mValues[Matrix::TwoDimToOneDim(0,2)] * rhs.mValues[Matrix::TwoDimToOneDim(2,3)] + mValues[Matrix::TwoDimToOneDim(0,3)] * rhs.mValues[Matrix::TwoDimToOneDim(3,3)]; 
	mValues[Matrix::TwoDimToOneDim(1,0)] = mValues[Matrix::TwoDimToOneDim(1,0)] * rhs.mValues[Matrix::TwoDimToOneDim(0,0)] + mValues[Matrix::TwoDimToOneDim(1,1)] * rhs.mValues[Matrix::TwoDimToOneDim(1,0)] + mValues[Matrix::TwoDimToOneDim(1,2)] * rhs.mValues[Matrix::TwoDimToOneDim(2,0)] + mValues[Matrix::TwoDimToOneDim(1,3)] * rhs.mValues[Matrix::TwoDimToOneDim(3,0)]; 
	mValues[Matrix::TwoDimToOneDim(1,1)] = mValues[Matrix::TwoDimToOneDim(1,0)] * rhs.mValues[Matrix::TwoDimToOneDim(0,1)] + mValues[Matrix::TwoDimToOneDim(1,1)] * rhs.mValues[Matrix::TwoDimToOneDim(1,1)] + mValues[Matrix::TwoDimToOneDim(1,2)] * rhs.mValues[Matrix::TwoDimToOneDim(2,1)] + mValues[Matrix::TwoDimToOneDim(1,3)] * rhs.mValues[Matrix::TwoDimToOneDim(3,1)]; 
	mValues[Matrix::TwoDimToOneDim(1,2)] = mValues[Matrix::TwoDimToOneDim(1,0)] * rhs.mValues[Matrix::TwoDimToOneDim(0,2)] + mValues[Matrix::TwoDimToOneDim(1,1)] * rhs.mValues[Matrix::TwoDimToOneDim(1,2)] + mValues[Matrix::TwoDimToOneDim(1,2)] * rhs.mValues[Matrix::TwoDimToOneDim(2,2)] + mValues[Matrix::TwoDimToOneDim(1,3)] * rhs.mValues[Matrix::TwoDimToOneDim(3,2)]; 
	mValues[Matrix::TwoDimToOneDim(1,3)] = mValues[Matrix::TwoDimToOneDim(1,0)] * rhs.mValues[Matrix::TwoDimToOneDim(0,3)] + mValues[Matrix::TwoDimToOneDim(1,1)] * rhs.mValues[Matrix::TwoDimToOneDim(1,3)] + mValues[Matrix::TwoDimToOneDim(1,2)] * rhs.mValues[Matrix::TwoDimToOneDim(2,3)] + mValues[Matrix::TwoDimToOneDim(1,3)] * rhs.mValues[Matrix::TwoDimToOneDim(3,3)]; 
	mValues[Matrix::TwoDimToOneDim(2,0)] = mValues[Matrix::TwoDimToOneDim(2,0)] * rhs.mValues[Matrix::TwoDimToOneDim(0,0)] + mValues[Matrix::TwoDimToOneDim(2,1)] * rhs.mValues[Matrix::TwoDimToOneDim(1,0)] + mValues[Matrix::TwoDimToOneDim(2,2)] * rhs.mValues[Matrix::TwoDimToOneDim(2,0)] + mValues[Matrix::TwoDimToOneDim(2,3)] * rhs.mValues[Matrix::TwoDimToOneDim(3,0)]; 
	mValues[Matrix::TwoDimToOneDim(2,1)] = mValues[Matrix::TwoDimToOneDim(2,0)] * rhs.mValues[Matrix::TwoDimToOneDim(0,1)] + mValues[Matrix::TwoDimToOneDim(2,1)] * rhs.mValues[Matrix::TwoDimToOneDim(1,1)] + mValues[Matrix::TwoDimToOneDim(2,2)] * rhs.mValues[Matrix::TwoDimToOneDim(2,1)] + mValues[Matrix::TwoDimToOneDim(2,3)] * rhs.mValues[Matrix::TwoDimToOneDim(3,1)]; 
	mValues[Matrix::TwoDimToOneDim(2,2)] = mValues[Matrix::TwoDimToOneDim(2,0)] * rhs.mValues[Matrix::TwoDimToOneDim(0,2)] + mValues[Matrix::TwoDimToOneDim(2,1)] * rhs.mValues[Matrix::TwoDimToOneDim(1,2)] + mValues[Matrix::TwoDimToOneDim(2,2)] * rhs.mValues[Matrix::TwoDimToOneDim(2,2)] + mValues[Matrix::TwoDimToOneDim(2,3)] * rhs.mValues[Matrix::TwoDimToOneDim(3,2)]; 
	mValues[Matrix::TwoDimToOneDim(2,3)] = mValues[Matrix::TwoDimToOneDim(2,0)] * rhs.mValues[Matrix::TwoDimToOneDim(0,3)] + mValues[Matrix::TwoDimToOneDim(2,1)] * rhs.mValues[Matrix::TwoDimToOneDim(1,3)] + mValues[Matrix::TwoDimToOneDim(2,2)] * rhs.mValues[Matrix::TwoDimToOneDim(2,3)] + mValues[Matrix::TwoDimToOneDim(2,3)] * rhs.mValues[Matrix::TwoDimToOneDim(3,3)]; 
	mValues[Matrix::TwoDimToOneDim(3,0)] = mValues[Matrix::TwoDimToOneDim(3,0)] * rhs.mValues[Matrix::TwoDimToOneDim(0,0)] + mValues[Matrix::TwoDimToOneDim(3,1)] * rhs.mValues[Matrix::TwoDimToOneDim(1,0)] + mValues[Matrix::TwoDimToOneDim(3,2)] * rhs.mValues[Matrix::TwoDimToOneDim(2,0)] + mValues[Matrix::TwoDimToOneDim(3,3)] * rhs.mValues[Matrix::TwoDimToOneDim(3,0)]; 
	mValues[Matrix::TwoDimToOneDim(3,1)] = mValues[Matrix::TwoDimToOneDim(3,0)] * rhs.mValues[Matrix::TwoDimToOneDim(0,1)] + mValues[Matrix::TwoDimToOneDim(3,1)] * rhs.mValues[Matrix::TwoDimToOneDim(1,1)] + mValues[Matrix::TwoDimToOneDim(3,2)] * rhs.mValues[Matrix::TwoDimToOneDim(2,1)] + mValues[Matrix::TwoDimToOneDim(3,3)] * rhs.mValues[Matrix::TwoDimToOneDim(3,1)]; 
	mValues[Matrix::TwoDimToOneDim(3,2)] = mValues[Matrix::TwoDimToOneDim(3,0)] * rhs.mValues[Matrix::TwoDimToOneDim(0,2)] + mValues[Matrix::TwoDimToOneDim(3,1)] * rhs.mValues[Matrix::TwoDimToOneDim(1,2)] + mValues[Matrix::TwoDimToOneDim(3,2)] * rhs.mValues[Matrix::TwoDimToOneDim(2,2)] + mValues[Matrix::TwoDimToOneDim(3,3)] * rhs.mValues[Matrix::TwoDimToOneDim(3,2)]; 
	mValues[Matrix::TwoDimToOneDim(3,3)] = mValues[Matrix::TwoDimToOneDim(3,0)] * rhs.mValues[Matrix::TwoDimToOneDim(0,3)] + mValues[Matrix::TwoDimToOneDim(3,1)] * rhs.mValues[Matrix::TwoDimToOneDim(1,3)] + mValues[Matrix::TwoDimToOneDim(3,2)] * rhs.mValues[Matrix::TwoDimToOneDim(2,3)] + mValues[Matrix::TwoDimToOneDim(3,3)] * rhs.mValues[Matrix::TwoDimToOneDim(3,3)];  

	return *this;
}