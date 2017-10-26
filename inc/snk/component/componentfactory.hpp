#ifndef SNAKE_COMPONENT_FACTORY_HEADER
#define SNAKE_COMPONENT_FACTORY_HEADER

#include <memory>
#include <vector>
#include <snk/identifiers.hpp>
#include <snk/resource/resourcemanager.hpp>
#include <snk/error/snkexception.hpp>
#include <snk/component/component.hpp>

namespace snk {

class ComponentFactory {
public:

    ComponentFactory(ComponentId componentCount);

    template<typename T>
    void registerComponent(ComponentId componentId);
    std::unique_ptr<Component> createComponent(ComponentId componentId) const;

    ComponentId getComponentCount() const;

private:

    typedef std::function<std::unique_ptr<Component>()> Factory;

private:

    struct ComponentType {

        bool init = false;
        Factory factory;

    };

private:

    // Factories for creating components.
    std::vector<ComponentType> mComponentTypes;

};


template<typename T>
void ComponentFactory::registerComponent(ComponentId componentId) {

    if (componentId >= mComponentTypes.size()) {

        throw SnakeException("Attempting to initialise component type Id which is greater than maximum component Id");

    }

    if (mComponentTypes[componentId].init) {

        throw SnakeException("Attempting to initialise already initialised component type Id");

    }

    mComponentTypes[componentId].init = true;
    mComponentTypes[componentId].factory = 
    []() {

        return std::unique_ptr<T>(new T());

    };

}

} // namespace snk

#endif
