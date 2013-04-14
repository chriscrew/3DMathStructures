#include "Matrix.h"
#include <math.h>

Matrix::Matrix()
{
	SetRow(1, 1, 0, 0, 0);
	SetRow(2, 0, 1, 0, 0);
	SetRow(3, 0, 0, 1, 0);
	SetRow(4, 0, 0, 0, 1);
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

Vector3 Matrix::TransformPoint(Vector3 point)
{
	Vector3 result;
	
	result.SetX(mValues[Matrix::TwoDimToOneDim(0,0,4)] * point.X() + 
				mValues[Matrix::TwoDimToOneDim(0,1,4)] * point.Y() + 
				mValues[Matrix::TwoDimToOneDim(0,2,4)] * point.Z());

	result.SetY(mValues[Matrix::TwoDimToOneDim(1,0,4)] * point.X() + 
				mValues[Matrix::TwoDimToOneDim(1,1,4)] * point.Y() + 
				mValues[Matrix::TwoDimToOneDim(1,2,4)] * point.Z());

	result.SetZ(mValues[Matrix::TwoDimToOneDim(2,0,4)] * point.X() + 
				mValues[Matrix::TwoDimToOneDim(2,1,4)] * point.Y() + 
				mValues[Matrix::TwoDimToOneDim(2,2,4)] * point.Z());	

	return result;
}

void Matrix::Transpose()
{
	float temp[16];

	for(int i = 0; i < 16; i++)
	{
		temp[i] = mValues[i];
	}

	mValues[0] = temp[0];
	mValues[1] = temp[4];
	mValues[2] = temp[8];
	mValues[3] = temp[12];
	mValues[4] = temp[1];
	mValues[5] = temp[5];
	mValues[6] = temp[9];
	mValues[7] = temp[13];
	mValues[8] = temp[2];
	mValues[9] = temp[6];
	mValues[10] = temp[10];
	mValues[11] = temp[14];
	mValues[12] = temp[3];
	mValues[13] = temp[7];
	mValues[14] = temp[11];
	mValues[15] = temp[15];
}

Matrix Matrix::Transposed()
{
	Matrix result;

	float temp[16];

	for(int i = 0; i < 16; i++)
	{
		temp[i] = mValues[i];
	}

	result.SetValue(1, 1, temp[0]);
	result.SetValue(1, 2, temp[4]);
	result.SetValue(1, 3, temp[8]);
	result.SetValue(1, 4, temp[12]);
	result.SetValue(2, 1, temp[1]);
	result.SetValue(2, 2, temp[5]);
	result.SetValue(2, 3, temp[9]);
	result.SetValue(2, 4, temp[13]);
	result.SetValue(3, 1, temp[2]);
	result.SetValue(3, 2, temp[6]);
	result.SetValue(3, 3, temp[10]);
	result.SetValue(3, 4, temp[14]);
	result.SetValue(4, 1, temp[3]);
	result.SetValue(4, 2, temp[7]);
	result.SetValue(4, 3, temp[11]);
	result.SetValue(4, 4, temp[15]);

	return result;
}

void Matrix::Invert()
{
	float temp[16];

    temp[0] = mValues[5]  * mValues[10] * mValues[15] - 
             mValues[5]  * mValues[11] * mValues[14] - 
             mValues[9]  * mValues[6]  * mValues[15] + 
             mValues[9]  * mValues[7]  * mValues[14] +
             mValues[13] * mValues[6]  * mValues[11] - 
             mValues[13] * mValues[7]  * mValues[10];

    temp[4] = -mValues[4]  * mValues[10] * mValues[15] + 
              mValues[4]  * mValues[11] * mValues[14] + 
              mValues[8]  * mValues[6]  * mValues[15] - 
              mValues[8]  * mValues[7]  * mValues[14] - 
              mValues[12] * mValues[6]  * mValues[11] + 
              mValues[12] * mValues[7]  * mValues[10];

    temp[8] = mValues[4]  * mValues[9] * mValues[15] - 
             mValues[4]  * mValues[11] * mValues[13] - 
             mValues[8]  * mValues[5] * mValues[15] + 
             mValues[8]  * mValues[7] * mValues[13] + 
             mValues[12] * mValues[5] * mValues[11] - 
             mValues[12] * mValues[7] * mValues[9];

    temp[12] = -mValues[4]  * mValues[9] * mValues[14] + 
               mValues[4]  * mValues[10] * mValues[13] +
               mValues[8]  * mValues[5] * mValues[14] - 
               mValues[8]  * mValues[6] * mValues[13] - 
               mValues[12] * mValues[5] * mValues[10] + 
               mValues[12] * mValues[6] * mValues[9];

    temp[1] = -mValues[1]  * mValues[10] * mValues[15] + 
              mValues[1]  * mValues[11] * mValues[14] + 
              mValues[9]  * mValues[2] * mValues[15] - 
              mValues[9]  * mValues[3] * mValues[14] - 
              mValues[13] * mValues[2] * mValues[11] + 
              mValues[13] * mValues[3] * mValues[10];

    temp[5] = mValues[0]  * mValues[10] * mValues[15] - 
             mValues[0]  * mValues[11] * mValues[14] - 
             mValues[8]  * mValues[2] * mValues[15] + 
             mValues[8]  * mValues[3] * mValues[14] + 
             mValues[12] * mValues[2] * mValues[11] - 
             mValues[12] * mValues[3] * mValues[10];

    temp[9] = -mValues[0]  * mValues[9] * mValues[15] + 
              mValues[0]  * mValues[11] * mValues[13] + 
              mValues[8]  * mValues[1] * mValues[15] - 
              mValues[8]  * mValues[3] * mValues[13] - 
              mValues[12] * mValues[1] * mValues[11] + 
              mValues[12] * mValues[3] * mValues[9];

    temp[13] = mValues[0]  * mValues[9] * mValues[14] - 
              mValues[0]  * mValues[10] * mValues[13] - 
              mValues[8]  * mValues[1] * mValues[14] + 
              mValues[8]  * mValues[2] * mValues[13] + 
              mValues[12] * mValues[1] * mValues[10] - 
              mValues[12] * mValues[2] * mValues[9];

    temp[2] = mValues[1]  * mValues[6] * mValues[15] - 
             mValues[1]  * mValues[7] * mValues[14] - 
             mValues[5]  * mValues[2] * mValues[15] + 
             mValues[5]  * mValues[3] * mValues[14] + 
             mValues[13] * mValues[2] * mValues[7] - 
             mValues[13] * mValues[3] * mValues[6];

    temp[6] = -mValues[0]  * mValues[6] * mValues[15] + 
              mValues[0]  * mValues[7] * mValues[14] + 
              mValues[4]  * mValues[2] * mValues[15] - 
              mValues[4]  * mValues[3] * mValues[14] - 
              mValues[12] * mValues[2] * mValues[7] + 
              mValues[12] * mValues[3] * mValues[6];

    temp[10] = mValues[0]  * mValues[5] * mValues[15] - 
              mValues[0]  * mValues[7] * mValues[13] - 
              mValues[4]  * mValues[1] * mValues[15] + 
              mValues[4]  * mValues[3] * mValues[13] + 
              mValues[12] * mValues[1] * mValues[7] - 
              mValues[12] * mValues[3] * mValues[5];

    temp[14] = -mValues[0]  * mValues[5] * mValues[14] + 
               mValues[0]  * mValues[6] * mValues[13] + 
               mValues[4]  * mValues[1] * mValues[14] - 
               mValues[4]  * mValues[2] * mValues[13] - 
               mValues[12] * mValues[1] * mValues[6] + 
               mValues[12] * mValues[2] * mValues[5];

    temp[3] = -mValues[1] * mValues[6] * mValues[11] + 
              mValues[1] * mValues[7] * mValues[10] + 
              mValues[5] * mValues[2] * mValues[11] - 
              mValues[5] * mValues[3] * mValues[10] - 
              mValues[9] * mValues[2] * mValues[7] + 
              mValues[9] * mValues[3] * mValues[6];

    temp[7] = mValues[0] * mValues[6] * mValues[11] - 
             mValues[0] * mValues[7] * mValues[10] - 
             mValues[4] * mValues[2] * mValues[11] + 
             mValues[4] * mValues[3] * mValues[10] + 
             mValues[8] * mValues[2] * mValues[7] - 
             mValues[8] * mValues[3] * mValues[6];

    temp[11] = -mValues[0] * mValues[5] * mValues[11] + 
               mValues[0] * mValues[7] * mValues[9] + 
               mValues[4] * mValues[1] * mValues[11] - 
               mValues[4] * mValues[3] * mValues[9] - 
               mValues[8] * mValues[1] * mValues[7] + 
               mValues[8] * mValues[3] * mValues[5];

    temp[15] = mValues[0] * mValues[5] * mValues[10] - 
              mValues[0] * mValues[6] * mValues[9] - 
              mValues[4] * mValues[1] * mValues[10] + 
              mValues[4] * mValues[2] * mValues[9] + 
              mValues[8] * mValues[1] * mValues[6] - 
              mValues[8] * mValues[2] * mValues[5];

    float detterminate = mValues[0] * temp[0] + mValues[1] * temp[4] + mValues[2] * temp[8] + mValues[3] * temp[12];

    if (detterminate == 0)
	{
        return;
	}

    detterminate = 1.0f / detterminate;

    for (int i = 0; i < 16; i++)
	{
        mValues[i] = temp[i] * detterminate;
	}
}

Matrix Matrix::Inverse()
{
	Matrix result;

	float temp[16];

    temp[0] = mValues[5]  * mValues[10] * mValues[15] - 
             mValues[5]  * mValues[11] * mValues[14] - 
             mValues[9]  * mValues[6]  * mValues[15] + 
             mValues[9]  * mValues[7]  * mValues[14] +
             mValues[13] * mValues[6]  * mValues[11] - 
             mValues[13] * mValues[7]  * mValues[10];

    temp[4] = -mValues[4]  * mValues[10] * mValues[15] + 
              mValues[4]  * mValues[11] * mValues[14] + 
              mValues[8]  * mValues[6]  * mValues[15] - 
              mValues[8]  * mValues[7]  * mValues[14] - 
              mValues[12] * mValues[6]  * mValues[11] + 
              mValues[12] * mValues[7]  * mValues[10];

    temp[8] = mValues[4]  * mValues[9] * mValues[15] - 
             mValues[4]  * mValues[11] * mValues[13] - 
             mValues[8]  * mValues[5] * mValues[15] + 
             mValues[8]  * mValues[7] * mValues[13] + 
             mValues[12] * mValues[5] * mValues[11] - 
             mValues[12] * mValues[7] * mValues[9];

    temp[12] = -mValues[4]  * mValues[9] * mValues[14] + 
               mValues[4]  * mValues[10] * mValues[13] +
               mValues[8]  * mValues[5] * mValues[14] - 
               mValues[8]  * mValues[6] * mValues[13] - 
               mValues[12] * mValues[5] * mValues[10] + 
               mValues[12] * mValues[6] * mValues[9];

    temp[1] = -mValues[1]  * mValues[10] * mValues[15] + 
              mValues[1]  * mValues[11] * mValues[14] + 
              mValues[9]  * mValues[2] * mValues[15] - 
              mValues[9]  * mValues[3] * mValues[14] - 
              mValues[13] * mValues[2] * mValues[11] + 
              mValues[13] * mValues[3] * mValues[10];

    temp[5] = mValues[0]  * mValues[10] * mValues[15] - 
             mValues[0]  * mValues[11] * mValues[14] - 
             mValues[8]  * mValues[2] * mValues[15] + 
             mValues[8]  * mValues[3] * mValues[14] + 
             mValues[12] * mValues[2] * mValues[11] - 
             mValues[12] * mValues[3] * mValues[10];

    temp[9] = -mValues[0]  * mValues[9] * mValues[15] + 
              mValues[0]  * mValues[11] * mValues[13] + 
              mValues[8]  * mValues[1] * mValues[15] - 
              mValues[8]  * mValues[3] * mValues[13] - 
              mValues[12] * mValues[1] * mValues[11] + 
              mValues[12] * mValues[3] * mValues[9];

    temp[13] = mValues[0]  * mValues[9] * mValues[14] - 
              mValues[0]  * mValues[10] * mValues[13] - 
              mValues[8]  * mValues[1] * mValues[14] + 
              mValues[8]  * mValues[2] * mValues[13] + 
              mValues[12] * mValues[1] * mValues[10] - 
              mValues[12] * mValues[2] * mValues[9];

    temp[2] = mValues[1]  * mValues[6] * mValues[15] - 
             mValues[1]  * mValues[7] * mValues[14] - 
             mValues[5]  * mValues[2] * mValues[15] + 
             mValues[5]  * mValues[3] * mValues[14] + 
             mValues[13] * mValues[2] * mValues[7] - 
             mValues[13] * mValues[3] * mValues[6];

    temp[6] = -mValues[0]  * mValues[6] * mValues[15] + 
              mValues[0]  * mValues[7] * mValues[14] + 
              mValues[4]  * mValues[2] * mValues[15] - 
              mValues[4]  * mValues[3] * mValues[14] - 
              mValues[12] * mValues[2] * mValues[7] + 
              mValues[12] * mValues[3] * mValues[6];

    temp[10] = mValues[0]  * mValues[5] * mValues[15] - 
              mValues[0]  * mValues[7] * mValues[13] - 
              mValues[4]  * mValues[1] * mValues[15] + 
              mValues[4]  * mValues[3] * mValues[13] + 
              mValues[12] * mValues[1] * mValues[7] - 
              mValues[12] * mValues[3] * mValues[5];

    temp[14] = -mValues[0]  * mValues[5] * mValues[14] + 
               mValues[0]  * mValues[6] * mValues[13] + 
               mValues[4]  * mValues[1] * mValues[14] - 
               mValues[4]  * mValues[2] * mValues[13] - 
               mValues[12] * mValues[1] * mValues[6] + 
               mValues[12] * mValues[2] * mValues[5];

    temp[3] = -mValues[1] * mValues[6] * mValues[11] + 
              mValues[1] * mValues[7] * mValues[10] + 
              mValues[5] * mValues[2] * mValues[11] - 
              mValues[5] * mValues[3] * mValues[10] - 
              mValues[9] * mValues[2] * mValues[7] + 
              mValues[9] * mValues[3] * mValues[6];

    temp[7] = mValues[0] * mValues[6] * mValues[11] - 
             mValues[0] * mValues[7] * mValues[10] - 
             mValues[4] * mValues[2] * mValues[11] + 
             mValues[4] * mValues[3] * mValues[10] + 
             mValues[8] * mValues[2] * mValues[7] - 
             mValues[8] * mValues[3] * mValues[6];

    temp[11] = -mValues[0] * mValues[5] * mValues[11] + 
               mValues[0] * mValues[7] * mValues[9] + 
               mValues[4] * mValues[1] * mValues[11] - 
               mValues[4] * mValues[3] * mValues[9] - 
               mValues[8] * mValues[1] * mValues[7] + 
               mValues[8] * mValues[3] * mValues[5];

    temp[15] = mValues[0] * mValues[5] * mValues[10] - 
              mValues[0] * mValues[6] * mValues[9] - 
              mValues[4] * mValues[1] * mValues[10] + 
              mValues[4] * mValues[2] * mValues[9] + 
              mValues[8] * mValues[1] * mValues[6] - 
              mValues[8] * mValues[2] * mValues[5];

    float detterminate = mValues[0] * temp[0] + mValues[1] * temp[4] + mValues[2] * temp[8] + mValues[3] * temp[12];

    if (detterminate == 0)
	{
		Matrix identity = Matrix::Identity();
        return identity;
	}

    detterminate = 1.0f / detterminate;

    for (int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			result.SetValue(i+1, j+1, temp[Matrix::TwoDimToOneDim(i, j, 4)] * detterminate);
		}
	}

	return result;
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
	matrixX.SetRow(1, 1.0f     , 0.0f                , 0.0f                , 0.0f);
	matrixX.SetRow(2, 0.0f     , cos(eulerAngles.X()), sin(eulerAngles.X()), 0.0f);
	matrixX.SetRow(3, 0.0f     ,-sin(eulerAngles.X()), cos(eulerAngles.X()), 0.0f);
	matrixX.SetRow(4, 0.0f     , 0.0f                , 0.0f                , 1.0f);

	Matrix matrixY;
	matrixY.SetRow(1, cos(eulerAngles.Y()), 0.0f     ,-sin(eulerAngles.Y()), 0.0f);
	matrixY.SetRow(2, 0.0f                , 1.0f     , 0.0f                , 0.0f);
	matrixY.SetRow(3, sin(eulerAngles.Y()), 0.0f     , cos(eulerAngles.Y()), 0.0f);
	matrixY.SetRow(4, 0.0f                , 0.0f     , 0.0f                , 1.0f);

	Matrix matrixZ;
	matrixZ.SetRow(1, cos(eulerAngles.Z()), sin(eulerAngles.Z()), 0.0f     , 0.0f);
	matrixZ.SetRow(2,-sin(eulerAngles.Z()), cos(eulerAngles.Z()), 0.0f     , 0.0f);
	matrixZ.SetRow(3, 0.0f                , 0.0f                , 1.0f     , 0.0f);
	matrixZ.SetRow(4, 0.0f                , 0.0f                , 0.0f     , 1.0f);

	return matrixZ * matrixY * matrixX;
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
	matrixY.SetRow(3, sin(y), 0.0f   , cos(y), 0.0f);
	matrixY.SetRow(4, 0.0f  , 0.0f   , 0.0f  , 1.0f);

	Matrix matrixZ;
	matrixZ.SetRow(1, cos(z), sin(z), 0.0f   , 0.0f);
	matrixZ.SetRow(2,-sin(z), cos(z), 0.0f   , 0.0f);
	matrixZ.SetRow(3, 0.0f  , 0.0f  , 1.0f   , 0.0f);
	matrixZ.SetRow(4, 0.0f  , 0.0f  , 0.0f   , 1.0f);

	return matrixZ * matrixY * matrixX;
}

