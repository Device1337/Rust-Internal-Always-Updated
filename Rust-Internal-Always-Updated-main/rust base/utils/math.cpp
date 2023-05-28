#include "math.hpp"

#define M_PI_2 1.57079632679489661923
#define M_PI 3.14159265358979323846f
#define M_RADPI	57.295779513082f
#define M_PI_F ((float)(M_PI))
#define RAD2DEG(x) ((float)(x) * (float)(180.f / M_PI_F))
#define DEG2RAD(x) ((float)(x) * (float)(M_PI_F / 180.f))
//#define min(a,b)            (((a) < (b)) ? (a) : (b))
#define powww(a)	(a) * (a)
//#define atan2(a, b) ((float)FC_NTDLL(atan2, (double)(a), (double)(b)))
static volatile const double Tiny = 0x1p-1022;
static volatile const double Infinity = INFINITY;
unsigned short lfsr = 0xACE1u;
unsigned int bit = 0;

using namespace Math;


static inline double2 Math::Mul112(double a, double b)
{
	static const double c = 0x1p27 + 1;

	double
		ap = a * c, bp = b * c,
		a0 = (a - ap) + ap, b0 = (b - bp) + bp,
		a1 = a - a0, b1 = b - b0,
		d0 = a * b,
		d1 = a0 * b0 - d0 + a0 * b1 + a1 * b0 + a1 * b1;
	return double2{ d0, d1 };
}

static inline double2 Math::Mul222(double2 a, double2 b)
{
	static const double c = 0x1p27 + 1;

	double
		ap = a.d0 * c, bp = b.d0 * c,
		a0 = (a.d0 - ap) + ap, b0 = (b.d0 - bp) + bp,
		a1 = a.d0 - a0, b1 = b.d0 - b0,
		m0 = a.d0 * b.d0,
		m1 = a0 * b0 - m0 + a0 * b1 + a1 * b0 + a1 * b1 + (a.d0 * b.d1 + a.d1 * b.d0),
		d0 = m0 + m1,
		d1 = m0 - d0 + m1;
	return double2{ d0, d1 };
}

static inline double Math::Mul121Special(double a, double2 b)
{
	static const double c = 0x1p27 + 1;

	double
		ap = a * c, bp = b.d0 * c,
		a0 = (a - ap) + ap, b0 = (b.d0 - bp) + bp,
		a1 = a - a0, b1 = b.d0 - b0,
		m1 = a0 * b0 - 1 + a0 * b1 + a1 * b0 + a1 * b1 + a * b.d1;
	return m1;
}

static inline double2 Math::Add212RightSmaller(double2 a, double b)
{
	double
		c0 = a.d0 + b,
		c1 = a.d0 - c0 + b + a.d1,
		d0 = c0 + c1,
		d1 = c0 - d0 + c1;
	return double2{ d0, d1 };
}

static inline double Math::Add221RightSmaller(double2 a, double2 b)
{
	double
		c0 = a.d0 + b.d0,
		c1 = a.d0 - c0 + b.d0 + b.d1 + a.d1,
		d0 = c0 + c1;
	return d0;
}

