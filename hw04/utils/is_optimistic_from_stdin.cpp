#include <iostream>


int main() {
    char ch_prev, ch_curr;
    std::cin.get(ch_prev);
    size_t positive_digraphs = 0;
    size_t negative_digraphs = 0;
    while (std::cin.get(ch_curr)) {
        if (ch_prev == ':') {
            if (ch_curr == ')')
                ++positive_digraphs;
            else if (ch_curr == '(')
                ++negative_digraphs;
        }
        ch_prev = ch_curr;
    }
    std::cout << positive_digraphs << '_' << negative_digraphs;
    return 0;
}
