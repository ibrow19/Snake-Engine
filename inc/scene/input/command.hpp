#ifndef SNAKE_COMMAND_HEADER
#define SNAKE_COMMAND_HEADER

#include <functional>
#include <identifiers.hpp>
#include <error/snkexception.hpp>
#include <scene/component/component.hpp>

namespace snk {

class Command {
public:
    
    Command();
    Command(ComponentId componentId, std::function<void(Component&)> action);

    ComponentId getId() const;
    void execute(Component& component) const;

private:

    ComponentId mComponentId;
    std::function<void(Component&)> mAction;
    
};


template<typename ComponentType, typename Function>
Command createCommand(ComponentId componentId, Function action) {

    std::function<void(Component&)> derivedAction =
    [action](Component& component) {

        ComponentType* derived = dynamic_cast<ComponentType*>(&component);
        if (derived == nullptr) {

            throw SnakeException("Invalid component type conversion when executing command");

        }
        action(*derived);

    };
    return Command(componentId, derivedAction);

}

} // namespace snk

#endif
