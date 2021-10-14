#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int solution(vector<int> &blocks)
{
    vector<int> maxd_l(blocks.size(), 0);
    vector<int> maxd_r(blocks.size(), 0);

    //find max distance points to the right
    for (int i = 1, bi=0; i < int(blocks.size()); i++)
    {
        if (blocks[i - 1] > blocks[i]){
            bi = i;
            continue;
        }
        maxd_r[bi]++;
    }

    //find max distance points to the left
    for (int i = 1; i < int(blocks.size()); i++)
    {
        if (blocks[i - 1] < blocks[i]){
            continue;
        }
        maxd_l[i] = maxd_l[i-1] + 1;
    }

    int max_dist = maxd_l[0] + maxd_r[0] + 1;

    for (int i = 1; i < int(blocks.size()); i++)
    {
        int maxd = maxd_l[i] + maxd_r[i] + 1;
        max_dist = max(maxd, max_dist);
    }

    return max_dist;
}

int main(char **argv, int argc)
{
    int sz;
    cin >> sz;
    for (int j = 0; j < sz; j++)
    {
        int s;
        cin >> s;
        vector<int> blocks(s-1);
        for (int i = 0 ; i < s-1; i++) {
            cin >> blocks[i];
        }


        for(auto e : blocks) {
            cout << e << " ";
        }
        cout << "\n";
        int expect;
        cin >> expect;
        cout << "ANSWER:" << solution(blocks) << " EXPECTED:" << expect  << endl;
    }


}
