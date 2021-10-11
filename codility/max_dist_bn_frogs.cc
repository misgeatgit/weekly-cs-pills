#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int solution(vector<int> &blocks)
{
    vector<int> maxd_l(blocks.size(), -1);
    vector<int> maxd_r(blocks.size(), -1);
    maxd_l[0] = 0;
    maxd_r[0] = 0;

    //init first block
    for (int i = 1; i < int(blocks.size()); i++)
    {
        if (blocks[i - 1] > blocks[i])
            break;
        maxd_r[0]++;
    }

    int max_dist = maxd_r[0] + 1;

    for (int i = 1; i < int(blocks.size()); i++)
    {
        int J = i, K = i;
        if (maxd_r[K - 1] == -1 or blocks[K+1] >= blocks[K])
        {
            while (K + 1 < blocks.size() and blocks[K + 1] >= blocks[K])
                K++;
            maxd_r[i] = K - i;
        }
        else
        {
            K = K + maxd_r[K - 1] - 1;
        }

        if (maxd_l[J - 1] == -1 or blocks[J] <= blocks[J-1])
        {
            while (J - 1 > 0 and blocks[J] <= blocks[J - 1])
                J--;
            maxd_l[i] = i - J;
        }
        else
        {
            J = J - maxd_l[J - 1] - 1;
        }

        max_dist = max(K - J + 1, max_dist);
    }

    return max_dist;
}

int main(char **argv, int argc)
{
    int sz;
    cin >> sz;
    vector<int> blocks(sz);
    for (int i = 0; i < sz; i++)
    {
        cin >> blocks[i];
    }
    for(auto e : blocks) {
        cout << e << " ";
    }
    cout << "\n";


    cout << solution(blocks) << endl;
}
