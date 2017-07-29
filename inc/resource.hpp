#ifndef SNAKE_RESOURCE_HEADER
#define SNAKE_RESOURCE_HEADER

namespace snk {

class Resource {
public:

    virtual ~Resource() {}

    virtual void reset() = 0;

};

} // namespace snk

#endif
