#include <algorithm>    // std::make_heap, std::pop_heap, std::push_heap, std::sort_heap
#include <cassert>
#include <cmath>
#include <iostream>     // std::cout
#include <map>
#include <vector>       // std::vector



using PointList = std::vector<std::pair<float, float>>;

PointList closest(PointList& points, int k)
{
    //std::map<float,std::pair<int,int>>  distance;
    using  DistCord = std::pair<float, std::pair<float, float>>;
    std::vector<DistCord> kdistance;
    std::vector<DistCord> remaining;
    for(const auto& p : points) {
        float xsq = pow( (float)p.first, 2);
        float ysq = pow( (float)p.second, 2);
        //std::cout << xsq << " " << ysq << "\n";
        float dist = pow( xsq + ysq , 0.5f);
        // std::cout <<"[DEBUG:]" << dist << "\n";
        if( k > kdistance.size())
            kdistance.push_back(make_pair(dist, p));
        else
            remaining.push_back(make_pair(dist, p));
    }

    auto print = [] (const std::vector<DistCord>& points) {
        for(auto& p : points) {
            std::cout << "(" << (p.second).first <<  "," << (p.second).second << ") ";
        }
        std::cout << "\n";
    };


    auto sortpair =  [](DistCord p1, DistCord p2) {
        return p1.first < p2.first;
    };
    std::make_heap(kdistance.begin(), kdistance.end(), sortpair) ;

    std::cout << "Initial heap:\n";
    print(kdistance);

    for(int i = 0 ; i < remaining.size(); i++) {
        if(remaining[i].first < kdistance.front().first) {
            std::pop_heap(kdistance.begin(), kdistance.end());
            kdistance.pop_back();
            kdistance.push_back(remaining[i]);
            std::push_heap(kdistance.begin(), kdistance.end(), sortpair);
        }
    }

    PointList kclosest;
    for(auto& p : kdistance) {
        kclosest.push_back(p.second);
    }

    return kclosest;
}

int main ()
{
    PointList points = { std::make_pair(-5, -5), std::make_pair(-2, -2),
                         std::make_pair(-0.5f, 1.0f), std::make_pair(1, 1)
                       };

    auto r = closest(points, 3);

    auto print = [] (const PointList & points) {
        for(auto& p : points) {
            std::cout << "(" << p.first <<  "," << p.second << ") ";
        }
        std::cout << "\n";
    };

    std::cout << "Points:\n"; print(points);
    std::cout << "K closest points to origin:\n"; print(r);
}

