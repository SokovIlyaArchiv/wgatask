#include "Game.h"

Game::Game(Vector2u windowSize) :
    window(VideoMode(windowSize.x, windowSize.y), "WGA_TASK", Style::Default),
    data({windowSize}, {5, 5}, EVENT::START), eventHandler(data),
    interfaceHandler(window, data), interfaceDrawer(data) {
    window.setFramerateLimit(60);
}

void Game::exec() {
    while(window.isOpen()) {
        interfaceHandler.handle();
        eventHandler.handle();
        window.draw(interfaceDrawer);
        window.display();
    }
}
