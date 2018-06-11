#include "utils.h"
#include "exceptions.h"

#include <netdb.h>
#include <ctime>
#include <iostream>

std::chrono::system_clock::duration Utils::duration_since_midnight()
{
    auto now = std::chrono::system_clock::now();

    time_t tnow = std::chrono::system_clock::to_time_t(now);
    tm *date = std::localtime(&tnow);
    date->tm_hour = 2; // TO UTC correction
    date->tm_min = 0;
    date->tm_sec = 0;
    auto midnight = std::chrono::system_clock::from_time_t(std::mktime(date));

    return now-midnight;
}

uint32_t Utils::milisFromMidnight()
{
    auto since_midnight = Utils::duration_since_midnight();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(since_midnight);
    uint32_t data = milliseconds.count();
    return data;
}

std::string Utils::timeFromMidnight(uint32_t milisFromMidnight)
{
    uint32_t hours = milisFromMidnight / (1000*60*60);
    uint32_t remain = milisFromMidnight % (1000*60*60);
    uint32_t minutes = remain / (1000*60);
    remain = remain % (1000*60);
    uint32_t seconds = remain / 1000;
    remain = remain % 1000;
    std::string time = "";
    time += std::to_string(hours);
    time += ":";
    if(minutes < 10){
        time+="0";
    }
    time += std::to_string(minutes);
    time += ":";
    if(seconds < 10){
        time+="0";
    }
    time += std::to_string(seconds);
    time += ",";
    if(remain < 100){
        time+="0";
    }
    if(remain < 10){
        time+="0";
    }
    time += std::to_string(remain);
    return time;
}

struct in_addr Utils::resolveHostname(std::string hostname){
    struct hostent *hp = gethostbyname(hostname.c_str());
    struct in_addr addr;
    if (hp == NULL) {
       std::cerr << "Couldn't resolve hostname.";
       throw DNSException(hostname.c_str());
    } else {
       if ( hp -> h_addr_list[0] != NULL) {
          addr = *((struct in_addr*)( hp -> h_addr_list[0]));
       }
    }
    return addr;
}
