#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>


std::pair<float, float> min_difference(std::vector<float> values)
{
    std::sort(values.begin(), values.end());

    float min = 0; float val1, val2;
    bool first_time = true;
    for(int i = 0; i < values.size() - 1; i++) {
        float diff =  fabs(values[i] - values[i + 1]);
        if(first_time) {
            min = diff;
            val1 = values[i];
            val2 = values[i + 1];
            first_time = false;

        } else {
            if ( diff < min) {
                min = diff;
                val1 = values[i];
                val2 = values[i + 1];
            }

        }
    }

    return std::make_pair(val1, val2);
}




int main(int argc, char** argv)
{
    std::vector<float> test = {0.7, 0.67, 0.65, 0.6};

    auto p = min_difference(test);

    std::cout << "Min diff is bn " << p.first << "and " <<  p.second << "\n";

}
