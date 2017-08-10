#include <error/snkexception.hpp>
#include <texturemanager.hpp>
#include <scene/component/componentmanager.hpp>
#include <scene/component/componentfactory.hpp>
#include <scene/node/node.hpp>
#include <scene/node/nodemanager.hpp>
#include <scene/node/nodefactory.hpp>
#include <scene/scene.hpp>

namespace snk {

Scene::Scene(TextureManager& tManager,
             ComponentFactory& cFactory,
             NodeFactory& nFactory)
: mRootHandle(),
  mCManager(cFactory),
  mNManager(tManager,
            mCManager,
            nFactory) {}

void Scene::update(float delta) {
    
    mCManager.update(delta);

}

void Scene::render() {

    assert(mRootHandle.getCounter() != 0);
    mNManager.dereference(mRootHandle).render();

};


void Scene::setRoot(NodeId rootId) {

    mRootHandle = mNManager.createNode(rootId); 

}

} // namespace snk
