#ifndef SNAKE_INPUT_HANDLER_FACTORY_HEADER
#define SNAKE_INPUT_HANDLER_FACTORY_HEADER

#include <vector>
#include <identifiers.hpp>
#include <error/snkexception.hpp>
#include <scene/input/inputhandler.hpp>

namespace snk {

/// Factory for creating input handlers for scenes.
class IHandlerFactory {
public:

    IHandlerFactory(unsigned int iHandlerCount);

    template<typename T>
    void registerIHandler(IHandlerId iHandlerId);

    std::unique_ptr<InputHandler> createIHandler(IHandlerId iHandlerId);

private:

    typedef std::function<std::unique_ptr<InputHandler>()> Factory;

private:

    struct IHandlerType {

        bool init = false;
        Factory factory;

    };

private:

    // Factories for creating components.
    std::vector<IHandlerType> mIHandlerTypes;

};


template<typename T>
void IHandlerFactory::registerIHandler(IHandlerId iHandlerId) {

    if (iHandlerId >= mIHandlerTypes.size()) {

        throw SnakeException("Attempting to initialise input handler type Id which is greater than maximum input handler Id");

    }

    if (mIHandlerTypes[iHandlerId].init) {

        throw SnakeException("Attempting to initialise already initialised input handler type Id");

    }

    mIHandlerTypes[iHandlerId].init = true;
    mIHandlerTypes[iHandlerId].factory = 
    []() {

        return std::unique_ptr<T>(new T());

    };

}

} // namespace snk

#endif
