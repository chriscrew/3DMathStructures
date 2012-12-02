#include "Vector2.h"
#include "Vector3.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

void main()
{
	cout << "Creating the vector2 (5, 5)" << endl;
	Vector2 vector2A;
	vector2A.SetX(5);
	vector2A.SetY(5);

	cout << "The x is " << vector2A.X() << endl;
	cout << "The y is " << vector2A.Y() << endl;

	cout << "The length is " << vector2A.Length() << ", the square length is " << vector2A.LengthSquared() << endl;

	Vector2 vector2B(10, 10);
	cout << "The distance between (5,5) and (10,10) is " << vector2A.Distance(vector2B) << ", the square distance is " << vector2A.DistanceSquared(vector2B) << endl;

	Vector2 vector2C = vector2A.Normalized();
	vector2A.Normalize();
	cout << "normalized, (5, 5) is (" << vector2A.X() << ", " << vector2C.Y() << ")." << endl;

	vector2B.Normalize();
	cout << "The dot product of (5, 5) normalized and (10,10) normalized is " << vector2A.Dot(vector2B) << "." << endl;

	cin.get();
	cin.ignore();

	


	cout << "Creating the vector3 (5, 5, 5)" << endl;
	Vector3 vector3A;
	vector3A.SetX(5);
	vector3A.SetY(5);
	vector3A.SetZ(5);

	cout << "The x is " << vector3A.X() << endl;
	cout << "The y is " << vector3A.Y() << endl;
	cout << "The z is " << vector3A.Z() << endl;

	cout << "The length is " << vector3A.Length() << ", the square length is " << vector3A.LengthSquared() << endl;

	Vector3 vector3B(10, 10, 10);
	cout << "The distance between (5, 5, 5) and (10, 10, 10) is " << vector3A.Distance(vector3B) << ", the square distance is " << vector3A.DistanceSquared(vector3B) << endl;

	Vector3 vector3C = vector3A.Normalized();
	vector3A.Normalize();
	cout << "normalized, (5, 5, 5) is (" << vector3A.X() << ", " << vector3C.Y() << ", " << vector3C.Z() << ")." << endl;

	vector3B.Normalize();
	cout << "The dot product of (5, 5, 5) normalized and (10, 10, 10) normalized is " << vector3A.Dot(vector3B) << "." << endl;

	Vector3 vector3D = vector3A.Cross(vector3B);
	cout << "The cross product of (5, 5, 5) normalized and (10, 10, 10) normalized is (" << vector3D.X() << ", " << vector3D.Y() << ", " << vector3D.Z() << ")." << endl;

	cin.get();
}