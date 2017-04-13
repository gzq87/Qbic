#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <cassert>
#include "commondef.h"
#include "vector.h"
using namespace std;

template<typename T>
class Mat4
{
public:
	T m_data[4][4];
public:
	Mat4(){}
	Mat4(void *ary) //an array contains 16 members of type T
	{
		memcpy((void*)m_data, (void*)ary, sizeof(T)*16);
	}

	void SetToIdentity()
	{
		memset((void*)m_data, 0, sizeof(T) * 16);
		m_data[0][0] = T(1);
		m_data[1][1] = T(1);
		m_data[2][2] = T(1);
		m_data[3][3] = T(1);
	}

	void SetToZero()
	{
		memset((void*)m_data, 0, sizeof(T) * 16);
	}

	static Mat4<T> GetIdentityMat()
	{
		Mat4<T> ret;
		ret.SetToIdentity();
		return ret;
	}

	static Mat4<T> GetZeroMat()
	{
		Mat4<T> ret;
		ret.SetToZero();
		return ret;
	}

	T* operator[](size_t idx)
	{
		assert(idx < 4);
		return m_data[idx];
	}

	const T* operator[](size_t idx) const
	{
		assert(idx < 4);
		return m_data[idx];
	}

	Mat4<T> operator+(const Mat4<T>& rhs)
	{
		T values[16];
		int idx = 0;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				values[idx++] = m_data[i][j] + rhs[i][j];
			}
		}
		return Mat4<T>((void*)values);
	}

	Mat4<T> operator-(const Mat4<T>& rhs)
	{
		T values[16];
		int idx = 0;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				values[idx++] = m_data[i][j] - rhs[i][j];
			}
		}
		return Mat4<T>((void*)values);
	}

	Mat4<T> operator*(const Mat4<T>& rhs)
	{
		Mat4<T> ret;
		ret.SetToZero();
		for (int i = 0; i < 4; ++i)
		{
			ret[0][0] += m_data[0][i] * rhs[i][0];
			ret[0][1] += m_data[0][i] * rhs[i][1];
			ret[0][2] += m_data[0][i] * rhs[i][2];
			ret[0][3] += m_data[0][i] * rhs[i][3];

			ret[1][0] += m_data[1][i] * rhs[i][0];
			ret[1][1] += m_data[1][i] * rhs[i][1];
			ret[1][2] += m_data[1][i] * rhs[i][2];
			ret[1][3] += m_data[1][i] * rhs[i][3];

			ret[2][0] += m_data[2][i] * rhs[i][0];
			ret[2][1] += m_data[2][i] * rhs[i][1];
			ret[2][2] += m_data[2][i] * rhs[i][2];
			ret[2][3] += m_data[2][i] * rhs[i][3];

			ret[3][0] += m_data[3][i] * rhs[i][0];
			ret[3][1] += m_data[3][i] * rhs[i][1];
			ret[3][2] += m_data[3][i] * rhs[i][2];
			ret[3][3] += m_data[3][i] * rhs[i][3];
		}
		return ret;
	}

	Mat4<T>& operator+=(const Mat4<T>& rhs)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				m_data[i][j] += rhs[i][j];
			}
		}
		return *this;
	}

	Mat4<T>& operator-=(const Mat4<T>& rhs)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				m_data[i][j] -= rhs[i][j];
			}
		}
		return *this;
	}
	
	Mat4<T>& operator*=(const Mat4<T>& rhs)
	{
		Mat4<T> ret;
		ret.SetToZero();
		for (int i = 0; i < 4; ++i)
		{
			ret[0][0] += m_data[0][i] * rhs[i][0];
			ret[0][1] += m_data[0][i] * rhs[i][1];
			ret[0][2] += m_data[0][i] * rhs[i][2];
			ret[0][3] += m_data[0][i] * rhs[i][3];

			ret[1][0] += m_data[1][i] * rhs[i][0];
			ret[1][1] += m_data[1][i] * rhs[i][1];
			ret[1][2] += m_data[1][i] * rhs[i][2];
			ret[1][3] += m_data[1][i] * rhs[i][3];

			ret[2][0] += m_data[2][i] * rhs[i][0];
			ret[2][1] += m_data[2][i] * rhs[i][1];
			ret[2][2] += m_data[2][i] * rhs[i][2];
			ret[2][3] += m_data[2][i] * rhs[i][3];

			ret[3][0] += m_data[3][i] * rhs[i][0];
			ret[3][1] += m_data[3][i] * rhs[i][1];
			ret[3][2] += m_data[3][i] * rhs[i][2];
			ret[3][3] += m_data[3][i] * rhs[i][3];
		}
		memcpy((void*)m_data, (void*)ret.m_data, sizeof(T) * 16);
		return *this;
	}

	Mat4<T> Transposed()
	{
		Mat4<T> ret;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				ret[i][j] = m_data[j][i];
			}
		}
		return ret;
	}

	void Transpose()
	{
		Mat4<T> m;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				m[i][j] = m_data[j][i];
			}
		}
		memcpy((void*)m_data, (void*)m.m_data, sizeof(T) * 16);
	}

	Vec4<T> GetRow(size_t idx)
	{
		assert(idx < 4);
		Vec4<T> ret(m_data[idx][0], m_data[idx][1], m_data[idx][2], m_data[idx][3]);
		return ret;
	}

	void SetRow(size_t idx, const Vec4<T>& v)
	{
		assert(idx < 4);
		memcpy((void*)(m_data[idx]), (void*)(v.m_data), sizeof(T) * 4);
	}

	Vec4<T> GetCol(size_t idx)
	{
		assert(idx < 4);
		Vec4<T> ret(m_data[0][idx], m_data[1][idx], m_data[2][idx], m_data[3][idx]);
		return ret;
	}

	void SetCol(size_t idx, const Vec4<T>& v)
	{
		assert(idx < 4);
		m_data[0][idx] = v[0];
		m_data[1][idx] = v[1];
		m_data[2][idx] = v[2];
		m_data[3][idx] = v[3];
	}
	
	Vec4<T> operator*(const Vec4<T>& rhs)
	{
		Vec4<T> ret;
		for (int i = 0; i < 4; ++i)
		{
			ret[i] = m_data[i][0] * rhs[0] + m_data[i][1] * rhs[1] + m_data[i][2] * rhs[2] + m_data[i][3] * rhs[3];
		}
		return ret;
	}

	Vec3<T> MultiplyPoint(const Vec3<T>& rhs)
	{
		Vec4<T> vec(rhs.x, rhs.y, rhs.z, T(1));
		Vec4<T> temp = (*this)*vec;
		return Vec3<T>(temp);
	}

	Vec3<T> MultiplyVector(const Vec3<T>& rhs)
	{
		Vec4<T> vec(rhs.x, rhs.y, rhs.z, T(0));
		Vec4<T> temp = (*this)*vec;
		return Vec3<T>(temp);
	}

	static Mat4<T> GetTranslateMat(const Vec3<T>& v)
	{
		Mat4<T> ret;
		ret.SetToIdentity();
		ret[0][3] = v.x;
		ret[1][3] = v.y;
		ret[2][3] = v.z;
		return ret;
	}

	static Mat4<T> GetTranslateMat(T x, T y, T z)
	{
		Mat4<T> ret;
		ret.SetToIdentity();
		ret[0][3] = x;
		ret[1][3] = y;
		ret[2][3] = z;
		return ret;
	}

	static Mat4<T> GetRotateMat(float theta, AxisName axis)
	{
		float sin_theta = sinf(DEG2RAD(theta));
		float cos_theta = cosf(DEG2RAD(theta));
		Mat4<T> ret;
		ret.SetToIdentity();
		switch (axis)
		{
		case AN_X:
			ret[1][1] = cos_theta;
			ret[1][2] = -sin_theta;
			ret[2][1] = sin_theta;
			ret[2][2] = cos_theta;
			break;
		case AN_Y:
			ret[0][0] = cos_theta;
			ret[0][2] = sin_theta;
			ret[2][0] = -sin_theta;
			ret[2][2] = cos_theta;
			break;
		case AN_Z:
			ret[0][0] = cos_theta;
			ret[0][1] = -sin_theta;
			ret[1][0] = sin_theta;
			ret[1][1] = cos_theta;
			break;
		default:
			break;
		}
		
		return ret;
	}

	static Mat4<T> GetRotateMat(float theta, const Vec3<T>& axis)
	{
		float sin_theta = sinf(DEG2RAD(theta));
		float cos_theta = cosf(DEG2RAD(theta));
		Mat4<T> ret;
		ret.SetToIdentity();
		
		ret[0][0] = cos_theta + axis.x * axis.x * (1 - cos_theta);
		ret[0][1] = axis.x * axis.y * (1 - cos_theta) - axis.z * sin_theta;
		ret[0][2] = axis.x * axis.z * (1 - cos_theta) + axis.y * sin_theta;
		
		ret[1][0] = axis.y * axis.x * (1 - cos_theta) + axis.z * sin_theta;
		ret[1][1] = cos_theta + axis.y * axis.y * (1 - cos_theta);
		ret[1][2] = axis.y * axis.z * (1 - cos_theta) - axis.x * sin_theta;

		ret[2][0] = axis.z * axis.x * (1 - cos_theta) - axis.y * sin_theta;
		ret[2][1] = axis.z * axis.y * (1 - cos_theta) + axis.x * sin_theta;
		ret[2][2] = cos_theta + axis.z * axis.z * (1 - cos_theta);

		return ret;
	}

	static Mat4<T> GetScaleMat(const Vec3<T>& v)
	{
		Mat4<T> ret;
		ret.SetToIdentity();
		ret[0][0] = v.x;
		ret[1][1] = v.y;
		ret[2][2] = v.z;
		return ret;
	}

	static Mat4<T> GetScaleMat(T x, T y, T z)
	{
		Mat4<T> ret;
		ret.SetToIdentity();
		ret[0][0] = x;
		ret[1][1] = y;
		ret[2][2] = z;
		return ret;
	}

	T Determinant()
	{
		T result = 
			m_data[0][0] * m_data[1][1] * m_data[2][2] * m_data[3][3]
			- m_data[0][0] * m_data[1][1] * m_data[2][3] * m_data[3][2]
			- m_data[0][0] * m_data[1][2] * m_data[2][1] * m_data[3][3]
			+ m_data[0][0] * m_data[1][2] * m_data[2][3] * m_data[3][1]
			+ m_data[0][0] * m_data[1][3] * m_data[2][1] * m_data[3][2]
			- m_data[0][0] * m_data[1][3] * m_data[2][2] * m_data[3][1]
			- m_data[0][1] * m_data[1][0] * m_data[2][2] * m_data[3][3]
			+ m_data[0][1] * m_data[1][0] * m_data[2][3] * m_data[3][2]
			- m_data[0][1] * m_data[1][2] * m_data[2][0] * m_data[3][3]
			+ m_data[0][1] * m_data[1][2] * m_data[2][3] * m_data[3][0]
			+ m_data[0][1] * m_data[1][3] * m_data[2][0] * m_data[3][2]
			- m_data[0][1] * m_data[1][3] * m_data[2][2] * m_data[3][0]
			+ m_data[0][2] * m_data[1][0] * m_data[2][1] * m_data[3][3]
			- m_data[0][2] * m_data[1][0] * m_data[2][3] * m_data[3][1]
			- m_data[0][2] * m_data[1][1] * m_data[2][0] * m_data[3][3]
			+ m_data[0][2] * m_data[1][1] * m_data[2][3] * m_data[3][0]
			+ m_data[0][2] * m_data[1][3] * m_data[2][0] * m_data[3][1]
			- m_data[0][2] * m_data[1][3] * m_data[2][1] * m_data[3][0]
			- m_data[0][3] * m_data[1][0] * m_data[2][1] * m_data[3][2]
			+ m_data[0][3] * m_data[1][0] * m_data[2][2] * m_data[3][1]
			- m_data[0][3] * m_data[1][1] * m_data[2][0] * m_data[3][2]
			+ m_data[0][3] * m_data[1][1] * m_data[2][2] * m_data[3][0]
			+ m_data[0][3] * m_data[1][2] * m_data[2][0] * m_data[3][1]
			- m_data[0][3] * m_data[1][2] * m_data[2][1] * m_data[3][0];
		return result;
	}

	//计算余子式，如果with_sign为true，则计算代数余子式
	T GetCofactor(size_t r, size_t c, bool with_sign)
	{
		assert(r < 4 && c < 4);
		T temp[3][3];
		int ii = 0, jj;
		for (int i = 0; i < 4; ++i)
		{
			if (i == r)
			{
				continue;
			}
			jj = 0;
			for (int j = 0; j < 4; ++j)
			{
				if (j == c)
				{
					continue;
					
				}
				temp[ii][jj] = m_data[i][j];
				++jj;
			}
			++ii;
		}
		T value = temp[0][0] * (temp[1][1] * temp[2][2] - temp[1][2] * temp[2][1])
			- temp[0][1] * (temp[1][0] * temp[2][2] - temp[1][2] * temp[2][0])
			+ temp[0][2] * (temp[1][0] * temp[2][1] - temp[1][1] * temp[2][0]);
		if (with_sign)
		{
			if ((r + c) % 2)
			{
				value = -value;
			}
		}
		if (value == -0)
		{
			value = 0;
		}
		return value;
	}

	Mat4<T> GetInversedMat()
	{
		float det = this->Determinant();
		assert(fabsf(det) > EPSILON5);
		Mat4<T> ret;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				ret[i][j] = GetCofactor(j, i, true) / det;
			}
		}
		return ret;
	}

	static Mat4<T> GetLookAtMat(const Vec3<T>& camPos, const Vec3<T>& frontDir, const Vec3<T>& upDir)
	{
		Vec3<T> zaxis = (-frontDir).Normalized();
		Vec3<T> xaxis = ((upDir.Normalized()).Cross(zaxis)).Normalized();
		Vec3<T> yaxis = zaxis.Cross(xaxis);

		Mat4<T> translation, rotation;
		translation.SetToIdentity();
		rotation.SetToIdentity();
		
		translation[3][0] = -camPos.x;
		translation[3][1] = -camPos.y;
		translation[3][2] = -camPos.z;

		rotation[0][0] = xaxis.x;
		rotation[0][1] = xaxis.y;
		rotation[0][2] = xaxis.z;
		rotation[1][0] = yaxis.x;
		rotation[1][1] = yaxis.y;
		rotation[1][2] = yaxis.z;
		rotation[2][0] = zaxis.x;
		rotation[2][1] = zaxis.y;
		rotation[2][2] = zaxis.z;

		return rotation * translation;
	}

	static Mat4<T> GetOrthoMat(T left, T right, T bottom, T top, T zNear, T zFar)
	{
		Mat4<T> ret;
		ret.SetToIdentity();
		
		ret[0][0] = 2 / (right - left);
		ret[1][1] = 2 / (top - bottom);
		ret[2][2] = -2 / (zFar - zNear);
		ret[0][3] = -(right + left) / (right - left);
		ret[1][3] = -(top + bottom) / (top - bottom);
		ret[2][3] = -(zFar + zNear) / (zFar - zNear);

		return ret;
	}

	static Mat4<T> GetPerspectiveMat(T left, T right, T bottom, T top, T zNear, T zFar)
	{
		Mat4<T> ret;
		ret.SetToZero();

		ret[0][0] = 2 * zNear / (right - left);
		ret[0][2] = (right + left) / (right - left);
		ret[1][1] = 2 * zNear / (top - bottom);
		ret[1][2] = (top + bottom) / (top - bottom);
		ret[2][2] = -(zFar + zNear) / (zFar - zNear);
		ret[2][3] = -2 * zFar*zNear / (zFar - zNear);
		ret[3][2] = -1;


			return ret;
	}

	static Mat4<T> GetPerspectiveMat(T fov, T aspect, T zNear, T zFar)
	{
		Mat4<T> ret;
		ret.SetToZero();

		T cot_half_theta = 1 / tan(DEG2RAD(fov / 2));

		ret[0][0] = cot_half_theta / aspect;
		ret[1][1] = cot_half_theta;
		ret[2][2] = -(zFar + zNear) / (zFar - zNear);
		ret[2][3] = -2 * zFar*zNear / (zFar - zNear);
		ret[3][2] = -1;

		return ret;
	}

};

template<typename T>
ostream& operator<<(ostream& os, const Mat4<T>& m)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			cout << m.m_data[i][j] << ",";
		}
		cout << endl;
	}
	return os;
}
