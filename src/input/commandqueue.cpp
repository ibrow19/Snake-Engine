#include <snk/input/commandqueue.hpp>

namespace snk {

void CommandQueue::push(const Command& command) {

    mQueue.push(command);

}


bool CommandQueue::pollCommands(Command& command) {

    if (mQueue.empty()) {

        return false;

    }
    command = mQueue.front();
    mQueue.pop();
    return true;

}

} // namespace snk
