#include <iostream>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/process.hpp>
#include <filesystem>
#include <thread>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <sys/resource.h>
#include <boost/interprocess/streams/bufferstream.hpp>

namespace bp = boost::process;
namespace bi = boost::interprocess;


std::ostream& operator<<(std::ostream& out, const std::vector<char>& v) {
    for (auto& el: v)
        out << el;
    out << '\n';
    return out;
}


bool is_optimistic_parallel(const char* filename) {
    auto processor_count = std::thread::hardware_concurrency();
    size_t filesize = std::filesystem::file_size(filename);
    size_t offset = 0;
    size_t batch_size = filesize / processor_count;
    boost::asio::io_context ioc;
    bp::group g;
    bi::file_mapping shm(filename, bi::read_only);
    std::vector<std::string> out_buffs(processor_count, std::string(100, '\0'));
    try {
        for (size_t ind = 0; ind < processor_count; ++ind){
            std::string cmd = "./is_optimistic_parallel";
            std::string args = std::string(filename) + " " + std::to_string(offset) + " " + std::to_string(batch_size);
            bp::spawn(cmd + " " + args,
//                      filename,
//                      offset,
//                      batch_size,
                      bp::std_out > boost::asio::buffer(out_buffs[ind]),
                      ioc,
                      g);
            offset += batch_size - 1;
        }
        ioc.run();
    } catch (bp::process_error &error) {
        std::cerr << "Caught error " << error.what() << "\n";
    }
    int64_t positive_cnt = 0;
    int64_t negative_cnt = 0;
    for (const auto& out_buff: out_buffs) {
        if (!out_buff.empty()) {
            std::cout << out_buff << '\n';
            auto underscore_pos = out_buff.find("_");
            //auto underscore_rpos = out_buff.rfind("_");
            positive_cnt += std::stoul(out_buff.substr(0, underscore_pos));
            negative_cnt += std::stoul(out_buff.substr(underscore_pos + 1));//, underscore_rpos));
        }
    }
    std::cout << positive_cnt << ' ' << negative_cnt << '\n';
    return positive_cnt > negative_cnt;
}


bool is_optimistic(const std::string& filename) {
    bp::ipstream out_pipe;
    std::string out_buff;
    bp::system("./is_optimistic", bp::std_in < filename, bp::std_out > out_pipe);
    out_pipe >> out_buff;
    auto underscore_pos = out_buff.find("_");
    auto positive_cnt = std::stoul(out_buff.substr(0, underscore_pos));
    auto negative_cnt = std::stoul(out_buff.substr(underscore_pos + 1));
    std::cout << positive_cnt << ' ' << negative_cnt << '\n';
    return positive_cnt > negative_cnt;
}


int main(int argc, char *argv[]) {
    if (argc == 3) {
        if (!strcmp(argv[1], "--parallel"))
            std::cout << "Run in parallel\n" << is_optimistic_parallel(argv[2]) << '\n';
        else if (!strcmp(argv[1], "--synchronous"))
            std::cout << "Run synchronous\n" << is_optimistic(argv[2]) << '\n';
    }
    return 0;
}


