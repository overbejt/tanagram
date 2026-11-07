#ifndef _READ_OVERFLOW
#define _READ_OVERFLOW

#include <exception>
#include <string>

class ReadOverflowException : public std::exception {
  private:
    std::string message;
  
  public:
    explicit ReadOverflowException(std::string msg) : message(std::move(msg)) { };

    const char* what() const noexcept override {
      return message.c_str();
    };
};

#endif /* _READ_OVERFLOW */

// END OF FILE

