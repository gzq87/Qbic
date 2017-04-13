#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <cassert>
#include "commondef.h"
using namespace std;

template<typename T>
class Vec2;

template<typename T>
class Vec3;

template<typename T>
class Vec4;

template<typename T>
class Vec2
{
public:
	union {
		struct
		{
			T x;
			T y;
		};
		struct
		{
			T m_data[2];
		};
	};

public:
	Vec2() :x(T(0)), y(T(0)) {}
	Vec2(T _x, T _y) :x(_x), y(_y) {}
	Vec2(const Vec3<T>& v) :x(v.x), y(v.y) {}
	Vec2(const Vec4<T>& v) :x(v.x), y(v.y) {}

	T& operator[](size_t idx) {
		assert(idx >= 0 && idx < 2);
		return m_data[idx];
	}

	const T& operator[](size_t idx) const {
		assert(idx >= 0 && idx < 2);
		return m_data[idx];
	}

	Vec2 operator+(const Vec2& rhs)
	{
		return Vec2(x + rhs.x, y + rhs.y);
	}

	Vec2 operator-(const Vec2& rhs)
	{
		return Vec2(x - rhs.x, y - rhs.y);
	}

	Vec2 operator-()
	{
		return Vec2(-x, -y);
	}

	Vec2 operator*(const float rhs)
	{
		return Vec2(T(rhs * x), T(rhs * y));
	}

	T Dot(const Vec2& rhs)
	{
		return T(x*rhs.x + y*rhs.y);
	}

	Vec2& operator+=(const Vec2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Vec2& operator-=(const Vec2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	Vec2& operator*=(const float rhs)
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}

	//returns true if the two vectors are exactly equal
	//bool Equals(const Vec2& rhs)
	//{

	//}

	//returns true if the magnitude of their difference is less than EPSILON5
	bool operator==(const Vec2& rhs)
	{
		long double dx = fabsl(x, rhs.x);
		long double dy = fabsl(y, rhs.y);
		return (dx <= EPSILON5 && dy <= EPSILON5);
	}

	float Magnitude()
	{
		return sqrtf(x*x + y*y);
	}

	void Normalize()
	{
		float len = Magnitude();
		//assert(len > EPSILON5);
		if (len > EPSILON5)
		{
			x /= len;
			y /= len;
		} 
		else
		{
			x = T(0);
			y = T(0);
		}
	}

	Vec2 Normalized()
	{
		float len = Magnitude();
		//assert(len > EPSILON5);
		if (len > EPSILON5)
		{
			return Vec2(x / len, y / len);
		} 
		else
		{
			retrun Vec2(0,0);
		}
	}
	
	float Angle(const Vec2& rhs)
	{
		//a.Dot(b) = |a||b|cos(theta)
		float cos_angle = (this->Dot(rhs)) / (this->Magnitude()*rhs.Magnitude());
		return acos(cos_angle);
	}
};

template<typename T>
ostream& operator<<(ostream& os, const Vec2<T>& v)
{
	os << "(" << v.x << "," << v.y << ")";
	return os;
}

template<typename T>
class Vec3
{
public:
	union {
		struct
		{
			T x;
			T y;
			T z;
		};
		struct
		{
			T m_data[3];
		};
	};

public:
	Vec3() :x(T(0)), y(T(0)), z(T(0)) {}
	Vec3(T _x, T _y, T _z) :x(_x), y(_y), z(_z) {}
	Vec3(const Vec2<T>& v) :x(v.x), y(v.y), z(T(0)) {}
	Vec3(const Vec4<T>& v) :x(v.x), y(v.y), z(v.z) {}

	T& operator[](size_t idx) {
		assert(idx >= 0 && idx < 3);
		return m_data[idx];
	}

	const T& operator[](size_t idx) const {
		assert(idx >= 0 && idx < 3);
		return m_data[idx];
	}

