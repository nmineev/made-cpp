#include <iostream>
#include <string>
#include <sstream>
#include "is_optimistic_parallelized.hpp"
#include "is_optimistic_synchronized.hpp"
#include "is_optimistic.cpp"
#include <gtest/gtest.h>
#include <random>
#include <vector>


TEST(DialogOptimismCheckersTest, CountDigraphsTest1) {
    std::string s = ":):):):)\n"
                    ":):):):)\n"
                    ":):):):)\n"
                    ":):):):)";
    std::istringstream is(s);
    auto [positive_digraphs, negative_digraphs] = CountDigraphs(is, 0, s.size());
    EXPECT_EQ(16, positive_digraphs);
    EXPECT_EQ(0, negative_digraphs);
}


TEST(DialogOptimismCheckersTest, CountDigraphsTest2) {
std::string s = ":(:(:(:(\n"
                ":(:(:(:(\n"
                ":(:(:(\n";
std::istringstream is(s);
auto [positive_digraphs, negative_digraphs] = CountDigraphs(is, 0, s.size());
EXPECT_EQ(0, positive_digraphs);
EXPECT_EQ(11, negative_digraphs);
}


TEST(DialogOptimismCheckersTest, CountDigraphsTest3) {
std::string s = "hahaha :( hello :) :) hahaha :( :) hahaha cringe gimme the loot :( hahaha lol :) :(\n"
                "hahaha hahaha hello gimme the loot :) hello hahaha lol cringe op lol gimme the loot :( :) cringe hello\n"
                ":) hello lol hahaha :) :( hello :( gimme the loot op gimme the loot op op op :) :(\n"
                "hello :) op op cringe op op hahaha cringe :( cringe hahaha op :) op hahaha\n"
                "gimme the loot :) hello :) lol lol gimme the loot op gimme the loot lol gimme the loot :( :) op gimme the loot cringe\n"
                "gimme the loot gimme the loot lol hahaha op hello op lol hahaha gimme the loot gimme the loot hello :) lol lol :)\n"
                "lol lol op cringe :";
std::istringstream is(s);
auto [positive_digraphs, negative_digraphs] = CountDigraphs(is, 0, s.size());
EXPECT_EQ(16, positive_digraphs);
EXPECT_EQ(10, negative_digraphs);
}


TEST(DialogOptimismCheckersTest, CountDigraphsTest4) {
std::string s = "hahaha :( hello :) :) hahaha :( :) hahaha cringe gimme the loot :( hahaha lol :) :(\n"
                "hahaha hahaha hello gimme the loot :) hello hahaha lol cringe op lol gimme the loot :( :) cringe hello\n"
                ":) hello lol hahaha :) :( hello :( gimme the loot op gimme the loot op op op :) :(\n"
                "hello :) op op cringe op op hahaha cringe :( cringe hahaha op :) op hahaha\n"
                "gimme the loot :) hello :) lol lol gimme the loot op gimme the loot lol gimme the loot :( :) op gimme the loot cringe\n"
                "gimme the loot gimme the loot lol hahaha op hello op lol hahaha gimme the loot gimme the loot hello :) lol lol :)\n"
                "lol lol op cringe :";
std::istringstream is(s);
auto [positive_digraphs, negative_digraphs] = CountDigraphs(is, 4, 32);
EXPECT_EQ(3, positive_digraphs);
EXPECT_EQ(2, negative_digraphs);
}


const std::vector<std::string> WORDS = {"hello", "op", "lol", "hahaha", "cringe", "gimme the loot", ":)", ":(", "Ronaldo", "goyda"};
std::mt19937 GENERATOR(123);


std::vector<std::string> GenerateString(size_t num_words = 16) {
    std::vector<std::string> random_string(num_words);
    std::uniform_int_distribution<size_t> dist(0, WORDS.size() - 1);
    for (auto& word: random_string)
        word = WORDS[dist(GENERATOR)];
    return random_string;
}

std::string GenerateFile(const char* filename = "dialog.txt", size_t num_lines = 1'000'000) {
    std::ofstream fout(filename);
    for (size_t line_num = 0; line_num < num_lines; ++line_num) {
        std::vector<std::string> random_strings = GenerateString();
        for (const auto& s: random_strings)
            fout << s << ' ';
        fout << '\n';
    }
    fout.close();
    return filename;
}


TEST(DialogOptimismCheckersTest, StressTest) {
    for (size_t ind = 0; ind < 5; ++ind) {
        GenerateFile();
        EXPECT_EQ(parallelized::is_optimistic("dialog.txt"), synchronized::is_optimistic("dialog.txt"));
    }
}

