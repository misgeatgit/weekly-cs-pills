

#include <iostream>
#include <map>
#include <vector>

bool containsUniqueChars(const std::string& str)
{
    //std::map<char,int> cnt;
    int char_freq [256] = {0};
    for(const char& c : str) {
        //if(cnt.find(c) != cnt.end()) return false;
        if( char_freq[c] > 0 ) return false;
        else char_freq[c] = 1;
    }

    return true;
}



int main(int argc, char ** argv)
{

    char * str = argv[1];

    if( containsUniqueChars(std::string(str)))
        std::cout << str << " is build from unique chars.\n";
    else
        std::cout << str << " Contains duplicates.\n";


}
