#include <sstream>
#include <fstream>
#include <string>
#include <iostream>


using namespace std;


int main(int argc, char** argv){
	if(argc < 1) {
		std::cerr << "Please specify the input file.\n";
	}
	ifstream ifs(argv[1]);
	if(!ifs.is_open()){
		std::cerr << "Error opening the file.\n";
	}
	int safe_cnt = 0;
	int prev_value = 0;
	std::string line{};
	while ( std::getline(ifs, line)) {
		std::istringstream iss(line);
		int value;
		bool incmode = true;
		bool decmode = true;
		bool is_safe = true;
		while (iss >> value) {
			if (prev_value == 0){
				prev_value = value;
				continue;
			}
			if(incmode && value > prev_value){
				const auto diff = value-prev_value;
				if(!(diff >= 1 && diff <=3)) { 
					is_safe = false; break; }
				decmode = false;
			}
			else if(decmode && value < prev_value){
				const auto diff = prev_value - value;
				if(!(diff >= 1 && diff <=3)) { 
					is_safe = false; 
					break; }
				incmode = false;
			} else { 
				is_safe = false; break;}
			prev_value = value;
		}
		if(is_safe){ safe_cnt++; }
		prev_value = 0;
	}
	ifs.close();

	std::cout << safe_cnt << '\n';
	return 0;

}
