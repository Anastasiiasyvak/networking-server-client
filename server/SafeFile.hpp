#ifndef SAFEFILE_HPP
#define SAFEFILE_HPP

#include <string>
#include <fstream>
#include <mutex>

class SafeFile {
public:
    static void writeToFile(const std::string& filename, const std::string& message);

private:
    static std::mutex m_mutex;
};

#endif // SAFEFILE_HPP