Matrix Matrix::GenRotation(Quaternion quaternion)
{
	Matrix matrix;

	matrix.SetRow(1, 1 - (2 * pow(quaternion.J(), 2)) - (2 * pow(quaternion.K(), 2))          , 2 * quaternion.I() * quaternion.J() - 2 * quaternion.K() * quaternion.R(), 2 * quaternion.I() * quaternion.K() + 2 * quaternion.J() * quaternion.R(), 0.0f);
	matrix.SetRow(2, 2 * quaternion.I() * quaternion.J() + 2 * quaternion.K() * quaternion.R(), 1 - (2 * pow(quaternion.I(), 2)) - (2 * pow(quaternion.K(), 2))          , 2 * quaternion.J() * quaternion.K() - 2 * quaternion.I() * quaternion.R(), 0.0f);
	matrix.SetRow(3, 2 * quaternion.I() * quaternion.K() - 2 * quaternion.J() * quaternion.R(), 2 * quaternion.J() * quaternion.K() + 2 * quaternion.I() * quaternion.R(), 1 - (2 * pow(quaternion.I(), 2)) - (2 * pow(quaternion.J(), 2))          , 0.0f);
	matrix.SetRow(4, 0.0f                                                                     , 0.0f                                                                     , 0.0f                                                                     , 1.0f);

	return matrix;
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
	matrix.SetRow(4, -xAxis.Dot(position), -yAxis.Dot(position), zAxis.Dot(position)  , 1);

	return matrix;
}

