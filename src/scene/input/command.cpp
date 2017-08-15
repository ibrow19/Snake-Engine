#include <scene/input/command.hpp>

namespace snk {

Command::Command() {}

Command::Command(ComponentId componentId, std::function<void(Component&)> action)
: mComponentId(componentId),
  mAction(action) {}


ComponentId Command::getId() const {

    return mComponentId;

}


void Command::execute(Component& component) const {

    mAction(component);

}

} // namespace snk
