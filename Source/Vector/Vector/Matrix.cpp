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
	mValues[Matrix::TwoDimToOneDim(x, y,4)] = value;
}

float Matrix::GetValue(int x, int y)
{
	x -= 1;
	y -= 1;
	return mValues[Matrix::TwoDimToOneDim(x, y,4)];
}

void Matrix::SetRow(int row, float x, float y, float z, float w)
{
	row -=1;
	mValues[row     ] = x;
	mValues[row + 4 ] = y;
	mValues[row + 8 ] = z;
	mValues[row + 12] = w;
}

void Matrix::SetCollumm(int collumn, float x, float y, float z, float w)
{
	collumn -= 1;
	mValues[(collumn * 4)    ] = x;
	mValues[(collumn * 4) + 1] = y;
	mValues[(collumn * 4) + 2] = z;
	mValues[(collumn * 4) + 3] = w;
}

float* Matrix::GetPtr()
{
	return mValues;
}

Matrix Matrix::GenTranslation(Vector3 pos)
{
	Matrix matrix;
	matrix.SetRow(1,    1.0f,    0.0f,    0.0f, 0.0f);
	matrix.SetRow(2,    0.0f,    1.0f,    0.0f, 0.0f);
	matrix.SetRow(3,    0.0f,    0.0f,    1.0f, 0.0f);
	matrix.SetRow(4, pos.X(), pos.Y(), pos.Z(), 1.0f);
	return matrix;
}

Matrix Matrix::GenTranslation(float x, float y, float z)
{
	Matrix matrix;
	matrix.SetRow(1, 1.0f, 0.0f, 0.0f, 0.0f);
	matrix.SetRow(2, 0.0f, 1.0f, 0.0f, 0.0f);
	matrix.SetRow(3, 0.0f, 0.0f, 1.0f, 0.0f);
	matrix.SetRow(4,    x,    y,    z, 1.0f);
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

Matrix Matrix::GenLookAt(Vector3 target, Vector3 position, Vector3 up)
{
	Vector3 zAxis = (target - position).Normalized();
	Vector3 yAxis = up.Normalized();
	Vector3 xAxis = zAxis.Cross(yAxis).Normalized();
	yAxis = xAxis.Cross(zAxis);

	Matrix matrix;
	matrix.SetRow(1, xAxis.X()           , yAxis.X()           , -zAxis.X()           , 0);
	matrix.SetRow(2, xAxis.Y()           , yAxis.Y()           , -zAxis.Y()           , 0);
	matrix.SetRow(3, xAxis.Z()           , yAxis.Z()           , -zAxis.Z()           , 0);
	matrix.SetRow(4, -xAxis.Dot(position), -yAxis.Dot(position), zAxis.Dot(position), 1);

	return matrix;
}

Matrix Matrix::GenProjection(float fov, float aspectRatio, float near, float far)
{
	float size = near * tan((fov * (3.1415926 / 180.0)) / 2.0);
	float left = -size * aspectRatio;
	float right = size * aspectRatio;
	float bottom = -size;
	float top = size;

	Matrix matrix;
	matrix.SetRow(1, (2 * near) / (right - left), 0                          , (right + left)/(right - left)   ,  0);
	matrix.SetRow(2, 0                          , (2 * near )/ (top - bottom), (top + bottom)/(top - bottom)   ,  0);
	matrix.SetRow(3, 0                          , 0                          , -(far + near)/(far - near)      , -1);
	matrix.SetRow(4, 0                          , 0                          , -(2 * far * near) / (far - near),  0);
	return matrix;
}

int Matrix::TwoDimToOneDim(int y, int x, int width)
{
	return (y * width) + x;
}

Matrix Matrix::operator*(const Matrix &rhs)
{
	Matrix matrix = *this;
	matrix *= rhs;
	return matrix;
}

Matrix& Matrix::operator*=(const Matrix &rhs)
{
	float temp[16];

	for (int i=0; i<4; i++) 
	{
		temp[Matrix::TwoDimToOneDim(i,0,4)] =   (mValues[Matrix::TwoDimToOneDim(i,0,4)] * rhs.mValues[Matrix::TwoDimToOneDim(0,0,4)]) +
												(mValues[Matrix::TwoDimToOneDim(i,1,4)] * rhs.mValues[Matrix::TwoDimToOneDim(1,0,4)]) +
												(mValues[Matrix::TwoDimToOneDim(i,2,4)] * rhs.mValues[Matrix::TwoDimToOneDim(2,0,4)]) +
												(mValues[Matrix::TwoDimToOneDim(i,3,4)] * rhs.mValues[Matrix::TwoDimToOneDim(3,0,4)]) ;

		temp[Matrix::TwoDimToOneDim(i,1,4)] =   (mValues[Matrix::TwoDimToOneDim(i,0,4)] * rhs.mValues[Matrix::TwoDimToOneDim(0,1,4)]) +
												(mValues[Matrix::TwoDimToOneDim(i,1,4)] * rhs.mValues[Matrix::TwoDimToOneDim(1,1,4)]) +
												(mValues[Matrix::TwoDimToOneDim(i,2,4)] * rhs.mValues[Matrix::TwoDimToOneDim(2,1,4)]) +
												(mValues[Matrix::TwoDimToOneDim(i,3,4)] * rhs.mValues[Matrix::TwoDimToOneDim(3,1,4)]) ;

		temp[Matrix::TwoDimToOneDim(i,2,4)] =   (mValues[Matrix::TwoDimToOneDim(i,0,4)] * rhs.mValues[Matrix::TwoDimToOneDim(0,2,4)]) +
												(mValues[Matrix::TwoDimToOneDim(i,1,4)] * rhs.mValues[Matrix::TwoDimToOneDim(1,2,4)]) +
												(mValues[Matrix::TwoDimToOneDim(i,2,4)] * rhs.mValues[Matrix::TwoDimToOneDim(2,2,4)]) +
												(mValues[Matrix::TwoDimToOneDim(i,3,4)] * rhs.mValues[Matrix::TwoDimToOneDim(3,2,4)]) ;

		temp[Matrix::TwoDimToOneDim(i,3,4)] =   (mValues[Matrix::TwoDimToOneDim(i,0,4)] * rhs.mValues[Matrix::TwoDimToOneDim(0,3,4)]) +
												(mValues[Matrix::TwoDimToOneDim(i,1,4)] * rhs.mValues[Matrix::TwoDimToOneDim(1,3,4)]) +
												(mValues[Matrix::TwoDimToOneDim(i,2,4)] * rhs.mValues[Matrix::TwoDimToOneDim(2,3,4)]) +
												(mValues[Matrix::TwoDimToOneDim(i,3,4)] * rhs.mValues[Matrix::TwoDimToOneDim(3,3,4)]) ;
	}


	for(int i = 0; i < 16; i++)
	{
		mValues[i] = temp[i];
	}

	return *this;
}