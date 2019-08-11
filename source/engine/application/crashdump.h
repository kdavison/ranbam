#pragma once

#include <boost/stacktrace.hpp>
#include <boost/filesystem.hpp>
#include <exception>
#include <chrono>
#include <fstream>
#include <atomic>
#include <csignal>
#include <cassert>

namespace ranbam
{

static class _CrashReporter {
public:
  _CrashReporter();
  ~_CrashReporter();
  void report();
private:
  std::atomic<bool> _crash;
  const char* file;
  std::ofstream ofs;
} CrashReport;

_CrashReporter::_CrashReporter()
  : file(new char[1024])
{
  std::strcpy(const_cast<char*>(file), ("./crash_" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count())).c_str());
  if(!::boost::filesystem::exists(file)) {
    ofs.open(file, std::fstream::out | std::fstream::trunc);
    assert(ofs.is_open());
  }

  std::set_terminate([](){
    if(CrashReport._crash) {
      ::boost::stacktrace::safe_dump_to(CrashReport.file);
    }
    std::abort();
  });
  std::signal(SIGFPE, [](int){
    CrashReport._crash = true;
    std::terminate();
  });
  std::signal(SIGILL, [](int){
    CrashReport._crash = true;
    std::terminate();
  });
  std::signal(SIGSEGV, [](int){
    CrashReport._crash = true;
    std::terminate();
  });
}

_CrashReporter::~_CrashReporter() {
  ofs.close();
  ::boost::filesystem::remove(file);
}

void _CrashReporter::report() {
  ofs << ::boost::stacktrace::stacktrace() << std::endl;
  ofs.close();
  std::abort();
}

}