/*
bool is_optimistic_parallel(const char* filename) {
    boost::asio::io_context ioc;
    std::vector<char> buf(4096);

    bp::async_pipe ap(ioc);

    bp::child c{"./is_optimistic", bp::std_in < ap};

    boost::asio::async_write(ap, boost::asio::buffer("Jopa zalupa\n"),
                            [](const boost::system::error_code &ec, std::size_t size){
                                if (ec) {
                                    std::cout << ec.message() << ", size=" << size << "\n";
                                }
                            }
    );

    ioc.run();
    c.wait();

    int result = c.exit_code();

    std::cout << "Subprocess finished with code: " << result << "\n";
    std::copy(std::begin(buf), std::end(buf), std::ostreambuf_iterator(std::cout));
    return true;
}


bool is_optimistic_parallel(const char* filename) {
    auto processor_count = std::thread::hardware_concurrency();
    bi::file_mapping shm(filename, bi::read_only);
    int64_t filesize = std::filesystem::file_size(filename);
    std::cout << "File size: " << filesize << '\n';

    boost::asio::io_context ioc;
    bp::group g;
    int64_t offset = 0;
    //int64_t batch_size = filesize / processor_count + 2;
    std::vector<std::string> out_buffs(processor_count, std::string(1000, '\0'));
    //std::cout << "Batch size: " << batch_size << '\n';
    std::cout << "askdjfakjsd\n";
    bp::async_pipe ap{ioc};
    bi::mapped_region region(shm, bi::read_only, offset, 20);
//    boost::asio::async_write(ap, boost::asio::buffer(region.get_address(), 10),
//                             [](const boost::system::error_code &ec, std::size_t size){});
    bp::child c("./is_optimistic",
                bp::std_in < ap,
                bp::std_out > boost::asio::buffer(out_buffs[0]),
                g);
//    boost::asio::async_write(ap, boost::asio::buffer(static_cast<char*>(region.get_address()) + 10, 5),
//                             [](const boost::system::error_code &ec, std::size_t size){});
    ioc.run();
    g.wait();
    //c.wait();
//    try {
//        for (size_t ind = 0; ind < processor_count; ++ind){
//            bi::mapped_region region(shm, bi::read_only, offset, batch_size);
//            std::cout << "Region size: " << region.get_size() << '\n';
//            //const char* s = static_cast<char*>(region);
//            //std::cout << std::string(static_cast<char*>(region.get_address()), batch_size) << '\n';
//            offset += batch_size - 1;
//            //boost::asio::streambuf pp(static_cast<char*>(region.get_address()));
//            //bp::async_pipe ap{ioc};
//            //ap.read_some(std::string(static_cast<char*>(region.get_address())));
//            //bi::bufferstream input_stream(static_cast<char*>(region.get_address()), batch_size);
//            //std::string s(static_cast<char*>(region.get_address()), batch_size);
//            //bp::async_pipe pp(ioc);
//            //bp::pstream in;
//            //in << s;
//            bp::spawn("./is_optimistic",
//                      bp::std_in < boost::asio::buffer(region.get_address(), batch_size),//, batch_size
//                      bp::std_out > boost::asio::buffer(out_buffs[ind]),
//                      ioc,
//                      g);
//        }
//        ioc.run();
//    } catch (bp::process_error &error) {
//        std::cerr << "Caught error " << error.what() << "\n";
//    }
//    int64_t positive_cnt = 0;
//    int64_t negative_cnt = 0;
//    for (const auto& out_buff: out_buffs) {
//        std::cout << out_buff << '\n';
//        auto underscore_pos = out_buff.find("_");
//        auto underscore_rpos = out_buff.rfind("_");
//        positive_cnt += std::stoul(out_buff.substr(0, underscore_pos));
//        negative_cnt += std::stoul(out_buff.substr(underscore_pos + 1, underscore_rpos));
//    }
//    std::cout << positive_cnt << ' ' << negative_cnt << '\n';
    return true;//positive_cnt > negative_cnt;
}


//int main() {
//    bp::pipe intermediate;
//
//    bp::child process_gzip("/bin/gzip",   "-c", bp::std_in<"src/ProcessPipe2.cpp",   bp::std_out> intermediate);
//    bp::child process_bzip2("/bin/bzip2", "-c", bp::std_in<intermediate, bp::std_out> "src/ProcessPipe2.gz.bz2");
//
//    process_bzip2.wait();
//    process_bzip2.wait();
//}

int main(int argc, char *argv[]) {
    if (argc == 3) {
        if (!strcmp(argv[1], "--parallel"))
            std::cout << "Run in parallel\n" << is_optimistic_parallel(argv[2]) << '\n';
        else if (!strcmp(argv[1], "--synchronous"))
            std::cout << "Run synchronous\n" << is_optimistic(argv[2]) << '\n';
    }
//    auto processor_count = std::thread::hardware_concurrency();
//    std::cout << "Num Of CPUs: " << processor_count << '\n';
//
////    struct shm_remove {
////        shm_remove() { bi::shared_memory_object::remove("MySharedMemory"); }
////        ~shm_remove(){ bi::shared_memory_object::remove("MySharedMemory"); }
////    } remover;
//
////    bi::shared_memory_object shm(bi::create_only, "MySharedMemory", bi::read_write);
////    shm.truncate(100);
////
////    bi::mapped_region region_to_set(shm, bi::read_write);
////    //std::memset(region_to_set.get_address(), 'b', region_to_set.get_size());
////    std::memcpy(region_to_set.get_address(), "01234567891011121314151617181920212223242526272829", 50);
//
//    const char* filename = "dialog.txt";
//
////    struct file_remove {
////        file_remove(const char* filename): filename_(filename) {}
////        ~file_remove(){ bi::file_mapping::remove(filename_); }
////        const char* filename_;
////    } remover(filename);
//
//    bi::file_mapping shm(filename,
//                         bi::read_only);
//    size_t filesize = std::filesystem::file_size(filename);
//    std::cout << "File size: " << filesize << " bytes\n";
//
//
//    boost::asio::io_context ioc;
//    std::vector<std::string> out_buffs(processor_count, std::string(100, '\0'));//, std::vector<char>(100));
//
//    bp::group g;
//    size_t offset = 0;
//    size_t batch_size = 5;
//    try {
//        for (size_t ind = 0; ind < processor_count; ++ind){
//            bi::mapped_region region(shm, bi::read_only, offset, batch_size);
//            offset += batch_size - 1;
//            bp::spawn("./is_optimistic",
//                      bp::std_in < boost::asio::buffer(region.get_address(), batch_size),
//                      bp::std_out > boost::asio::buffer(out_buffs[ind]),
//                      ioc,
//                      g);
//        }
//        //    bp::child c{"./is_optimistic",
//        //                bp::std_in < boost::asio::buffer(region.get_address(), 5), bp::std_out > boost::asio::buffer(out_buf), ioc};
//        ioc.run();
//        //g.wait();
//    } catch (bp::process_error &error) {
//        std::cout << "Caught error " << error.what() << "\n";
//    }
//
//    //int result = g.exit_code();
//    //std::cout << "Subprocess finished with code: " << result << "\n";
//    for (const auto& out_buf: out_buffs) {
//        //std::copy(std::begin(out_buf), std::end(out_buf), std::ostreambuf_iterator(std::cout));
//        std::cout << out_buf << '\n';
//    }
//    std::cout << '\n';
    return 0;
}*/
