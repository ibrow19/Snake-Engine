#include <handle.hpp>

namespace snk {

Handle::Handle(unsigned int index, unsigned int counter)
: mIndex(index),
  mCounter(counter) {}


unsigned int Handle::getIndex() const {

    return mIndex;

}


unsigned int Handle::getCounter() const {

    return mCounter;

}

} // namespace snk
