#include <boost/asio.hpp>
#include <boost/process.hpp>
#include <boost/filesystem.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <system_error>
#include "log.h"
#include <iostream>

const std::string generate_unique_filename() {
  return ::boost::uuids::to_string(::boost::uuids::random_generator()());
}

enum eCleanup {
  NONE,
  SAVELOG,
  CRASH
};

int main(int argc, char *argv[])
{
  const auto filename(generate_unique_filename());
  const auto engine_path = ::boost::filesystem::relative("ranbam.engine");
  auto cleanup = eCleanup::SAVELOG;
  {
    ::ranbam::launcher::Log log(filename + ".log");
    log.write(filename + '\n');
    log.flush();

    try {
      namespace bp = ::boost::process;
      bp::ipstream output;
      bp::ipstream error;
      std::error_code ec{};
      bp::child application(engine_path,
        bp::std_in.close(),
        bp::std_out > output,
        bp::std_err > error,
        ec
      );
      if(!ec) {
        std::string line;
        line.reserve(4096);
        while(
          application.running() &&
          output &&
          error) {
          std::getline(output, line);
          log.write(line);
          std::getline(error, line);
          log.write(line);
        }


        application.wait();
      } else {
        const std::string error_message("application failed to start\n");
        log.write(error_message);
      }
    } catch(const std::exception& ex) {
      cleanup = eCleanup::SAVELOG;
      const std::string exception_message = "std.ex: " + std::string(ex.what()) + '\n';
      log.write(exception_message);
    }
  }
  
  switch(cleanup) {
  case eCleanup::NONE:
    ::boost::filesystem::remove(filename + ".log");
    break;
  case eCleanup::SAVELOG:
    break;
  case eCleanup::CRASH:
    //do crash cleanup
    break;
  }

  return 0;
}
