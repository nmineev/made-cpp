#include <iostream>
#include <boost/process.hpp>
#include <filesystem>
#include <thread>
#include <string>
#include <cstring>
#include <vector>

namespace bp = boost::process;


namespace parallelized {
//    size_t GetFileSize(const std::string& filename) {
//        struct stat stat_buf;
//        int rc = stat(filename.c_str(), &stat_buf);
//        return rc == 0 ? stat_buf.st_size : 0;
//    }

bool is_optimistic(const char* filename) {
    auto processor_count = std::thread::hardware_concurrency();
    size_t filesize = std::filesystem::file_size(filename);//GetFileSize(filename)
    size_t offset = 0;
    size_t batch_size = filesize / processor_count + 2;
    boost::asio::io_context ioc;
    bp::group g;
    std::vector<std::string> out_buffs(processor_count, std::string(100, '\0'));
    try {
        for (size_t ind = 0; ind < processor_count; ++ind) {
            std::string cmd = "utils/is_optimistic";
            std::string args = std::string(filename) + " " \
            + std::to_string(offset) + " " + std::to_string(batch_size);
            bp::spawn(cmd + " " + args,
                      bp::std_out > boost::asio::buffer(out_buffs[ind]),
                      ioc,
                      g);
            offset += batch_size - 1;
        }
        ioc.run();
    } catch (bp::process_error &error) {
        std::cerr << "Caught error " << error.what() << "\n";
    }
    size_t positive_cnt = 0;
    size_t negative_cnt = 0;
    for (const auto& out_buff: out_buffs) {
        if (!out_buff.empty()) {
            auto underscore_pos = out_buff.find("_");
            positive_cnt += std::stoul(out_buff.substr(0, underscore_pos));
            negative_cnt += std::stoul(out_buff.substr(underscore_pos + 1));
        }
    }
    //std::cerr << positive_cnt << ' ' << negative_cnt << '\n';
    return positive_cnt > negative_cnt;
}
};
