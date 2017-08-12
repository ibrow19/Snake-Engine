#include <scene/input/ihandlerfactory.hpp>

namespace snk {

IHandlerFactory::IHandlerFactory(unsigned int iHandlerCount) 
: mIHandlerTypes(iHandlerCount) {}


std::unique_ptr<InputHandler> IHandlerFactory::createIHandler(IHandlerId iHandlerId) {

    
    if (iHandlerId >= mIHandlerTypes.size()) {

        throw SnakeException("Attempting to initialise input handler with Id which is greater than maximum input handler Id");

    }

    if (!mIHandlerTypes[iHandlerId].init) {

        throw SnakeException("Attempting to create input handler with unitialised type");

    }

    return mIHandlerTypes[iHandlerId].factory();

}

} // namespace snk
