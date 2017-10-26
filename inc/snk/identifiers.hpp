#ifndef SNAKE_IDENTIFIERS_HEADER
#define SNAKE_IDENTIFIERS_HEADER

#include <cstddef>
#include <snk/resource/handle.hpp>

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
typedef std::size_t SceneId;
typedef std::size_t IHandlerId;
typedef std::size_t TextureId;
typedef std::size_t ClipId;
typedef std::size_t ComponentId;
typedef std::size_t NodeId;

} // namespace snk

#endif