Matrix Matrix::GenProjection(float fov, float aspectRatio, float near, float far)
{
	float size = near * tanf((fov * (3.1415926f / 180.0f)) / 2.0f);
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

Matrix Matrix::Identity()
{
	Matrix result;

	result.SetRow(1, 1, 0, 0, 0);
	result.SetRow(2, 0, 1, 0, 0);
	result.SetRow(3, 0, 0, 1, 0);
	result.SetRow(4, 0, 0, 0, 1);

	return result;
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

Vector3 Matrix::operator*(const Vector3 &rhs)
{
	Vector3 vector;

	vector.SetX(mValues[Matrix::TwoDimToOneDim(0,0,4)] * rhs.X() + mValues[Matrix::TwoDimToOneDim(0,1,4)] * rhs.Y() + mValues[Matrix::TwoDimToOneDim(0,2,4)] * rhs.Z() + mValues[Matrix::TwoDimToOneDim(0,3,4)] * 1);
	vector.SetY(mValues[Matrix::TwoDimToOneDim(1,0,4)] * rhs.X() + mValues[Matrix::TwoDimToOneDim(1,1,4)] * rhs.Y() + mValues[Matrix::TwoDimToOneDim(1,2,4)] * rhs.Z() + mValues[Matrix::TwoDimToOneDim(1,3,4)] * 1);
	vector.SetZ(mValues[Matrix::TwoDimToOneDim(2,0,4)] * rhs.X() + mValues[Matrix::TwoDimToOneDim(2,1,4)] * rhs.Y() + mValues[Matrix::TwoDimToOneDim(2,2,4)] * rhs.Z() + mValues[Matrix::TwoDimToOneDim(2,3,4)] * 1);

	return vector;
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