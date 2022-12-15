#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <utility>
#include "is_optimistic.cpp"


int main(int argc, char *argv[]) {
    if (argc < 4)
        return 0;
    const char* filename = argv[1];
    size_t start_pos = std::stoi(argv[2]);
    size_t count = std::stoi(argv[3]);
    std::ifstream fin(filename);
    auto [positive_digraphs, negative_digraphs] = CountDigraphs(fin, start_pos, count);
    std::cout << positive_digraphs << '_' << negative_digraphs;
    return 0;
}
