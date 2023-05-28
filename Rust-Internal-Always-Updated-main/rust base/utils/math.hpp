#pragma once
#include <Windows.h>
#include <vector>
#include <cmath>
#include <iostream>
#include "../includes.hpp"

#define M_PI 3.14159265358979323846f
#define M_PI_F ((float)(M_PI))
#define RAD2DEG(x) ((float)(x) * (float)(180.f / M_PI_F))

namespace Math
{

	float sqrt(float n);
}

class Vector3
{
public:
	float x, y, z;

	inline Vector3() {
		x = y = z = 0.0f;
	}

	inline Vector3(float X, float Y, float Z) {
		x = X; y = Y; z = Z;
	}

	inline float operator[](int i) const {
		return ((float*)this)[i];
	}

	inline Vector3& operator-=(float v) {
		x -= v; y -= v; z -= v; return *this;
	}

	inline Vector3 operator*(float v) const {
		return Vector3(x * v, y * v, z * v);
	}

	inline Vector3 operator/(float v) const
	{
		return Vector3(x / v, y / v, z / v);
	}

	inline Vector3& operator+=(const Vector3& v) {
		x += v.x; y += v.y; z += v.z; return *this;
	}

	inline Vector3& operator+=(const float& v) {
		x += v; y += v; z += v; return *this;
	}

	inline Vector3& operator-=(const Vector3& v) {
		x -= v.x; y -= v.y; z -= v.z; return *this;
	}

