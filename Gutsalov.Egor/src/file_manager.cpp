#include "file_manager.hpp"
#include <sstream>

namespace files {

FileManager::~FileManager() {
    if (file_.is_open()) {
        file_.close();
    }
}

void FileManager::open(std::ios_base::openmode mode) {
    if (file_.is_open()) {
        file_.close();
    }
    file_.open(filepath_, mode);
}

void FileManager::close() {
    if (file_.is_open()) {
        file_.close();
    }
}

bool FileManager::is_open() const {
    return file_.is_open();
}

FileManager& FileManager::operator<<(std::string_view data) {
    if (!file_.is_open()) {
        open(std::ios_base::out | std::ios_base::app);
    }
    if (file_.is_open()) {
        file_ << data;
        file_.flush();
    }
    return *this;
}

FileManager& FileManager::operator>>(std::string& data) {
    if (!file_.is_open()) {
        open(std::ios_base::in);
    }
    if (file_.is_open()) {
        file_ >> data; 
    }
    return *this;
}

FileManager& FileManager::operator>(std::string_view data) {
    if (file_.is_open()) {
        file_.close();
    }
    file_.open(filepath_, std::ios_base::out | std::ios_base::trunc);
    if (file_.is_open()) {
        file_ << data;
        file_.flush();
    }
    return *this;
}

FileManager& FileManager::operator<(std::string& data) {
    if (!file_.is_open()) {
        open(std::ios_base::in);
    }
    if (file_.is_open()) {
        std::ostringstream ss;
        ss << file_.rdbuf();
        data = ss.str();
    }
    return *this;
}

} // namespace files