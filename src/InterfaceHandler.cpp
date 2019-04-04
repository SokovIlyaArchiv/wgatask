#include "InterfaceHandler.h"
#include <iostream>

InterfaceHandler::InterfaceHandler(RenderWindow &window, Data& data) :
    window(window), data(data) {
}


void InterfaceHandler::handle() {
    Event windowEvent;
    Field& field = data.getField();
    EVENT gameEvent = data.getGameEvent();
    if(window.pollEvent(windowEvent)) {
        switch (windowEvent.type) {
            case Event::Closed: {
                window.close();
                break;
            }
            case Event::Resized: {
                auto  X = window.getSize().x, Y = window.getSize().y;
                if(X < 100 || Y < 100) {
                    window.setSize({100, 100});
                } else {
                    if(X / Y > 5) {
                        window.setSize({X, X/4});
                    }
                    if(Y / X > 5) {
                        window.setSize({Y/4, Y});
                    }
                }
                data.windowWasResized(window.getSize());
                window.setView(sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y)));
                break;
            }
            case Event::MouseButtonPressed: {
                if(Mouse::isButtonPressed(Mouse::Button::Left)) {
                    size_t cellNumber = getCellNumberByCoord(Mouse::getPosition(window));
                    switch (data.getGameEvent()) {
                        case EVENT::WAITING: {
                            if(cellNumber) {
                                CELL_TYPE cellType = field.getCellValue(cellNumber);
                                if(cellType != CELL_TYPE::EMPTY && cellType != CELL_TYPE::BLOCK) {
                                    field.setSelectedTile(cellNumber);
                                    data.setGameEvent(EVENT::HAVE_A_TILE);
                                }
                            }
                            break;
                        }
                        case EVENT::HAVE_A_TILE: {
                            if(cellNumber) {
                                field.setTarget(cellNumber);
                                data.setGameEvent(EVENT::HAVE_A_TARGET);
                            } else {
                                data.setGameEvent(EVENT::WAITING);
                                field.setSelectedTile(0);
                            }
                            break;
                        }
                        default:
                            break;

                    }
                }
                if(Mouse::isButtonPressed(Mouse::Button::Right) && gameEvent == EVENT::HAVE_A_TILE) {
                    field.setSelectedTile(0);
                    data.setGameEvent(EVENT::WAITING);
                }
                break;
            }
            case Event::KeyPressed: {
                if(Keyboard::isKeyPressed(Keyboard::Escape) && gameEvent == EVENT::GAME_OVER) {
                    window.close();
                }
                if(Keyboard::isKeyPressed(Keyboard::R) && gameEvent == EVENT::GAME_OVER) {
                    data.setGameEvent(EVENT::START);
                }
                break;
            }
            default:
                break;
        }
    }

}

size_t InterfaceHandler::getCellNumberByCoord(Vector2i coords) const {
    size_t  X = (coords.x - data.getAnchor().x) / data.getCellSize().x,
            Y = (coords.y - data.getAnchor().y) / data.getCellSize().y;
    if(Y < data.getFieldSize().y && data.getFieldSize().x > X) {
        return X + Y * data.getFieldSize().x + 1;
    }
    return 0;
}

