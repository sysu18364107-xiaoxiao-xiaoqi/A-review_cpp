#include<iostream>
using namespace std;
#define day 7
int main()
{
	float fl = 3.14f;
	double dl = 3.14;

	cout << fl << endl;
	cout << dl << endl;

	cout << "float sizeof = " << sizeof(fl) << endl;
	cout << "double sizeof =" << sizeof(dl) << endl;

	float f2 = 3e2;
	cout << "f2 = " << f2 << endl;
	float f3 = 3e-2;
	cout << "f3 =" << f3 << endl;

	system("pause");
	
	return 0;

	cout << "short " << sizeof(short)<<endl;
	cout << "long " << sizeof(long) << endl;
	cout << "int " << sizeof(int) << endl;
	cout << "long long" << sizeof(long long) << endl;
	system("pause");
	return 0;
}
