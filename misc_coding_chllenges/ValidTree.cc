class Solution
{
public:
    bool validTree(int n, vector<pair<int, int>>& edges)
    {
        if( n <= 1) return true;
        // connectedness and acycliness

        map<int, vector<int>> adj;

        for(auto& p : edges) {
            if(adj.find(p.first) == adj.end())
                adj[p.first] = {p.second};
            else
                adj[p.first].push_back(p.second);

            if(adj.find(p.second) == adj.end())
                adj[p.second] = {p.first};
            else
                adj[p.second].push_back(p.first);
        }

        // Assumption : Order doesn't matter i.e (0,1) == (1,0)
        for(auto& p : adj) {
            int parent = p.first;
            auto& vec = adj[parent];
            std::cout << parent << "[ ";
            //self reference check
            for(int& e : vec) if(e == parent) return false;

            bool visited [n];
            stack<int> check;

            for(int& v : vec) {

                auto& vec2 = adj[v];
                visited[v] = true;
                for(int& e : vec2) {
                    if( e != parent) {
                        check.push(e);
                        visited[e] = true;
                    }
                }

                while(not check.empty()) {
                    auto& vec = adj[check.top()];
                    check.pop();

                    for(int& e : vec) {
                        if(e == parent) return false;
                        else if(not visited[e]) {
                            check.push(e);
                            visited[e] = true;
                        }
                    }
                }
            }



        }

        return (n - 1 == edges.size());


    }
};
