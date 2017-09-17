#ifndef SNAKE_CONTEXT_HEADER
#define SNAKE_CONTEXT_HEADER

namespace snk {

class TextureManager;
class ComponentManager;
class NodeManager;
//class CommandQueue;

/// Give components relevant access to global systems.
// TODO: wrap contents so only relevant functions are exposed.
struct Context {

    TextureManager& tManager;
    ComponentManager& cManager;
    NodeManager& nManager;
    // CommandQueue& cQueue;
    // SoundQueue& sQueue;

};

} // namespace snk

#endif
