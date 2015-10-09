#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


namespace one
{
	int main() {
		int a, b, c;
		cin >> a >> b >> c;
		cout << (a+b+c);
		return 0;
	}
}



namespace two
{
	int main() {
		int x;
		long y;
		long long z;
		char c;
		float f;
		double d;
		scanf("%d %ld %lld %c %f %lf",&x, &y, &z, &c, &f, &d);
		printf("%d\n%ld\n%lld\n%c\n%f\n%lf\n", x, y, z, c, f, d);
		return 0;
	}
}

namespace array
{
	int main() {
		int size;    
		cin >> size;
		int a [size];

		for(int i = 0; i< size; i++)
			cin >> a[i];

		for(int i= size-1; i>=0; i--)
			cout << a[i] << " ";

		return 0;
	}
}

int main()
{
	array::main();
}
