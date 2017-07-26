#ifndef SNAKE_COMPONENT_MANAGER_HEADER
#define SNAKE_COMPONENT_MANAGER_HEADER

#include <scene/component.hpp>

namespace snk {

//template<typename ... types>
class ComponentManager {
public:

    typedef unsigned int Id;

public:

    Component& createComponent(Id componentId);

    void update(float delta); 

private: 

    //std::tuple<std::vector<std::unique_ptr<types>>...> mComponents;

};

} // namespace snk

#endif
