#ifndef SNAKE_SNK_EXCEPTION_HEADER
#define SNAKE_SNK_EXCEPTION_HEADER

#include <stdexcept>

namespace snk {

class SnakeException : public std::runtime_error {
public:

    SnakeException(const std::string& message);

};

} // namespace snk

#endif
