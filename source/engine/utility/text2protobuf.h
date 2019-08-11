#pragma once

#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <fcntl.h>
#include <memory>
#include <cassert>

namespace UTILITY
{

template<typename T>
static std::enable_if_t<true, std::unique_ptr<T>> LoadProtobufFromText(const std::string& filepath) {
  assert(!filepath.empty());
  int fd = open(filepath.c_str(), O_RDONLY);
  if(0 < fd) {
    ::google::protobuf::io::FileInputStream file(fd);
    file.SetCloseOnDelete(true);
    auto message = std::make_unique<T>();
    auto result = ::google::protobuf::TextFormat::Parse(&file, message.get());
    if(result) {
      return std::move(message);
    }
  }
  return nullptr;
}

template<typename T>
static void SaveProtobufToText(const std::string& filepath, const T& message) {
  assert(!filepath.empty());
  int fd = open(filepath.c_str(), O_WRONLY | O_CREAT);
  assert(0 < fd);
  ::google::protobuf::io::FileOutputStream file(fd);
  file.SetCloseOnDelete(true);
  auto result = ::google::protobuf::TextFormat::Printer().Print(message, &file);
  assert(result);
}

}
