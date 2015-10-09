/*
 * Author: Misgana Bayetta <https://www.github.com/misgeatgit>
 *
 * Solution for https://www.hackerrank.com/challenges/matrix-rotation-alg
 *
 *
 *
 */

#include <iostream>

using namespace std;

int main() {
    int M,N,R;   
    cin >> M; cin >> N; cin >> R;
    int matrix [M][N];
    for(int i = 0; i<M; i++){
        for(int j = 0; j<N; j++){
            cin >> matrix[i][j]; 
        }
    }

    int RINGS=0;
    M < N ? RINGS = M/2 : RINGS = N/2; 

    int damntemp;
    int tempu,templ; // hold the last poped element from lower and upper rotation.   
    for(int j=0; j < RINGS; j++){            
        const int ROWU = j; 
        const int ROWL = M-1-j;
        const int CLEFT = j;
        const int CRIGHT = N-1-j;
        const int RING_M = ROWL-ROWU+1;
        const int RING_N = CRIGHT-CLEFT+1;
        const int NORMAL_BOUND = R % (2*(RING_M+RING_N)-4);//Doing this brought huge performance. 
        
        for(int i=0; i < NORMAL_BOUND ; i++){
            //Rotate upper and lower edges of the ring
            tempu = matrix [ROWU][CRIGHT-1];
            matrix[ROWU][CRIGHT-1] = matrix[ROWU][CRIGHT]; 
            for(int c=CRIGHT-1; c > CLEFT; c--){              
                damntemp = matrix[ROWU][c-1];
                matrix[ROWU][c-1] = tempu;
                tempu = damntemp;              
            }            
            templ = matrix [ROWL][CLEFT+1];
            matrix[ROWL][CLEFT+1] = matrix[ROWL][CLEFT];                
            for(int c = CLEFT+1 ; c < CRIGHT; c++){               
                damntemp = matrix[ROWL][c+1];
                matrix[ROWL][c+1] = templ;
                templ = damntemp;                
            }

            //Rotate left and righ edges of the ring
            for(int r = ROWU ; r< ROWL; r++){                        
                damntemp = matrix[r+1][CLEFT];
                matrix[r+1][CLEFT] = tempu;
                tempu = damntemp;                 
            }
            for(int r = ROWL; r > ROWU; r--){                        
                damntemp = matrix[r-1][CRIGHT];
                matrix[r-1][CRIGHT] = templ;
                templ = damntemp;   
            }

        }
    }    

    for(int i=0 ; i < M; i++){
        for(int j=0; j < N; j++){
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}

