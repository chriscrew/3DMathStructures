//A class for representing a 2d vector or point in space
//written by Kyle Marchev
class Vector2
{
public:
	__declspec(dllexport) Vector2();
	__declspec(dllexport) Vector2(float x, float y);

	float __declspec(dllexport) X();
	float __declspec(dllexport) Y();

	void __declspec(dllexport) SetX(float x);
	void __declspec(dllexport) SetY(float y);

	float __declspec(dllexport) Length();
	float __declspec(dllexport) LengthSquared();

	float __declspec(dllexport) Distance(Vector2 other);
	float __declspec(dllexport) DistanceSquared(Vector2 other);

	float __declspec(dllexport) Dot(Vector2 other);

	void __declspec(dllexport) Normalize();
	Vector2 __declspec(dllexport) Normalized();

private:

	float mX;
	float mY;
};
