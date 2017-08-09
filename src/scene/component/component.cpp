#include <scene/component/component.hpp>

namespace snk {

Component::Component() 
: mOwnerHandle() {}

void Component::init() {}
void Component::update(float /* delta */) {}

} // namespace snk
