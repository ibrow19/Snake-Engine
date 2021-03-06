#include <iostream>
#include <snk/game.hpp>
#include <snk/error/snkexception.hpp>
#include "inputhandler.hpp"
#include "identifiers.hpp"
#include "ship.hpp"
#include "turret.hpp"
#include "rotation.hpp"

int main() {

    try {

        std::cout << "Starting" << std::endl;
        snk::Game game(texture::Id::Count,
                       iHandler::Id::Count,
                       component::Id::Count,
                       node::Id::Count,
                       scene::Id::Count);

        game.setTitle("Game");

        // Register textures.
        game.registerTexture(texture::Id::Ship, "ship.xml");

        // Register Input handler.
        game.registerIHandler<Input>(iHandler::Id::Input);

        // Register Components.
        game.registerComponent<ShipComponent>(component::Id::Ship);
        game.registerComponent<TurretComponent>(component::Id::Turret);
        game.registerComponent<RotationComponent>(component::Id::ShipRotation);
        game.registerComponent<RotationComponent>(component::Id::TurretRotation);

        // Register ship node.
        snk::NodeData nData;
        nData.hasTexture = true;
        nData.textureId = texture::Id::Ship;
        nData.components.push_back(component::Id::Ship);
        nData.components.push_back(component::Id::ShipRotation);
        game.registerNode(node::Id::Ship, nData);

        // Register turret node.
        nData.components.clear();
        nData.textureId = texture::Id::Ship;
        nData.components.push_back(component::Id::Turret);
        nData.components.push_back(component::Id::TurretRotation);
        game.registerNode(node::Id::Turret, nData);

        // Initialise scene.
        snk::SceneData sData;
        sData.rootId = node::Id::Ship;
        sData.iHandlerId = iHandler::Id::Input;
        game.registerScene(scene::Id::Scene, sData);
        game.setInitialScene(scene::Id::Scene);

        game.run();

    } catch (snk::SnakeException& e) {

        fprintf(stderr, "%s\n", e.what());

    }

}
