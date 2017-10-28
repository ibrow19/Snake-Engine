#ifndef SNAKE_NODE_HEADER
#define SNAKE_NODE_HEADER

#include <vector>
#include <map>
#include <memory>
#include <snk/identifiers.hpp>
#include <snk/texture/texture.hpp>
#include <snk/texture/texturemanager.hpp>
#include <snk/maths/transform.hpp>
#include <snk/resource/resource.hpp>
#include <snk/component/component.hpp>
#include <snk/component/componentmanager.hpp>
#include <snk/node/nodemanager.hpp>
#include <snk/node/nodedata.hpp>

namespace snk {

class Node : public Resource {
public:

    Node();

    void reset();

    // Mark the node and its children for removal so that once iteration for
    // updating is finished, the node can be destroyed by node manager.
    void destroy();
    
    // Check if node is marked for removal.
    bool isDestroyed() const;

    /// Add a component node to this node.
    void addComponent(ComponentId componentId, const ComponentHandle& handle);

    bool hasComponent(ComponentId componentId) const;
    const ComponentHandle& getComponent(ComponentId componentId) const;

    /* Texture functions */
    
    /// Set the texture used by this node.
    void setTexture(TextureId textureId);
    
    /// Set the texture clip used by this node.
    void setClip(ClipId clipId);

    /// Render this node and its children.
    /// \param tManager texture manager to use for drawing textures.
    /// \param nManager node manager to use for drawing children.
    void render(TextureManager& tManager, NodeManager& nManager);

    /* Transform functions */

    /// Add a child node to this node.
    void addChild(const NodeHandle& handle);

    // Operations corresponding to the various possible transformations.

    // Origin
    const Point2f& getOrigin() const;
    void setOrigin(Point2f origin);
    void setOrigin(float x, float y);

    // Scale
    const Vector2f& getScale() const;
    void setScale(float factor);
    void setScale(const Vector2f& factor);
    void setScale(float x, float y);
    void scale(float factor);
    void scale(const Vector2f& factor);
    void scale(float x, float y);

    // Rotate.
    float getRotation() const;
    void setRotation(float angle);
    void rotate(float angle);

    // Translation.
    const Vector2f& getTranslation() const;
    void setTranslation(const Vector2f& v);
    void setTranslation(float x, float y);
    void translate(const Vector2f& v);
    void translate(float x, float y);

private:

    /// Render this node and then it's children.
    /// \param tManager texture manager to use for getting textures to draw.
    /// \param nManager node manager to get children to draw.
    /// \param world the transform the node needs to combine with its local transform to get the
    ///        global transform.
    /// \param dirty whether the transform along the path to  this node has changed
    ///        since the last render.
    void render(TextureManager& tManager,
                NodeManager& nManager,
                const Transform& world, 
                bool dirty);


private:

    bool mDestroyed;
    bool mHasTexture;
    bool mDirty;

    TextureId mTextureId;
    ClipId mClipId;

    Transform::TData mLocalData;
    Transform mLocal;
    Transform mWorld;

    // TODO: use more efficient structure for component lookup (e.g hashmap).
    std::map<ComponentId, ComponentHandle> mComponents;
    std::vector<NodeHandle> mChildren;

};

} // namespace snk

#endif