	Vec3 operator+(const Vec3& rhs)
	{
		return Vec3(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	Vec3 operator-(const Vec3& rhs)
	{
		return Vec3(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	Vec3 operator-()
	{
		return Vec3(-x, -y, -z);
	}

	Vec3 operator*(const float rhs)
	{
		return Vec3(T(rhs * x), T(rhs * y), T(rhs * z));
	}

	T Dot(const Vec3& rhs)
	{
		return T(x*rhs.x + y*rhs.y + z*rhs.z);
	}

	Vec3 Cross(const Vec3& rhs)
	{
		T _x = y*rhs.z - rhs.y*z;
		T _y = rhs.x*z - x*rhs.z;
		T _z = x*rhs.y - rhs.x*y;
		return Vec3(_x, _y, _z);
	}

	Vec3& operator+=(const Vec3& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	Vec3& operator-=(const Vec3& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	Vec3& operator*=(const float rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		return *this;
	}

	//returns true if the magnitude of their difference is less than EPSILON5
	bool operator==(const Vec3& rhs)
	{
		long double dx = fabsl(x, rhs.x);
		long double dy = fabsl(y, rhs.y);
		long double dz = fabsl(z, rhs.z);
		return (dx <= EPSILON5 && dy <= EPSILON5 && dz <= EPSILON5);
	}

	float Magnitude()
	{
		return sqrtf(x*x + y*y + z*z);
	}

	void Normalize()
	{
		float len = Magnitude();
		//assert(len > EPSILON5);
		if (len > EPSILON5)
		{
			x /= len;
			y /= len;
			z /= len;
		}
		else
		{
			x = T(0);
			y = T(0);
			z = T(0);
		}
	}

	Vec3 Normalized()
	{
		float len = Magnitude();
		//assert(len > EPSILON5);
		if (len > EPSILON5)
		{
			return Vec3(x / len, y / len, z / len);
		}
		else
		{
			retrun Vec3(0, 0, 0);
		}
	}

	float Angle(const Vec3& rhs)
	{
		//a.Dot(b) = |a||b|cos(theta)
		float cos_angle = (this->Dot(rhs)) / (this->Magnitude()*rhs.Magnitude());
		return acos(cos_angle);
	}

};

template<typename T>
ostream& operator<<(ostream& os, const Vec3<T>& v)
{
	os << "(" << v.x << "," << v.y << "," << v.z ")";
	return os;
}

template<typename T>
class Vec4
{
public:
	union {
		struct
		{
			T x;
			T y;
			T z;
			T w;
		};
		struct
		{
			T m_data[4];
		};
	};

public:
	Vec4() :x(T(0)), y(T(0)), z(T(0)), w(T(0)) {}
	Vec4(T _x, T _y, T _z, T _w) :x(_x), y(_y), z(_z), w(_w) {}
	Vec4(const Vec2<T>& v) :x(v.x), y(v.y), z(T(0)), w(T(0)) {}
	Vec4(const Vec3<T>& v) :x(v.x), y(v.y), z(v.z), w(T(0)) {}

	T& operator[](size_t idx) {
		assert(idx >= 0 && idx < 4);
		return m_data[idx];
	}

	const T& operator[](size_t idx) const {
		assert(idx >= 0 && idx < 4);
		return m_data[idx];
	}

	Vec4 operator+(const Vec4& rhs)
	{
		return Vec4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
	}

	Vec4 operator-(const Vec4& rhs)
	{
		return Vec4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
	}

	Vec4 operator-()
	{
		return Vec4(-x, -y, -z, -w);
	}

	Vec4 operator*(const float rhs)
	{
		return Vec4(T(rhs * x), T(rhs * y), T(rhs * z), T(rhs * w));
	}

	T Dot(const Vec4& rhs)
	{
		return T(x*rhs.x + y*rhs.y + z*rhs.z + w*rhs.w);
	}

	Vec4& operator+=(const Vec4& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w;
		return *this;
	}

	Vec4& operator-=(const Vec4& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w;
		return *this;
	}

	Vec4& operator*=(const T& rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		w *= rhs;
		return *this;
	}

	//returns true if the magnitude of their difference is less than EPSILON5
	bool operator==(const Vec4& rhs)
	{
		long double dx = fabsl(x, rhs.x);
		long double dy = fabsl(y, rhs.y);
		long double dz = fabsl(z, rhs.z);
		long double dw = fabsl(w, rhs.w);
		return (dx <= EPSILON5 && dy <= EPSILON5 && dz <= EPSILON5 && dw <= EPSILON5);
	}

	float Magnitude()
	{
		return sqrtf(x*x + y*y + z*z + w*w);
	}

	void Normalize()
	{
		float len = Magnitude();
		//assert(len > EPSILON5);
		if (len > EPSILON5)
		{
			x /= len;
			y /= len;
			z /= len;
			w /= len;
		}
		else
		{
			x = T(0);
			y = T(0);
			z = T(0);
			w = T(0);
		}
	}

	Vec4 Normalized()
	{
		float len = Magnitude();
		//assert(len > EPSILON5);
		if (len > EPSILON5)
		{
			return Vec4(x / len, y / len, z / len, w/len);
		}
		else
		{
			retrun Vec4(0, 0, 0, 0);
		}
	}

	float Angle(const Vec4& rhs)
	{
		//a.Dot(b) = |a||b|cos(theta)
		float cos_angle = (this->Dot(rhs)) / (this->Magnitude()*rhs.Magnitude());
		return acos(cos_angle);
	}

};

template<typename T>
ostream& operator<<(ostream& os, const Vec4<T>& v)
{
	os << "(" << v.x << "," << v.y << "," << v.z << "," << v.w")";
	return os;
}