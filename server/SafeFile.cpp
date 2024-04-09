#include "SafeFile.hpp"

std::mutex SafeFile::m_mutex;

void SafeFile::writeToFile(const std::string& filename, const std::string& message) {
    std::lock_guard<std::mutex> lock(m_mutex);
    std::ofstream file(filename, std::ios_base::app);
    if (file.is_open()) {
        std::time_t now = std::time(nullptr);
        char timeString[64];
        strftime(timeString, sizeof(timeString), "%c", std::localtime(&now));
        file << timeString << ": " << message << std::endl;
    }
}

