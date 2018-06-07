#include "exceptions.h"

DNSException::DNSException(const char *msg){
    this->msg = "";
    this->msg += msg ;
}

DNSException::~DNSException() throw(){
}

const char* DNSException::what() const throw()
{
  return msg.c_str();
}
