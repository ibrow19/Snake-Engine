#ifndef DEMO_IDENTIFIER_HEADER
#define DEMO_IDENTIFIER_HEADER

#include <snk/identifiers.hpp>

namespace texture {

enum Id : snk::TextureId {

    Ship,
    Turret,
    Count

};

}


namespace iHandler {

enum Id : snk::IHandlerId {

    Input,
    Count

};

}


namespace component {

enum Id : snk::ComponentId {

    Ship,
    Turret,
    TurretRotation,
    ShipRotation,
    Count

};

}


namespace node {

enum Id : snk::NodeId {

    Ship,
    Turret,
    Count

};

}


namespace scene {

enum Id : snk::SceneId {

    Scene,
    Count

};

}

#endif
