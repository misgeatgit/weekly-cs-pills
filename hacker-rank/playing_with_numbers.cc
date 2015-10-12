#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

// Sum_j = Sum_i0_to_n( abs ( a_i + sum_j0_n(q_j)))
int main() {     
	int size;
	cin >> size;

	int arr [size];
	for(int i=0; i< size; i++)
		int f = scanf("%d",&arr[i]);    

	int qsize;
	cin >> qsize;

	long long int  QSUM [qsize];
	cin >> QSUM[0];
	int temp;
	for(int i=1; i< qsize; i++){        
		int f = scanf("%d",&temp);
		QSUM[i] = QSUM[i-1] + temp;
	}    

	sort(arr, arr+size); 

	long long int ARR_SUM[size]; 
	ARR_SUM[0] = arr[0];    
	for(int i = 1 ; i < size; i++){
		ARR_SUM[i] = arr[i] + ARR_SUM[i-1];       
	}

	long long int sum=0;    
	// if sumj+arr[i] > 0 then sumj+arr[i+...] > 0 so sum = sum_i_k(ai) + k*sumj
	// and if sumj+arr[i] < 0 then sumj+arr[k] < 0 for k < i so sum = abs(sum_0_i(ai) + (size-i)*sumj)
	for(int i = 0; i < qsize; i++ ){
		for(int j=0; j< size; j++){  
			//Left right check over the sorted order.
			if(QSUM[i]+arr[j] >= 0 ){               
				sum = ((size-j)*QSUM[i] + (ARR_SUM[size-1]-ARR_SUM[j] + arr[j]));
				for(int k = 0; k < j; k++) sum += abs(arr[k]+QSUM[i]);
				break;
			}
			else if(QSUM[i] + arr[size-j-1] < 0){                
				sum = abs((size-j)*QSUM[i] + ARR_SUM[size-j-1] ); 
				for(int k = size-j; k < size; k++) sum += abs(arr[k]+QSUM[i]);                
				break;
			}
		}          
		printf("%lld\n",sum);
		sum = 0;
	}

	return 0;
}

