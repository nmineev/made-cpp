#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <utility>


std::pair<size_t, size_t> CountDigraphs(std::istream& fin, size_t start_pos, size_t count) {
    fin.seekg(start_pos);
    size_t positive_digraphs = 0;
    size_t negative_digraphs = 0;
    char ch_curr, ch_prev = fin.get();
    for (size_t pos = start_pos + 1; pos < start_pos + count; ++pos) {
        if (fin.bad() || fin.eof() || fin.fail()) {
            //std::cerr << "I/O error while reading\n";
            break;
        }
        ch_curr = fin.get();
        if (ch_prev == ':') {
            if (ch_curr == ')')
                ++positive_digraphs;
            else if (ch_curr == '(')
                ++negative_digraphs;
        }
        ch_prev = ch_curr;
    }
    return std::make_pair(positive_digraphs, negative_digraphs);
}
