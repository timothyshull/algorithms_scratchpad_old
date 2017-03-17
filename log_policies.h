#ifndef CUSTOM_ALGORITHMS_LOG_POLICIES_H
#define CUSTOM_ALGORITHMS_LOG_POLICIES_H

#include <string>
#include <fstream>

class log_policy_interface {
public:
    virtual void open_ostream(const std::string &name) = 0;

    virtual void close_ostream() = 0;

    virtual void write(const std::string &msg) = 0;
};

class file_log_policy : public log_policy_interface {
    std::unique_ptr<std::basic_ofstream> out_stream;
//    std::basic_ofstream out_stream;
public:
    file_log_policy() : out_stream{std::unique_ptr(new std::basic_ofstream())} {}

    void open_ostream(const std::string &name);

    void close_ostream();

    void write(const std::string &msg);

    ~file_log_policy();
};

#endif //CUSTOM_ALGORITHMS_LOG_POLICIES_H
