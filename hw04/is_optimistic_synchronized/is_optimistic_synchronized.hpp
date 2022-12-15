#include <iostream>
#include <boost/process.hpp>
#include <filesystem>
#include <string>
#include <cstring>
#include <vector>

namespace bp = boost::process;


namespace synchronized {
//    size_t GetFileSize(const std::string& filename) {
//        struct stat stat_buf;
//        int rc = stat(filename.c_str(), &stat_buf);
//        return rc == 0 ? stat_buf.st_size : 0;
//    }

bool is_optimistic(const std::string& filename) {
    size_t filesize = std::filesystem::file_size(filename);//GetFileSize(filename)
    bp::ipstream out_pipe;
    std::string cmd = "utils/is_optimistic";
    std::string args = std::string(filename) + " " \
    + std::to_string(0) + " " + std::to_string(filesize);
    std::string out_buff(100, '\0');
    bp::system(cmd + " " + args, bp::std_out > out_pipe);
    out_pipe >> out_buff;
    auto underscore_pos = out_buff.find("_");
    auto positive_cnt = std::stoul(out_buff.substr(0, underscore_pos));
    auto negative_cnt = std::stoul(out_buff.substr(underscore_pos + 1));
    //std::cerr << positive_cnt << ' ' << negative_cnt << '\n';
    return positive_cnt > negative_cnt;
}
};
