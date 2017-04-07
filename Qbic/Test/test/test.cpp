#include <iostream>
using namespace std;
#include "../../Qbic/geometry/vector.h"

int main()
{
	Vec2<float> vec;
	cout << vec << endl;
	Vec2<float> vec2(1.0f, 2.0f);
	cout << vec2 << endl;
	cout << vec2[0] << endl;
	system("pause");
	return 0;
}