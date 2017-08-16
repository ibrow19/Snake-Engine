#include <iostream>
#include <snk/game.hpp>
#include <snk/error/snkexception.hpp>
#include "component.hpp"
#include "inputhandler.hpp"

int main() {

    try {

        std::cout << "Starting" << std::endl;
        snk::Game game(texture::Id::Count,
                       iHandler::Id::Count,
                       component::Id::Count,
                       node::Id::Count,
                       scene::Id::Count);

        game.setTitle("Game");
        game.registerTexture(texture::Id::Test, "texture.xml");
        game.registerIHandler<TestIHandler>(iHandler::Id::Test);
        game.registerComponent<TestComponent>(component::Id::Test1);
        game.registerComponent<TestComponent2>(component::Id::Test2);

        snk::NodeData nData;
        nData.hasTexture = true;
        nData.textureId = texture::Id::Test;
        nData.components.push_back(component::Id::Test1);

        game.registerNode(node::Id::Test1, nData);

        nData.components.clear();
        nData.components.push_back(component::Id::Test2);
        game.registerNode(node::Id::Test2, nData);

        snk::SceneData sData;
        sData.rootId = node::Id::Test1;
        sData.iHandlerId = iHandler::Id::Test;
        game.registerScene(scene::Id::Test, sData);
        game.setInitialScene(scene::Id::Test);

        game.run();

    } catch (snk::SnakeException& e) {

        fprintf(stderr, "%s\n", e.what());

    }

}
