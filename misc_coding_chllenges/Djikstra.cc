#include <bits/stdc++.h>
#include <cassert>
#include <iterator>
#include <vector>
#include <stack>

using namespace std;

vector<string> split_string(string);

// Complete the shortestReach function below.
vector<int> shortestReach(int n, vector<vector<int>> edges, int s)
{
    n += 1;
    int distance [n];
    for( int i = 0; i < n; i++) distance[i] = -1;

    bool visited[n] = {false};
    int via[n] = { -1};
    int dist_pair [n][n];

    vector<int> adj [n];
    for(int i = 0; i < n; i++)
        adj[i] = {};

    for(vector<int>& vec : edges) {
        assert(vec.size() == 3);
        dist_pair[vec[0]][vec[1]] = vec[2];
        dist_pair[vec[1]][vec[0]] = vec[2];

        adj[vec[0]].push_back(vec[1]);
        adj[vec[1]].push_back(vec[0]);
    }

    distance[s] = 0;
    visited[s] = true;
    stack<int> V; //vertices
    V.push(s);

    while(not V.empty()) {
        int v = V.top();
        V.pop();
        int next = -1;
        int d = INT_MAX;
        for(int& e : adj[v]) {
//            std::cout << e << "\n";
            int curdist = distance[e];
            int new_dist = distance[v] + dist_pair[v][e];

            if(curdist == -1 or new_dist < curdist) {
                distance[e] = new_dist;
                via[e] = v; // => reached e via v
            }
            // Find the minimum
            if( distance[e] < d and (not visited[e]) ) {
                d = distance[e];
                next = e;
            }

        }

        if( next != -1) {
            visited[next] = true;
            V.push(next);
        }
        //distance[next] = d;
    }

    //vector<int> ans(std::begin(distance), std::end(distance));
    vector<int> ans;
    for(int i = 1; i < n; i++) {
        if(i != s)
            ans.push_back(distance[i]);
    }
    return ans;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string nm_temp;
        getline(cin, nm_temp);

        vector<string> nm = split_string(nm_temp);

        int n = stoi(nm[0]);

        int m = stoi(nm[1]);

        vector<vector<int>> edges(m);
        for (int i = 0; i < m; i++) {
            edges[i].resize(3);

            for (int j = 0; j < 3; j++) {
                cin >> edges[i][j];
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        int s;
        cin >> s;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        vector<int> result = shortestReach(n, edges, s);

        for (int i = 0; i < result.size(); i++) {
            fout << result[i];
            cout << result[i];
            if (i != result.size() - 1) {
                fout << " ";
                cout << " ";
            }
        }

        fout << "\n";
        cout << "\n";
    }

    fout.close();

    return 0;
}

vector<string> split_string(string input_string)
{
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
