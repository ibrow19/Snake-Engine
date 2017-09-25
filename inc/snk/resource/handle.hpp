#ifndef SNAKE_HANDLE_HEADER
#define SNAKE_HANDLE_HEADER

#define INDEX_BITS 16
#define COUNTER_BITS 16
#define MAX_INDEX ((1 << INDEX_BITS) - 1)
#define MAX_COUNTER ((1 << COUNTER_BITS) - 1)

namespace snk {

/// Handle for resources.
/// Template Tag to allow different handle types for different resources for 
/// compile time safety.
/// A null handle has the counter zero.
template<typename Tag>
class Handle {
public:

    /// Default initialision.
    Handle();

    Handle(unsigned int index, unsigned int counter);
    
    unsigned int getIndex() const;
    unsigned int getCounter() const;

private:    

    unsigned int mIndex : INDEX_BITS;
    unsigned int mCounter : COUNTER_BITS;

};

#include <snk/resource/handle.inl>

} // namespace snk

#endif
