#include <iostream>
#include "command_line.hpp"
#include "utils.hpp"

void print_version_message() {
    std::cout << SMARTMHA_VERSION_STR << std::endl;
}

void help_smartmha_porcelain() {

}

void help_smartmha_create() {
    std::cout << " " << std::endl;
}

int main_smartmha_porcelain(int argc, char *argv[]) {
    std::cout << argc << std::endl;
    std::cout << argv[0] << std::endl;
    return 0;
}

int main_smartmha_create(int argc, char *argv[]) {
    std::cout << argc << std::endl;
    std::cout << argv[0] << std::endl;
    return 0;
}