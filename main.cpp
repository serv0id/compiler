#include <iostream>
#include <utility>

class Lox {
public:
    Lox(const std::string &file_name) {
        this->file = file_name;
    }
    int run();
    std::string read_file(std::string& file_name);

private:
    std::string file;
};

int main(const int argc, char *argv[]) {
    std::cout << "Welcome to lox compiler." << std::endl;

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        exit(64);  // sysexits.h
    } else {
        std::string file_name = argv[1];
        Lox lox = Lox(file_name);
    }

    return 0;
}