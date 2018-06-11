#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class DNSException: public std::exception
{
    std::string msg;
  public:
    DNSException(const char *msg);
    ~DNSException() throw();
    virtual const char* what() const throw();
};

#endif // EXCEPTIONS_H
