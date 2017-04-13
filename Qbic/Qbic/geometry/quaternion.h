#pragma once

#include <iostream>
#include "vector.h"
#include "commondef.h"
using namespace std;

template<typename T>
class Quaternion
{
public:
	union
	{
		struct 
		{
			T m_data[4];
		};
		struct 
		{
			T x;
			T y;
			T z;
			T w;
		};
	};
public:
	Quaternion() {}
	Quaternion(T _x, T _y, T _z, T _w):x(_x), y(_y), z(_z), w(_w) {}
	
	T& operator[](size_t idx) {
		assert(idx < 4);
		return m_data[idx];
	}

	const T& operator[](size_t idx) const {
		assert(idx < 4);
		return m_data[idx];
	}

	static Quaternion<T> AngleAxis(T angle, const Vec3<T>& axis)
	{
		Quaternion<T> q;
		T half_angle = DEG2RAD(angle/2);
		q.x = axis.x * sin(half_angle);
		q.y = axis.y * sin(half_angle);
		q.z = axis.z * sin(half_angle);
		w = cos(half_angle);
		return q;
	}

	T EulerAngles()
	{
		return RAD2DEG(acos(w) * 2);
	}

	void ToAngleAxis(T& angle, Vec3<T>& axis)
	{
		T half_angle = acos(w);
		angle = RAD2DEG(half_angle * 2);
		T sin_half_angle = sin(half_angle);
		axis.x = x / sin_half_angle;
		axis.y = y / sin_half_angle;
		axis.z = z / sin_half_angle;
		
	}

	void SetToIdentity()
	{
		x = y = z = 0;
		w = 1;
	}

	static Quaternion<T> GetIdentityQuaternion()
	{
		return Quaternion<T>(0, 0, 0, 1);
	}

	float Magnitude()
	{
		return sqrtf(x*x + y*y + z*z + w*w);
	}

	Quaternion<T> GetConjugateQuaternion()
	{
		return Quaternion<T>(-x, -y, -z, w);
	}

	void SetToConjugateQuaternion()
	{
		x = -x;
		y = -y;
		z = -y;
	}

	//since we only use identity quaternion, its conjugate and inverse quaternion are equal
	Quaternion<T> GetInversedQuaternion()
	{
		float m = Magnitude();
		assert(m > EPSILON5);
		return Quaternion<T>(-x / m, -y / m, -z / m, w / m);
	}

	static Quaternion<T> Lerp(const Quaternion<T>& q0, const Quaternion<T>& q1, float t)
	{
		float k0 = 1.0f - t;
		float k1 = t;

		Quaternion<T> ret;
		ret.w = q0.w*k0 + q1.w*k1;
		ret.x = q0.x*k0 + q1.x*k1;
		ret.y = q0.y*k0 + q1.y*k1;
		ret.z = q0.z*k0 + q1.z*k1;
		return ret;
	}

	Quaternion<T> Lerp(const Quaternion<T>& q1, float t)
	{
		float k0 = 1.0f - t;
		float k1 = t;

		Quaternion<T> ret;
		ret.w = w*k0 + q1.w*k1;
		ret.x = x*k0 + q1.x*k1;
		ret.y = y*k0 + q1.y*k1;
		ret.z = z*k0 + q1.z*k1;
		return ret;
	}

	static Quaternion<T> Slerp(const Quaternion<T>& q0, const Quaternion<T>& q1, float t)
	{
		Quaternion<T> ret, rhs = q1;
		
		T cosOmega = q0.Dot(q1);//calculate cosine with dot
		if (cosOmega < 0.0f)
		{
			rhs = -rhs;
			cosOmega = -cosOmega;
		}
		
		float k0, k1;
		if (cosOmega > 0.9999f) //linear interpolate
		{
			k0 = 1.0f - t;
			k1 = t;
		} 
		else
		{
			float sinOmega = sqrtf(1.0f - cosOmega * cosOmega);
			float omega = atan2(sinOmega, cosOmega);
			float oneOverSinOmega = 1.0f / sinOmega;
			k0 = sin((1.0f - t) * omega) * oneOverSinOmega;
			k1 = sin(t * omega) * oneOverSinOmega;
		}
		
		ret.w = q0.w*k0 + q1.w*k1;
		ret.x = q0.x*k0 + q1.x*k1;
		ret.y = q0.y*k0 + q1.y*k1;
		ret.z = q0.z*k0 + q1.z*k1;

		return ret;

	}

	Quaternion<T> Slerp(const Quaternion<T>& q1, float t)
	{
		Quaternion<T> ret, rhs = q1;

		T cosOmega = this->Dot(q1);//calculate cosine with dot
		if (cosOmega < 0.0f)
		{
			rhs = -rhs;
			cosOmega = -cosOmega;
		}

		float k0, k1;
		if (cosOmega > 0.9999f) //linear interpolate
		{
			k0 = 1.0f - t;
			k1 = t;
		}
		else
		{
			float sinOmega = sqrtf(1.0f - cosOmega * cosOmega);
			float omega = atan2(sinOmega, cosOmega);
			float oneOverSinOmega = 1.0f / sinOmega;
			k0 = sin((1.0f - t) * omega) * oneOverSinOmega;
			k1 = sin(t * omega) * oneOverSinOmega;
		}

		ret.w = w*k0 + q1.w*k1;
		ret.x = x*k0 + q1.x*k1;
		ret.y = y*k0 + q1.y*k1;
		ret.z = z*k0 + q1.z*k1;

		return ret;
	}

	T Dot(const Quaternion<T>& rhs)
	{
		return x*rhs.x + y*rhs.y + z*rhs.z + w*rhs.w;
	}
	
	Quaternion<T> Cross(const Quaternion<T>& rhs)
	{
		T _w = w*rhs.w - x*rhs.x - y*rhs.y - z*rhs.z;
		T _x = w*rhs.x + x*rhs.w + y*rhs.z - z*rhs.y;
		T _y = w*rhs.y + y*rhs.w + z*rhs.x - x*rhs.z;
		T _z = w*rhs.z + z*rhs.w + x*rhs.y - y*rhs.x;
		return Quaternion<T>(_x, _y, _z, _w);
	}

	
	Quaternion<T> operator*(T rhs)
	{
		return Quaternion<T>(x*rhs, y*rhs, z*rhs, w*rhs);
	}

	Quaternion<T>& operator*=(T rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		w *= rhs;
		return *this;
	}

	Quaternion<T> operator-()
	{
		return Quaternion<T>(-x, -y, -z, -w);
	}

	bool operator==(const Quaternion<T>& rhs)
	{
		return (fabsf(this->Dot(rhs) - 1) < EPSILON3);
	}
	
};

template<typename T>
ostream& operator<<(ostream& os, const Quaternion<T>& q)
{
	os << "(" << q.x << "," << q.y << "," << q.z << "," << q.w")";
	return os;
}