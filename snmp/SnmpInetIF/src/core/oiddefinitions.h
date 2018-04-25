#ifndef OIDDEFINITIONS_H
#define OIDDEFINITIONS_H

#include <string>

std::string base_oid = ".1.3.6.1.2.1.2";
std::string physAdd_oid = base_oid + ".2.1.6";
std::string inBytes_oid = base_oid + ".2.1.10";
std::string outBytes_oid = base_oid + ".2.1.16";

std::string adminStatus_oid = base_oid + ".2.1.7";
std::string MTU_oid = base_oid + ".2.1.4";
std::string description_oid = base_oid + ".2.1.2";

#endif // OIDDEFINITIONS_H
