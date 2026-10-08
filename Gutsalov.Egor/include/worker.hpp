#pragma once

#include "file_manager.hpp"

#include <concepts>
#include <filesystem>
#include <string>
#include <tuple>

namespace application {

constexpr std::string total_log_filename = "total.log";

class Worker {
public:
  template <typename F, typename S>
    requires(std::constructible_from<std::filesystem::path, F> &&
             std::constructible_from<std::filesystem::path, S>)
  explicit Worker(F &&firt_directory, S &&second_directory)
      : first_dir_(std::forward(firt_directory)),
        second_dir_(std::forward(second_directory)),
        total_log_(second_dir_.string() + total_log_filename) {}

  template <typename... Args, int DirNum = 1>
    requires((sizeof...(Args) <= 2) &&
             (std::constructible_from<std::filesystem::path, Args> && ...))
  inline void changeDirectory(Args &&...strings) {
    auto args_tuple = std::forward_as_tuple(std::forward<Args>(strings)...);
    if constexpr (sizeof...(Args) == 2) {
      first_dir_ = std::get<0>(args_tuple);
      second_dir_ = std::get<1>(args_tuple);
      return;
    }

    static_assert(DirNum <= 2 && DirNum > 0);

    if constexpr (DirNum == 1) {
      first_dir_ = std::get<0>(args_tuple);
    } else {
      second_dir_ = std::get<0>(args_tuple);
    }

    need_to_reopen_files_ = true;
  }

  void makeIteration();

private:
  // Worker will open files only after iteration is over to avoid unfinished
  // actions
  bool need_to_reopen_files_{false};

  std::filesystem::path first_dir_;
  std::filesystem::path second_dir_;

  files::FileManager total_log_;
};

} // namespace application