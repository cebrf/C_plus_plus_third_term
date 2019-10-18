#include <iostream>
#include <string>
#include <cstdint>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <memory>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

class PackageStream {
 public:
  PackageStream(std::string data, int32_t package_len) :
    data_(data), package_len_(package_len) {}

  int32_t PackageLen() const {
    return package_len_;
  }

  int32_t ReadPackage(char* buf) {
    int32_t next_pos = std::min<int32_t>(data_.size(), pos_ + PackageLen());
    int32_t len = next_pos - pos_;

    memcpy(buf, data_.c_str() + pos_, len);
    pos_ = next_pos;
    return len;
  }

 private:
  const int32_t package_len_;
  int32_t pos_ = 0;

  std::string data_;
};

class BufferedReader {
 public:
  explicit BufferedReader(PackageStream* stream) : stream(stream) {}
  int32_t Read(char* output_buffer, int32_t output_buffer_len) {
    if (output_buffer_len == 0) {
      return output_buffer_len;
    }
    int k = 0;
    if (buff.length() > 0) {
      if (buff.length() >= output_buffer_len) {
        memcpy(output_buffer, buff.c_str(), output_buffer_len);
        buff.erase(buff.begin(), buff.begin() + output_buffer_len);
        k = output_buffer_len;
      } else {
        memcpy(output_buffer, buff.c_str(), buff.length());
        k = buff.length();
        buff.clear();
      }
    }
    if (k < output_buffer_len) {
      int32_t package_len = 0;
      while (1) {
        char* new_package = new char[stream->PackageLen() + 1];
        package_len = stream->ReadPackage(new_package);
        if (package_len == 0) {
          delete[] new_package;
          break;
        }
        if (package_len == (output_buffer_len - k)) {
          memcpy(output_buffer + k, new_package, package_len);
          k = output_buffer_len;
          delete[] new_package;
          break;
        }
        if (package_len > (output_buffer_len - k)) {
          memcpy(output_buffer + k, new_package, (output_buffer_len - k));
          std::string buff_;
          for (int i = output_buffer_len - k; i < package_len; i++) {
            buff_ += new_package[i];
          }
          buff += buff_;
          //char* buff_ch = new char[package_len - (output_buffer_len - k)];
          //memcpy(buff_ch, new_package + , package_len - (output_buffer_len - k));
          //std::string buff_(buff_ch);
          //buff += buff_.substr(output_buffer_len - k, package_len - (output_buffer_len - k));
          k = output_buffer_len;

          //delete[] buff_ch;
          delete[] new_package;
          break;
        }
        if (package_len < (output_buffer_len - k)) {
          memcpy(output_buffer + k, new_package, package_len);
          k += package_len;
          delete[] new_package;
        }
      }
    }
    return k;
  }

 private:
  PackageStream* stream;
  std::string buff;
};

int main() {

  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  int32_t package_len = 0;
  int32_t read_len = 0;
  int32_t expect_len = 0;
  int ok = true;
  int cur_byte = 0;

  std::cin >> package_len;
  std::string s;
  getline(std::cin, s);
  getline(std::cin, s);
  PackageStream stream(s, package_len);
  BufferedReader reader(&stream);

  while (std::cin >> read_len >> expect_len) {
    std::unique_ptr<char[]> buf(new char[read_len]);

    int got_len = reader.Read(buf.get(), read_len);
    if (got_len != expect_len || memcmp(buf.get(), s.c_str() + cur_byte, expect_len) != 0) {
      ok = false;
      break;
    }

    cur_byte += read_len;
  }

  std::cout << (int)ok << std::endl;
}