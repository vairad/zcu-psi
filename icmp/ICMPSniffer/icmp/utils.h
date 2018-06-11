#ifndef UTILS_H
#define UTILS_H

#include <chrono>
#include <string>
#include <netinet/in.h>

class Utils
{
    static std::chrono::system_clock::duration duration_since_midnight();
    static std::chrono::system_clock::duration now();
public:
    static uint32_t milisFromMidnight();
    static std::string timeFromMidnight(uint32_t);
    static in_addr resolveHostname(std::string hostname);
};

#endif // UTILS_H
