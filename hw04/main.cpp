#include "is_optimistic_parallelized.hpp"
#include "is_optimistic_synchronized.hpp"
#include <iostream>
#include <cstring>


int main(int argc, char *argv[]) {
    if (argc == 3) {
        if (!strcmp(argv[1], "--parallelized"))
            std::cout << parallelized::is_optimistic(argv[2]) << '\n';
        else if (!strcmp(argv[1], "--synchronized"))
            std::cout << synchronized::is_optimistic(argv[2]) << '\n';
    }
    return 0;
}
