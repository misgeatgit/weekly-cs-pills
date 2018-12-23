#include <cstdio>
#include <cstdlib>


int main(int argc, char** argv)
{
    int start = atoi(argv[1]);
    int N = atoi(argv[2]);
    int cnt = 0;
    while(cnt < N) {
        bool prime = true;
        for(int i = 2; i <= start / 2; ++i) {
            if ( start % i == 0) {
                prime = false;
                break;
            }
        }

        if(prime) {
            printf("%d ", start);
            ++cnt;
        }
        start++;
    }
}
