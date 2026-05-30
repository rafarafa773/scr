#include <fstream>
#include <iostream>
#include <string>

struct file_obj {
	int lines = 0;
	std::string line1;
	std::size_t chars_of_file = 0;

	void reset_stream(std::ifstream& file1) {
		file1.clear();
		file1.seekg(0);
	}

	int count_lines(std::ifstream& file1) {
		reset_stream(file1);
		lines = 0;
		while (std::getline(file1, line1)) {
			lines++;
		}
		return lines;
	}

	int count_chars(std::ifstream& file1) {
		reset_stream(file1);
		chars_of_file = 0;
		while (std::getline(file1, line1)) {
			chars_of_file += line1.size();
		}
		return (int)chars_of_file;
	}

	void show_all(std::ifstream& file1) {
		reset_stream(file1);
		while(std::getline(file1, line1)) {
			std::cout << line1 << "\n";
		}
	}
};

int main(int argc, char *file_passed[]) {
	double version = 0.1;

	if (argc > 1 && (std::string)file_passed[1] == "--version") {
		std::cout << "version: " << version << "\n";
		return 0;
	}

	if (argc < 2) {
		std::cout << "mate, provide a file.\n";
		return 1;
	}
	
	if (argc == 2) {
		std::cout << "are you dumb? use count or show.\n";
	}

	std::ifstream file(file_passed[1]); 
	if(!file.is_open()) {
		std::cout << "mate, that file doesn't exist.\n";
		return 1;
	}

	file_obj test1;
	if (argc > 2) {
		if ((std::string)file_passed[2] == "show") {
			test1.show_all(file);
		} else if ((std::string)file_passed[2] == "count") {
			std::cout << "lines: " << test1.count_lines(file) << "\n";
			std::cout << "chars: " << test1.count_chars(file) << "\n";
		}
	}
	return 0;
}
