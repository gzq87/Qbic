#include <iostream>
using namespace std;
#include "../../Qbic/geometry/vector.h"
#include "../../Qbic/geometry/matrix.h"


int main()
{
	/*
	Vec2<float> vec;
	cout << vec << endl;
	Vec2<float> vec2(1.0f, 2.0f);
	cout << vec2 << endl;
	cout << vec2[0] << endl;
	*/
	//Mat4<float> m = Mat4<float>::GetIdentityMat();
	//cout << m;
	//m.SetToZero();
	//cout << m;
	/*
	float values[] = {
		1, 0, 0, 1,
		0, 1, 0, 2,
		0, 0, 1, 3,
		0, 0, 0, 1
	};
	Mat4<float> m((void*)values);
	cout << m << endl;
	cout << m.Determinant() << endl;
	Mat4<float> im = m.GetInversedMat();
	cout << im << endl;
	cout << (m*im) << endl;
	*/

	Mat4<float> r1 = Mat4<float>::GetRotateMat(30.0f, AN_X);
	Mat4<float> r2 = Mat4<float>::GetRotateMat(30.0f, Vec3<float>(1.0f, 0.0f, 0.0f));
	cout << r1 << endl;
	cout << r2 << endl;
	system("pause");
	return 0;
}