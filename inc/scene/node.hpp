#ifndef SNAKE_NODE_HEADER
#define SNAKE_NODE_HEADER

#include <vector>
#include <memory>
#include <texture.hpp>
#include <maths/transform.hpp>

namespace snk {

// Note: using dirty flag with local transform data makes some operations impossible
//       e.g rotating around a point that is not the origin (translate to point, rotate,
//       translate back ~ would just appear like a rotation around the origin).
//       However, it does ensure transformations are always applied in the same order:
//       Translate to origin -> scale -> rotate -> translate.
class Node {
public:

    Node(Texture* texture);

    void addChild(Node& child);

    void render();

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

    void render(const Transform& world, bool dirty);

private:

    Node* mParent;

    bool mDirty;
    Transform mLocal;
    Transform mWorld;

    Transform::TData mLocalData;

    Texture* mTexture;

    std::vector<Node*> mChildren;

};

} // namespace snk

#endif
