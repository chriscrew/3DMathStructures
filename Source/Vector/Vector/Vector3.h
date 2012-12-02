//A class for representing a 3d vector or point in space
//written by Kyle Marchev
class Vector3
{
public:
	__declspec(dllexport) Vector3();
	__declspec(dllexport) Vector3(float x, float y, float z);

	float __declspec(dllexport) X();
	float __declspec(dllexport) Y();
	float __declspec(dllexport) Z();

	void __declspec(dllexport) SetX(float x);
	void __declspec(dllexport) SetY(float y);
	void __declspec(dllexport) SetZ(float z);

	float __declspec(dllexport) Length();
	float __declspec(dllexport) LengthSquared();

	float __declspec(dllexport) Distance(Vector3 other);
	float __declspec(dllexport) DistanceSquared(Vector3 other);

	float __declspec(dllexport) Dot(Vector3 other);
	Vector3 __declspec(dllexport) Cross(Vector3 other);

	void __declspec(dllexport) Normalize();
	Vector3 __declspec(dllexport) Normalized();

private:

	float mX;
	float mY;
	float mZ;
};
