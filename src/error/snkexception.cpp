#include <snk/error/snkexception.hpp>

namespace snk {

SnakeException::SnakeException(const std::string& message) 
: std::runtime_error("Snake Engine error: " + message) {}

} // namespace snk
