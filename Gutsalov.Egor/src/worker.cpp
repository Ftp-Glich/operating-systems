#include "worker.hpp"

namespace application {

constexpr std::string log_ending = ".log";

bool checkIfLogFile(std::string_view filename) {
  if (filename.length() < 4) {
    return false;
  }

  auto ending = filename.substr(filename.length() - log_ending.length());
  return ending == log_ending;
}

void Worker::makeIteration() {
  namespace fs = std::filesystem;

  // Search for all the *.log files
  for (auto &entry : fs::recursive_directory_iterator(first_dir_)) {
    if (!entry.is_regular_file() ||
        !checkIfLogFile(entry.path().filename().string())) {
      continue;
    }

    auto log_file = files::FileManager(fs::absolute(entry.path()));

    log_file.open(std::ios_base::out);

    // Read data form log file
    std::string data;
    log_file < data;

    log_file.close();

    // Write data to the end of the total.log file
    if (!total_log_.is_open()) {
      total_log_.open(std::ios_base::app);
    }

    total_log_ << "\n\n" << entry.path().filename().string() << "\n" << data;
  }

  total_log_.close();

  if (need_to_reopen_files_) {
    total_log_ .change_directory(second_dir_.string() + total_log_filename);
  }
}

} // namespace application