double Math::atan(double x)
{
	// Return arctangent(x) given that 5/3 < x <= 2, with the same properties as atan.
	auto atani5 = [](double x) {
		constexpr double p00 = +0x1.124A85750FB5Cp+00;
		constexpr double p01 = +0x1.D59AE78C11C49p-03;
		constexpr double p02 = -0x1.8AD3C44F10DC3p-04;
		constexpr double p03 = +0x1.2B090AAD5F9DCp-05;
		constexpr double p04 = -0x1.881EC3D15241Fp-07;
		constexpr double p05 = +0x1.8CB82A74E0699p-09;
		constexpr double p06 = -0x1.3182219E21362p-12;
		constexpr double p07 = -0x1.2B9AD13DB35A8p-12;
		constexpr double p08 = +0x1.10F884EAC0E0Ap-12;
		constexpr double p09 = -0x1.3045B70E93129p-13;
		constexpr double p10 = +0x1.00B6A460AC05Dp-14;

		double y = x - 0x1.d555555461337p0;

		return ((((((((((+p10) * y + p09) * y + p08) * y + p07) * y + p06) * y +
			p05) *
			y +
			p04) *
			y +
			p03) *
			y +
			p02) *
			y +
			p01) *
			y +
			p00;
	};
	// Return arctangent(x) given that 4/3 < x <= 5/3, with the same properties as
	// atan.
	auto atani4 = [](double x) {
		constexpr double p00 = +0x1730BD281F69Dp-01;
		constexpr double p01 = +0x1.3B13B13B13B0Cp-02;
		constexpr double p02 = -0x1.22D719C06115Ep-03;
		constexpr double p03 = +0x1.C963C83985742p-05;
		constexpr double p04 = -0x1.135A0938EC462p-06;
		constexpr double p05 = +0x1.13A254D6E5B7Cp-09;
		constexpr double p06 = +0x1.DFAA5E77B7375p-10;
		constexpr double p07 = -0x14AC1342182D2p-10;
		constexpr double p08 = +0x1.25BAD4D85CBE1p-10;
		constexpr double p09 = -0x1.E4EEF429EB680p-12;
		constexpr double p10 = +0x1.B4E30D1BA3819p-14;
		constexpr double p11 = +0x1.0280537F097F3p-15;

		double y = x - 0x1.8000000000003p0;

		return (((((((((((+p11) * y + p10) * y + p09) * y + p08) * y + p07) * y +
			p06) *
			y +
			p05) *
			y +
			p04) *
			y +
			p03) *
			y +
			p02) *
			y +
			p01) *
			y +
			p00;
	};
	// Return arctangent(x) given that 1 < x <= 4 / 3, with the same properties as
	// atan.
	auto atani3 = [](double x) {
		constexpr double p00 = +0x1.B96E5A78C5C40p-01;
		constexpr double p01 = +0x1.B1B1B1B1B1B3Dp-02;
		constexpr double p02 = -0x1.AC97826D58470p-03;
		constexpr double p03 = +0x1.3FD2B9F586A67p-04;
		constexpr double p04 = -0x1.BC317394714B7p-07;
		constexpr double p05 = -0x1.2B01FC60CC37Ap-07;
		constexpr double p06 = +0x1.73A9328786665p-07;
		constexpr double p07 = -0x1.C0B993A09CE31p-08;
		constexpr double p08 = +0x1.2FCDACDD6E5B5p-09;
		constexpr double p09 = +0x1.CBD49DA316282p-13;
		constexpr double p10 = -0x1.0120E602F6336p-10;
		constexpr double p11 = +0x1.A89224FF69018p-11;
		constexpr double p12 = -0x1.883D8959134B3p-12;

		double y = x - 0x1.2aaaaaaaaaa96p0;

		return ((((((((((((+p12) * y + p11) * y + p10) * y + p09) * y + p08) * y +
			p07) *
			y +
			p06) *
			y +
			p05) *
			y +
			p04) *
			y +
			p03) *
			y +
			p02) *
			y +
			p01) *
			y +
			p00;
	};
	// Return arctangent(x) given that 3 / 4 < x <= 1, with the same properties as
	// atan.
	auto atani2 = [](double x) {
		constexpr double p00 = +0x1.700A7C580EA7Ep-01;
		constexpr double p01 = +0x1.21FB781196AC3p-01;
		constexpr double p02 = -0x1.1F6A8499714A2p-02;
		constexpr double p03 = +0x1.41B15E5E8DCD0p-04;
		constexpr double p04 = +0x1.59BC93F81895Ap-06;
		constexpr double p05 = -0x1.63B543EFFA4EFp-05;
		constexpr double p06 = +0x1.C90E92AC8D86Cp-06;
		constexpr double p07 = -0x1.91F7E2A7A338Fp-08;
		constexpr double p08 = -0x1.AC1645739E676p-08;
		constexpr double p09 = +0x1.152311B180E6Cp-07;
		constexpr double p10 = -0x1.265EF51B17DB7p-08;
		constexpr double p11 = +0x1.CA7CDE5DE9BD7p-14;

		double y = x - 0x1.c0000000f4213p-1;

		return (((((((((((+p11) * y + p10) * y + p09) * y + p08) * y + p07) * y +
			p06) *
			y +
			p05) *
			y +
			p04) *
			y +
			p03) *
			y +
			p02) *
			y +
			p01) *
			y +
			p00;
	};
	// Return arctangent(x) given that 1/2 < x <= 3/4, with the same properties as
	// atan.
	auto atani1 = [](double x) {
		constexpr double p00 = +0x1.1E00BABDEFED0p-1;
		constexpr double p01 = +0x1.702E05C0B8155p-1;
		constexpr double p02 = -0x1.4AF2B78215A1Bp-2;
		constexpr double p03 = +0x1.5D0B7E9E69054p-6;
		constexpr double p04 = +0x1.A1247CA5D9475p-4;
		constexpr double p05 = -0x1.519E110F61B54p-4;
		constexpr double p06 = +0x1.A759263F377F2p-7;
		constexpr double p07 = +0x1.094966BE2B531p-5;
		constexpr double p08 = -0x1.09BC0AB7F914Cp-5;
		constexpr double p09 = +0x1F3B7C531AA4Ap-8;
		constexpr double p10 = +0x1.950E69DCDD967p-7;
		constexpr double p11 = -0x1.D88D31ABC3AE5p-7;
		constexpr double p12 = +0x1.10F3E20F6A2E2p-8;

		double y = x - 0x1.4000000000027p-1;

		return ((((((((((((+p12) * y + p11) * y + p10) * y + p09) * y + p08) * y +
			p07) *
			y +
			p06) *
			y +
			p05) *
			y +
			p04) *
			y +
			p03) *
			y +
			p02) *
			y +
			p01) *
			y +
			p00;
	};
	// Return arctangent(x) given that 0x1p-27 < |x| <= 1/2, with the same properties
	// as atan.
	auto atani0 = [](double x) {
		constexpr double p03 = -0x1.555555555551Bp-2;
		constexpr double p05 = +0x1.99999999918D8p-3;
		constexpr double p07 = -0x1.2492492179CA3p-3;
		constexpr double p09 = +0x1.C71C7096C2725p-4;
		constexpr double p11 = -0x1.745CF51795B21p-4;
		constexpr double p13 = +0x1.3B113F18AC049p-4;
		constexpr double p15 = -0x1.10F31279EC05Dp-4;
		constexpr double p17 = +0x1.DFE7B9674AE37p-5;
		constexpr double p19 = -0x1.A38CF590469ECp-5;
		constexpr double p21 = +0x1.56CDB5D887934p-5;
		constexpr double p23 = -0x1.C0EB85F543412p-6;
		constexpr double p25 = +0x1.4A9F5C4724056p-7;

		// Square x.
		double x2 = x * x;

		return ((((((((((((+p25) * x2 + p23) * x2 + p21) * x2 + p19) * x2 + p17) *
			x2 +
			p15) *
			x2 +
			p13) *
			x2 +
			p11) *
			x2 +
			p09) *
			x2 +
			p07) *
			x2 +
			p05) *
			x2 +
			p03) *
			x2 * x +
			x;
	};
	// Return arctangent(x) given that 2 < x, with the same properties as atan.
	auto Tail = [](double x) {
		{
			constexpr double HalfPi = 0x3.243f6a8885a308d313198a2e037ap-1;

			// For large x, generate inexact and return pi/2.
			if (0x1p53 <= x)
				return HalfPi + DBL_EPSILON;
			if (x != x) // isnan
				return x - x;
		}

		constexpr double p03 = -0x1.5555555554A51p-2;
		constexpr double p05 = +0x1.999999989EBCAp-3;
		constexpr double p07 = -0x1.249248E1422E3p-3;
		constexpr double p09 = +0x1.C71C5EDFED480p-4;
		constexpr double p11 = -0x1.745B7F2D72663p-4;
		constexpr double p13 = +0x1.3AFD7A0E6EB75p-4;
		constexpr double p15 = -0x1.104146B1A1AE8p-4;
		constexpr double p17 = +0x1.D78252FA69C1Cp-5;
		constexpr double p19 = -0x1.81D33E401836Dp-5;
		constexpr double p21 = +0x1.007733E06CEB3p-5;
		constexpr double p23 = -0x1.83DAFDA7BD3FDp-7;

		constexpr double p000 = +0x1.921FB54442D18p0;
		constexpr double p001 = +0x1.1A62633145C07p-54;

		double y = 1 / x;

		// Square y.
		double y2 = y * y;

		return p001 -
			((((((((((((+p23) * y2 + p21) * y2 + p19) * y2 + p17) * y2 + p15) *
				y2 +
				p13) *
				y2 +
				p11) *
				y2 +
				p09) *
				y2 +
				p07) *
				y2 +
				p05) *
				y2 +
				p03) *
				y2 * y +
				y) +
			p000;
	};

	if (x < 0)
		if (x < -1)
			if (x < -5 / 3.)
				if (x < -2)
					return -Tail(-x);
				else
					return -atani5(-x);
			else if (x < -4 / 3.)
				return -atani4(-x);
			else
				return -atani3(-x);
		else if (x < -.5)
			if (x < -.75)
				return -atani2(-x);
			else
				return -atani1(-x);
		else if (x < -0x1.d12ed0af1a27fp-27)
			return atani0(x);
		else if (x <= -0x1p-1022)
			// Generate inexact and return x.
			return (DBL_EPSILON + 1) * x;
		else if (x == 0)
			return x;
		else
			// Generate underflow and return x.
			return x * DBL_EPSILON + x;
	else if (x <= +1)
		if (x <= +.5)
			if (x <= +0x1.d12ed0af1a27fp-27)
				if (x < +0x1p-1022)
					if (x == 0)
						return x;
					else
						// Generate underflow and return x.
						return x * DBL_EPSILON + x;
				else
					// Generate inexact and return x.
					return (DBL_EPSILON + 1) * x;
			else
				return atani0(x);
		else if (x <= +.75)
			return +atani1(+x);
		else
			return +atani2(+x);
	else if (x <= +5 / 3.)
		if (x <= +4 / 3.)
			return +atani3(+x);
		else
			return +atani4(+x);
	else if (x <= +2)
		return +atani5(+x);
	else
		return +Tail(+x);
}

