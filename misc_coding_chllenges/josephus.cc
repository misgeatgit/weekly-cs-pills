#include <cstdlib>
#include <cstdio>

int josephus(int N, int K)
{
    if( N == 1) return N;
    else return ((josephus(N - 1, K) + K - 1) % N) + 1;
}


int main(int argc, char** argv)
{
    if(argc < 3) {
        printf("Needs two arguments (Number of people and number of people to be skipped) \n");
        return 0;
    }
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);

    printf("%d \n", josephus(n, k + 1));

}
