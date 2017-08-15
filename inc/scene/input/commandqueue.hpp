#ifndef SNAKE_COMMAND_QUEUE_HEADER
#define SNAKE_COMMAND_QUEUE_HEADER

#include <queue>
#include <scene/input/command.hpp>

namespace snk {

class CommandQueue {
public:

    void push(const Command& command);
    bool pollCommands(Command& command);

private:

    std::queue<Command> mQueue;

};

} // namespace snk

#endif
