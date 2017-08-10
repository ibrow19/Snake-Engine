#ifndef SNAKE_COMPONENT_FACTORY_HEADER
#define SNAKE_COMPONENT_FACTORY_HEADER

#include <vector>
#include <identifiers.hpp>
#include <resourcemanager.hpp>
#include <error/snkexception.hpp>
#include <scene/component/componentpointer.hpp>

namespace snk {

class ComponentFactory {
public:

    ComponentFactory(unsigned int componentCount);

    template<typename T>
    void registerComponent(ComponentId componentId);
    void initComponent(ComponentId componentId,
                       ComponentPointer& newComponent);

    unsigned int getComponentCount() const;

private:

    struct ComponentType {

        bool init = false;
        ComponentPointer::Factory factory;

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