float Math::my_atan2(float y, float x)
{
	// https://en.wikipedia.org/wiki/Atan2#Definition (A compact expression with four
		// overlapping half-planes is: ...)
	if (x == 0) {
		if (y > 0.0f)
			return M_PI_2;
		else if (y < 0.0f)
			return -M_PI_2;
		return 0;
	}
	else if (x > 0)
		return atan(y / x);
	else if (x < 0)
		return M_PI + atan(y / x);
	else if (y > 0)
		return M_PI_2 - atan(y / x);
	else if (y < 0)
		return -M_PI_2 - atan(y / x);
	return 0;
}

float Math::abs(float a)
{
	if (a < 0.f) return -a;
	else return a;
}

float Math::my_asin(float x)
{
	float negate = float(x < 0);
	x = abs(x);
	float ret = -0.0187293;
	ret *= x;
	ret += 0.0742610;
	ret *= x;
	ret -= 0.2121144;
	ret *= x;
	ret += 1.5707288;
	ret = 3.14159265358979 * 0.5 - sqrt(1.0 - x) * ret;
	return ret - 2 * negate * ret;
}

float Math::sqrt(float number)
{
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

float Math::sin(float x)
{
	// useful to pre-calculate
	double x2 = x * x;
	double x4 = x2 * x2;

	// Calculate the terms
	// As long as abs(x) < sqrt(6), which is 2.45, all terms will be positive.
	// Values outside this range should be reduced to [-pi/2, pi/2] anyway for
	// accuracy. Some care has to be given to the factorials. They can be
	// pre-calculated by the compiler, but the value for the higher ones will exceed
	// the storage capacity of int. so force the compiler to use unsigned long longs
	// (if available) or doubles.
	double t1 = x * (1.0 - x2 / (2 * 3));
	double x5 = x * x4;
	double t2 = x5 * (1.0 - x2 / (6 * 7)) / (1.0 * 2 * 3 * 4 * 5);
	double x9 = x5 * x4;
	double t3 = x9 * (1.0 - x2 / (10 * 11)) / (1.0 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9);
	double x13 = x9 * x4;
	double t4 = x13 * (1.0 - x2 / (14 * 15)) /
		(1.0 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13);
	double x14 = x13 * x4;
	double t5 =
		x14 * (1.0 - x2 / (18 * 19)) /
		(1.0 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14 * 15 * 16 * 17);
	double x15 = x14 * x4;
	double t6 = x15 * (1.0 - x2 / (22 * 23)) /
		(1.0 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14 * 15 *
			16 * 17 * 18 * 19 * 20 * 21);
	// add some more if your accuracy requires them.
	// But remember that x is smaller than 2, and the factorial grows very fast
	// so I doubt that 2^17 / 17! will add anything.
	// Even t4 might already be too small to matter when compared with t1.

	// Sum backwards
	double result = t6;
	result += t5;
	result += t4;
	result += t3;
	result += t2;
	result += t1;

	return result;
}

float Math::cos(float x)
{
	return sin(x + M_PI_2);
}

float Math::Dot(const Vector3& Vec1, const Vector3& Vec2) {
	return Vec1[0] * Vec2[0] + Vec1[1] * Vec2[1] + Vec1[2] * Vec2[2];
}

float Math::Calc3D_Dist(const Vector3& Src, const Vector3& Dst) {
	return sqrt(powww((Src.x - Dst.x)) + powww((Src.y - Dst.y)) + powww((Src.z - Dst.z)));
}

float Math::Calc2D_Dist(const Vector2& Src, const Vector2& Dst) {
	return sqrt(
		powww(Src.x - Dst.x)
		+
		powww(Src.y - Dst.y)
	);
}

Vector2 Math::CalcAngle(const Vector3& src, const Vector3& dst) {
	Vector3 dir = src - dst;
	float length = dir.Length();
	return Vector2{ RAD2DEG(asin(dir.y / length)), RAD2DEG(-atan2(dir.x, -dir.z)) };
}


Vector2 CalcAngle(Vector3 src, Vector3 dst)
{
	Vector2 angle;
	angle.x = -atan2f(dst.x - src.x, dst.y - src.y) / M_PI * 180.0f;
	angle.y = -asinf((dst.z - src.z) / Calc3D_Dist(src, dst)) * (180.0f / M_PI);

	return angle;
}

/*
__forceinline Vector2 CalcAngle(const Vector3& Src, const Vector3& Dst) {
		Vector3 dir = Src - Dst;
		float length = dir.Length();
		return Vector2{ RAD2DEG(asin(dir.y / length)), RAD2DEG(-atan2(dir.x, -dir.z)) };

*/

void Math::Normalize(float& Yaw, float& Pitch) {
	if (Pitch < -89) Pitch = -89;
	else if (Pitch > 89) Pitch = 89;
	if (Yaw < -360) Yaw += 360;
	else if (Yaw > 360) Yaw -= 360;
}

Vector3 Math::cross_vector(Vector3 first_vec, Vector3 second_vec)
{
	Vector3 returnme = Vector3();
	returnme.x = first_vec.y * second_vec.z - first_vec.z * second_vec.y;
	returnme.y = first_vec.z * second_vec.x - first_vec.x * second_vec.z; //first_vec.x * second_vec.z - first_vec.z * second_vec.x;
	returnme.z = first_vec.x * second_vec.y - first_vec.y * second_vec.x;
	return returnme;
}

Vector4 quaternion_look_rotation(Vector3 forward, Vector3 upDirection)
{
	Vector3 up = upDirection;

	forward.Normalize();

	Vector3 first_vec = forward.Normalize();;
	Vector3 cross_value = Math::cross_vector(up, first_vec);
	Vector3 second_vec = cross_value.Normalize();
	Vector3 third_vec = Math::cross_vector(first_vec, second_vec);

	float m00 = second_vec.x;
	float m01 = second_vec.y;
	float m02 = second_vec.z;

	float m10 = third_vec.x;
	float m11 = third_vec.y;
	float m12 = third_vec.z;

	float m20 = first_vec.x;
	float m21 = first_vec.y;
	float m22 = first_vec.z;

	float num8 = (m00 + m11) + m22;

	Vector4 quaternion = Vector4();

	if (num8 > 0.f)
	{
		float num = Math::sqrt(num8 + 1.f);
		quaternion.w = num * 0.5f;
		num = 0.5f / num;
		quaternion.x = (m12 - m21) * num;
		quaternion.y = (m20 - m02) * num;
		quaternion.z = (m01 - m10) * num;
		return quaternion;
	}

	if ((m00 >= m11) && (m00 >= m22))
	{
		float num7 = Math::sqrt(((1.f + m00) - m11) - m22);
		float num4 = 0.5f / num7;
		quaternion.x = 0.5f * num7;
		quaternion.y = (m01 + m10) * num4;
		quaternion.z = (m02 + m20) * num4;
		quaternion.w = (m12 - m21) * num4;
		return quaternion;
	}
	if (m11 > m22)
	{
		float num6 = Math::sqrt(((1.f + m11) - m00) - m22);
		float num3 = 0.5f / num6;
		quaternion.x = (m10 + m01) * num3;
		quaternion.y = 0.5f * num6;
		quaternion.z = (m21 + m12) * num3;
		quaternion.w = (m20 - m02) * num3;
		return quaternion;
	}

	float num5 = Math::sqrt(((1.f + m22) - m00) - m11);
	float num2 = 0.5f / num5;
	quaternion.x = (m20 + m02) * num2;
	quaternion.y = (m21 + m12) * num2;
	quaternion.z = 0.5f * num5;
	quaternion.w = (m01 - m10) * num2;
	return quaternion;
}

unsigned Math::my_random()
{
	if (!lfsr) {
		lfsr = 0xACE1u; bit = 0;
	}
	bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1;
	return lfsr = (lfsr >> 1) | (bit << 15);
}

float Math::my_floor(float x)
{
	if (x == 0.0)
		return 0;

	union {
		float input;
		int   output;
	} data;

	data.input = x;

	int exp = data.output & (255 << 23);
	exp = exp >> 23;

	int man = data.output & ((1 << 23) - 1);

	int pow = exp - 127;
	int mulFactor = 1;

	int i = (pow < 0) ? (-pow) : (pow); //ABS(pow);
	while (i--)
		mulFactor *= 2;

	unsigned long long denominator = 1 << 23;
	unsigned long long numerator = man + denominator;

	bool negative = (data.output >> 31) != 0;

	if (pow < 0)
		denominator *= mulFactor;
	else
		numerator *= mulFactor;

	float res = 0.0;
	while (numerator >= denominator) {
		res++;
		numerator -= denominator;
	}

	if (negative) {
		res = -res;
		if (numerator != 0)
			res -= 1;
	}

	return res;
}

float Math::my_fmod(float a, float b)
{
	return (a - b * my_floor(a / b));
}