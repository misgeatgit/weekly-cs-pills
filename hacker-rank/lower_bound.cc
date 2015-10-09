#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
	int size;
	vector<int> v;
	scanf("%d",&size); 
	v.reserve(size);
	int val;
	for(int i=0; i<size; i++){
		scanf("%d",&val);
		v.push_back(val);
	}

	int qsize;
	cin >> qsize;
	for(int i=0; i < qsize; i++)
	{
		int lookfor;
		cin >> lookfor;                

		//auto it =stable_partition(v.begin(),v.end(),[lookfor](int i){ return i < lookfor;});
		auto it = lower_bound(v.begin(),v.end(),lookfor);
		int pos = it - v.begin();
		if(v[pos] == lookfor)
			cout << "Yes " << pos+1 << "\n";
		else 
			cout << "No "<<pos+1 << "\n";

	}
}

