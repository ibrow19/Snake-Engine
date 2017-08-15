#ifndef SNAKE_IDENTIFIERS_HEADER
#define SNAKE_IDENTIFIERS_HEADER

#include <handle.hpp>

namespace snk {

// Define different tags to be used.
struct TextureTag {};
struct ComponentTag {};
struct NodeTag {};

// Define handle for each tag.
typedef Handle<TextureTag> TextureHandle;
typedef Handle<ComponentTag> ComponentHandle;
typedef Handle<NodeTag> NodeHandle;

// Define different identifiers.
typedef unsigned int SceneId;
typedef unsigned int IHandlerId;
typedef unsigned int TextureId;
typedef unsigned int ComponentId;
typedef unsigned int NodeId;

} // namespace snk

#endif
