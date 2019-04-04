#include <fstream>
#include "InterfaceDrawer.h"

InterfaceDrawer::InterfaceDrawer(Data& data) : data(data), field(data.getField()) {
    if(!gameOverTexture.loadFromFile("resources/gameover.png")) {
        std::ofstream err("ERROR.txt");
        err << "Error! \'resources/gameover.png\' not found!" << std::endl;
        exit(1);
    }
}

void InterfaceDrawer::draw(RenderTarget &target, RenderStates states) const {
    target.clear({60, 63, 65, 255});
    drawField(target, states);
    drawLineColorBlocks(target, states);
    if(data.getGameEvent() == EVENT::GAME_OVER) {
        drawGameOverSprite(target, states);
    }
}

void InterfaceDrawer::drawField(RenderTarget &target, RenderStates states) const {
    Vector2f cellSize = {(float)data.getCellSize().x, (float)data.getCellSize().y},
             fieldSize = {(float)data.getFieldSize().x, (float)data.getFieldSize().y},
             anchor = {(float)data.getAnchor().x, (float)data.getAnchor().y};
    sf::RectangleShape outline({fieldSize.x*cellSize.x, (fieldSize.y)*cellSize.y});
    outline.setFillColor({255, 255, 255, 255});
    outline.setOutlineColor({30, 30, 30, 255});
    outline.setOutlineThickness(4);
    outline.setPosition(anchor);
    target.draw(outline, states);
    sf::RectangleShape shape(cellSize);
    shape.setOutlineThickness(1);
    shape.setOutlineColor({30, 30, 30, 255});
    for(size_t y = 0; y < fieldSize.y; y++) {
        for (size_t x = 0; x < fieldSize.x; x++) {
            shape.setFillColor(getColorByType(field.getCellValue(1+x+y*(int)fieldSize.x)));
            shape.setPosition({anchor.x + x * cellSize.x, anchor.y + y * cellSize.y});
            target.draw(shape, states);
        }
    }
    size_t nOfSelectedTile = field.getNOfSelectedTile();
    if (nOfSelectedTile) { //Draw selected tile
        size_t  X = (nOfSelectedTile - 1) % (int)fieldSize.x,
                Y = (nOfSelectedTile - 1) / (int)fieldSize.x;
        shape.setPosition(X * cellSize.x + anchor.x, Y * cellSize.y + anchor.y);
        shape.setFillColor({0, 0, 0, 180});
        target.draw(shape, states);
    }
}

void InterfaceDrawer::drawLineColorBlocks(RenderTarget &target, RenderStates states) const {
    Vector2u cellSize = data.getCellSize();
    sf::CircleShape shape(cellSize.x/4.f);
    shape.setOutlineThickness(1);
    shape.setOutlineColor({0, 0, 0, 255});
    for(size_t c = 0; c < 3; c++) {
        shape.setPosition({data.getAnchor().x + c*2*cellSize.x + cellSize.x / 4.f,
                           data.getAnchor().y - cellSize.y * 3 / 4.f - 4.f}); // -4 - it's bold outline
        shape.setFillColor(getColorByType(field.getLineType(c)));
        target.draw(shape, states);
    }
}

void InterfaceDrawer::drawGameOverSprite(RenderTarget &target, RenderStates states) const {
    Sprite gameOverSprite(gameOverTexture);
    gameOverSprite.setPosition(data.getAnchor().x, data.getAnchor().y);
    gameOverSprite.setScale(data.getCellSize().x / (gameOverTexture.getSize().x/5.f),
							data.getCellSize().y / (gameOverTexture.getSize().y/5.f));
    target.draw(gameOverSprite, states);
}
