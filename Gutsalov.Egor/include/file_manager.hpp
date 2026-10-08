#pragma once

#include <concepts>
#include <filesystem>
#include <fstream>
#include <string>
#include <string_view>
#include <utility>

namespace files {

class FileManager {
public:
  template <typename Filename>
    requires(std::constructible_from<std::filesystem::path, Filename>)
  explicit FileManager(Filename &&filepath)
      : filepath_(std::forward<Filename>(filepath)) {}

  ~FileManager();

  void open(std::ios_base::openmode mode = std::ios_base::in |
                                           std::ios_base::out |
                                           std::ios_base::app);
  void close();

  [[nodiscard]] bool is_open() const;

  FileManager &operator<<(std::string_view data);

  FileManager &operator>>(std::string &data);

  FileManager &operator>(std::string_view data);

  FileManager &operator<(std::string &data);

  void change_directory(const std::filesystem::path &new_dir) {
    filepath_ = new_dir;
  }

private:
  std::filesystem::path filepath_;
  std::fstream file_;
};

} // namespace files