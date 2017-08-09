#ifndef SNAKE_NODE_HEADER
#define SNAKE_NODE_HEADER

#include <vector>
#include <map>
#include <memory>
#include <texture.hpp>
#include <maths/transform.hpp>
#include <resource.hpp>
#include <identifiers.hpp>
#include <texturemanager.hpp>
#include <scene/component/component.hpp>
#include <scene/component/componentmanager.hpp>
#include <scene/node/nodemanager.hpp>

namespace snk {

//class TextureManager;
//class NodeManager;
//class ComponentManager;

class Node : public Resource {
public:

    Node();

    void reset();

    // TODO: less generic ResourceManager could avoid needing to constantly reinitialise
    //       managers.
    void init(TextureManager& tManager, 
              ComponentManager& cManager,
              NodeManager& nManager,  
              bool hasTexture, 
              TextureId textureId,
              const std::vector<ComponentId>& components);
    void addChild(const NodeHandle& childHandle);
    void render();
    
    // TODO: const getter.
    /// Get component of specified type T.
    /// \param componentId Identifier for component type to get.
    /// \return Pointer to the component or nullptr if node does not own such
    ///         a component.
    template<typename T>
    T* getComponent(ComponentId componentId); 

    // Mark the node and its children for removal so that once iteration for
    // updating is finished, the node can be destroyed by node manager.
    void destroy();
    
    // Check if node is marked for removal.
    bool isDestroyed() const;


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

    /// Add component to this node.
    /// \param componentId Id of component to add.
    void addComponent(ComponentId componentId);
    void render(const Transform& world, bool dirty);

private:

    bool mDestroyed;
    bool mHasTexture;
    bool mDirty;

    Transform::TData mLocalData;
    Transform mLocal;
    Transform mWorld;

    TextureId mTextureId;

    TextureManager* mTManager;
    ComponentManager* mCManager;
    NodeManager* mNManager;

    //NodeHandle mParent;
    std::map<ComponentId, ComponentHandle> mComponents;
    std::vector<NodeHandle> mChildren;

};


template<typename T>
T* Node::getComponent(ComponentId componentId) {

    assert(mTManager != nullptr);
    assert(mCManager != nullptr);
    assert(mNManager != nullptr);

    auto found = mComponents.find(componentId);
    if (found == mComponents.end()) {

        return nullptr;

    }
    Component& component = mCManager->dereference(found->first, found->second);
    T* target = dynamic_cast<T*>(&component);
    if (target == nullptr) {

        throw SnakeException("Using wrong type for component");

    }
    return target; 

}

} // namespace snk

#endif