	inline Vector3 operator-(const Vector3& v) const {
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	inline Vector3 operator+(const Vector3& v) const {
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	inline float Length()
	{
		auto number = (x * x + y * y + z * z);
		long        i;
		float       x2, y;
		const float threehalfs = 1.5F;

		x2 = number * 0.5F;
		y = number;
		i = *(long*)&y; // floating point bit level hacking [sic]
		i = 0x5f3759df - (i >> 1); // Newton's approximation
		y = *(float*)&i;
		y = y * (threehalfs - (x2 * y * y)); // 1st iteration
		y = y * (threehalfs - (x2 * y * y)); // 2nd iteration

		return 1 / y;
	}

	inline Vector3 Normalize()
	{
		float mag = Length();
		if (mag > 0.00001f)
		{
			x = x / mag;
			y = y / mag;
			z = z / mag;
		}
		else
		{
			x = 0;
			y = 0;
			z = 0;
		}
		return *this;
	}

	inline bool IsZero()
	{
		if (this->x == 0 && this->y == 0 && this->z == 0)
			return true;

		return false;
	}

	inline float magnitude2d()
	{
		return sqrtf(
			(this->x * this->x)
			+
			(this->z * this->z));
	}

	inline bool operator==(const Vector3& v) const {
		if (this->x == v.x && this->y == v.y && this->z == v.z)
			return true;
		else
			return false;
	}

	inline bool operator!=(const Vector3& v) const {
		if (this->x == v.x && this->y == v.y && this->z == v.z)
			return false;
		else
			return true;
	}
};

class Vector2 {
public:
	float x, y;

	inline Vector2() {
		x = y = 0.0f;
	}

	inline Vector2 operator/(float v) const {
		return Vector2(x / v, y / v);
	}
	inline Vector2(float X, float Y) {
		x = X; y = Y;
	}

	inline Vector2 operator-(const Vector2& v) const {
		return Vector2(x - v.x, y - v.y);
	}

	inline Vector2 operator+(const Vector2& v) const {
		return Vector2(x + v.x, y + v.y);
	}

	inline Vector2& operator+=(const Vector2& v) {
		x += v.x; y += v.y; return *this;
	}

	inline Vector2& operator-=(const Vector2& v) {
		x -= v.x; y -= v.y; return *this;
	}

	inline Vector2 operator*(const float& v) const {
		return Vector2(x * v, y * v);
	}

	inline bool Zero() const {
		return (x > -0.1f && x < 0.1f && y > -0.1f && y < 0.1f);
	}

	inline Vector2& operator/=(float fl)
	{
		float oofl = 1.0f / fl;
		x *= oofl;
		y *= oofl;
		return *this;
	}

	inline bool operator==(const Vector2& v) const {
		if (this->x == v.x && this->y == v.y)
			return true;
		else
			return false;
	}


	inline Vector2 Clamp()
	{
		if (x > 180)
			x -= 360;
		else if (x < -180)
			x += 360;

		if (y > 180)
			y -= 360;
		else if (y < -180)
			y += 360;

		if (x < -89)
			x = -89;

		if (x > 89)
			x = 89;

		while (y < -180.0f)
			y += 360.0f;

		while (y > 180.0f)
			y -= 360.0f;

		return *this;
	}

	inline float magnitude()
	{
		return Math::sqrt(
			(x * x)
			+
			(y * y)
		);
	}
};

class Vector4 {
public:
	float x, y, z, w;

public:
	inline Vector4() {
		x = y = z = w = 0.0f;
	}

	inline Vector4(float X, float Y, float Z, float W) {
		x = X; y = Y; z = Z; w = W;
	}

	inline float operator[](int i) const {
		return ((float*)this)[i];
	}

	inline bool contains(Vector2 point)
	{
		return point.x >= x && point.x < (x + z) && point.y >= y && point.y < (y + w);
	}
};

class VMatrix
{
public:
	VMatrix()
		: m{ { 0, 0, 0, 0 },
			 { 0, 0, 0, 0 },
			 { 0, 0, 0, 0 },
			 { 0, 0, 0, 0 } }
	{}

	VMatrix(const VMatrix&) = default;

	VMatrix transpose() {
		VMatrix m;

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				m.m[i][j] = this->m[j][i];

		return m;
	}

	void matrix_identity() {
		memset(this, 0, sizeof(VMatrix));
		m[0][0] = 1.0f;
		m[1][1] = 1.0f;
		m[2][2] = 1.0f;
		m[3][3] = 1.0f;
	}

	bool is_empty() {
		if (!m[3][0] && !m[3][1] && !m[3][2] && !m[2][1] && !m[2][0] && !m[2][2])
			return true;

		return false;
	}

	Vector3 operator*(const Vector3& vec) {
		VMatrix m;

		m[3][0] = vec.x;
		m[3][1] = vec.y;
		m[3][2] = vec.z;

		m[0][0] = 1;
		m[1][1] = 1;
		m[2][2] = 1;


		m[0][3] = 0.0f;
		m[1][3] = 0.0f;
		m[2][3] = 0.0f;
		m[3][3] = 1.0f;

		auto result = m * (*this);

		return Vector3{ result[3][0], result[3][1], result[3][2] };
	}

	VMatrix operator*(const VMatrix& _m2) {
		auto _m = *this;

		VMatrix out;
		out[0][0] = _m[0][0] * _m2[0][0] + _m[0][1] * _m2[1][0] + _m[0][2] * _m2[2][0] + _m[0][3] * _m2[3][0];
		out[0][1] = _m[0][0] * _m2[0][1] + _m[0][1] * _m2[1][1] + _m[0][2] * _m2[2][1] + _m[0][3] * _m2[3][1];
		out[0][2] = _m[0][0] * _m2[0][2] + _m[0][1] * _m2[1][2] + _m[0][2] * _m2[2][2] + _m[0][3] * _m2[3][2];
		out[0][3] = _m[0][0] * _m2[0][3] + _m[0][1] * _m2[1][3] + _m[0][2] * _m2[2][3] + _m[0][3] * _m2[3][3];
		out[1][0] = _m[1][0] * _m2[0][0] + _m[1][1] * _m2[1][0] + _m[1][2] * _m2[2][0] + _m[1][3] * _m2[3][0];
		out[1][1] = _m[1][0] * _m2[0][1] + _m[1][1] * _m2[1][1] + _m[1][2] * _m2[2][1] + _m[1][3] * _m2[3][1];
		out[1][2] = _m[1][0] * _m2[0][2] + _m[1][1] * _m2[1][2] + _m[1][2] * _m2[2][2] + _m[1][3] * _m2[3][2];
		out[1][3] = _m[1][0] * _m2[0][3] + _m[1][1] * _m2[1][3] + _m[1][2] * _m2[2][3] + _m[1][3] * _m2[3][3];
		out[2][0] = _m[2][0] * _m2[0][0] + _m[2][1] * _m2[1][0] + _m[2][2] * _m2[2][0] + _m[2][3] * _m2[3][0];
		out[2][1] = _m[2][0] * _m2[0][1] + _m[2][1] * _m2[1][1] + _m[2][2] * _m2[2][1] + _m[2][3] * _m2[3][1];
		out[2][2] = _m[2][0] * _m2[0][2] + _m[2][1] * _m2[1][2] + _m[2][2] * _m2[2][2] + _m[2][3] * _m2[3][2];
		out[2][3] = _m[2][0] * _m2[0][3] + _m[2][1] * _m2[1][3] + _m[2][2] * _m2[2][3] + _m[2][3] * _m2[3][3];
		out[3][0] = _m[3][0] * _m2[0][0] + _m[3][1] * _m2[1][0] + _m[3][2] * _m2[2][0] + _m[3][3] * _m2[3][0];
		out[3][1] = _m[3][0] * _m2[0][1] + _m[3][1] * _m2[1][1] + _m[3][2] * _m2[2][1] + _m[3][3] * _m2[3][1];
		out[3][2] = _m[3][0] * _m2[0][2] + _m[3][1] * _m2[1][2] + _m[3][2] * _m2[2][2] + _m[3][3] * _m2[3][2];
		out[3][3] = _m[3][0] * _m2[0][3] + _m[3][1] * _m2[1][3] + _m[3][2] * _m2[2][3] + _m[3][3] * _m2[3][3];

		return out;
	}

	float* operator[](size_t i) { return m[i]; }
	const float* operator[](size_t i) const { return m[i]; }

	union {
		struct {
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
	};
};

struct Matrix4x4 {
	union {
		struct {
			float        _11, _12, _13, _14;
			float        _21, _22, _23, _24;
			float        _31, _32, _33, _34;
			float        _41, _42, _43, _44;

		}; float m[4][4];
	};
};

namespace Math
{
	Vector3 cross_vector(Vector3 first_vec, Vector3 second_vec);

	typedef struct { double d0, d1; } double2;

	static inline double2 Mul112(double a, double b);

	static inline double2 Mul222(double2 a, double2 b);

	static inline double Mul121Special(double a, double2 b);

	static inline double2 Add212RightSmaller(double2 a, double b);

	static inline double Add221RightSmaller(double2 a, double2 b);

	double atan(double);

	float my_atan2(float y, float x);

	float abs(float a);

	float my_asin(float x);

	float sin(float x);

	float cos(float x);

	float Dot(const Vector3& Vec1, const Vector3& Vec2);

	float Calc3D_Dist(const Vector3& Src, const Vector3& Dst);

	float Calc2D_Dist(const Vector2& Src, const Vector2& Dst);

	Vector2 CalcAngle(const Vector3& Src, const Vector3& Dst);

	void Normalize(float& Yaw, float& Pitch);

	unsigned my_random();
	float my_floor(float x);
	float my_fmod(float a, float b);
}

Vector3 cross_vector(Vector3 first_vec, Vector3 second_vec);
Vector4 quaternion_look_rotation(Vector3 forward, Vector3 upDirection);

#define ImSqrt(x) Math::sqrt(x)
#define ImFabs(x) Math::abs(x)