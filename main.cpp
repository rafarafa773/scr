#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include <iomanip>
void print_with_highlight(const std::string& line, const std::string& target) {
	size_t pos = line.find(target);
	if (pos == std::string::npos) {
		std::cout << line << "\n";
		return;
    }
	std::cout << line.substr(0, pos);
	std::cout << "\033[31m" << target << "\033[0m";
	std::cout << line.substr(pos + target.length()) << "\n";
}

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

	size_t count_chars(std::ifstream& file1) {
		reset_stream(file1);
		chars_of_file = 0;
		while (std::getline(file1, line1)) {
			chars_of_file += line1.size();
			chars_of_file++;
		}
		return chars_of_file;
	}
	void list_files(const std::string& directory_path = ".") {
			for (const auto& entry : std::filesystem::directory_iterator(directory_path)) {
				std::cout << entry.path().filename().string() << "\n";
			}
	}

	int remove_archive(std::string name_of_archive) {
		std::filesystem::path path1 = name_of_archive;
		if(std::filesystem::remove(path1)) {
			std::cout << name_of_archive << " removed\n";
			return 0;
		} else {
			std::cout << "error\n";
			return 1;
		}
	}
	void print_dir() {
			std::cout << std::filesystem::current_path().string() << "\n";
	}

	int change1(const std::string& new_path) {
		std::filesystem::current_path(new_path);
		std::cout << "changed to: " << std::filesystem::current_path().string() << "\n";
		return 0;
	}



	void show_all(std::ifstream& file1) {
		reset_stream(file1);
		while(std::getline(file1, line1)) {
			std::cout << line1 << "\n";
		}
	}
};

int main(int argc, char *file_passed[]) {
	double version = 0.21;

	if (argc > 1 && (std::string)file_passed[1] == "--version") {
		std::cout << "version: " << version << "\n";
		return 0;
	}
	
	if (argc > 1 && (std::string)file_passed[1] == "--help") {
		std::cout << "usage: " << file_passed[0] << " <file> <option>\n\n"
				  << "commands:\n"
				  << "  list [dir]   : list files in directory (default: .)\n"
				  << "  whore        : print current working directory\n"
				  << "  change <dir> : change working directory\n"
				  << "  show         : display file content\n"
				  << "  show <str>   : search for a string in file\n"
				  << "  count        : count lines and characters\n"
				  << "  hex          : display file in hexadecimal\n"
				  << "  rm           : remove the file (dangerous!)\n";
        return 0;
    }
	if (argc > 1 && (std::string)file_passed[1] == "whore") {
		file_obj test1;
		test1.print_dir();
		return 0;
	}
	if (argc > 1 && (std::string)file_passed[1] == "change") {
		if (argc < 3) {
			std::cout << "your stupid\n";
			return 1;
		}
		file_obj test1;
		test1.change1(file_passed[2]);
		return 0;
	} /*this shit dont works*/

	if (argc < 2) {
		std::cout << "mate, provide a file.\n";
		return 1;
	}
	if (argc > 1 && (std::string)file_passed[1] == "list") {
    	std::string dir_path = (argc > 2) ? file_passed[2] : ".";
    	file_obj test1;
   		test1.list_files(dir_path);
		return 0;
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
		if ((std::string)file_passed[2] == "show" and argc == 3) {
			test1.show_all(file);
		} else if ((std::string)file_passed[2] == "count") {
			std::cout << "lines: " << test1.count_lines(file) << "\n";
			std::cout << "chars: " << test1.count_chars(file) << "\n";
		} else if ((std::string)file_passed[2] == "show" and argc > 3) {
			std::string busca = file_passed[3];
			std::string linha_temp;
			test1.reset_stream(file);
			while (std::getline(file, linha_temp)) {
				if (linha_temp.contains(busca)) {
					print_with_highlight(linha_temp, busca);
				}
			}
		} else if ((std::string)file_passed[2] == "hex") {
			std::string linha_temp;
			test1.reset_stream(file);
			while (std::getline(file, linha_temp)) {
				for(unsigned char c : linha_temp) {
					std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c) << " ";
				}
				std::cout << "\n";
			}
		} else if((std::string)file_passed[2] == "rm") {
			test1.remove_archive(file_passed[1]);
		}
	}
	return 0;
}
