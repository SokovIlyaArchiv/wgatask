#include "EventHandler.h"

#include <random>

EventHandler::EventHandler(Data& data) :
    data(data), field(data.getField()) {
    data.setGameEvent(EVENT::START);
    srand(time(NULL));
}

void EventHandler::handle() {
    switch (data.getGameEvent()) {
        case EVENT::START: {
            generateField();
            field.setSelectedTile(0);
            data.setGameEvent(EVENT::WAITING);
            break;
        }
        case EVENT::HAVE_A_TARGET: {
            size_t nOfSelectedTile = field.getNOfSelectedTile(),
                   nOfTarget = field.getNOfTarget();  //number of target cell
            if(!isTargetNearOfTile(nOfSelectedTile, nOfTarget)) {
                data.setGameEvent(EVENT::HAVE_A_TILE);
                break;
            }
            CELL_TYPE typeOfSelectedTile = field.getCellValue(nOfSelectedTile),
                      typeOfTarget = field.getCellValue(nOfTarget);
            if(typeOfTarget == CELL_TYPE::EMPTY) {
                CELL_TYPE  temp = typeOfSelectedTile;
                field.setCellValue(nOfSelectedTile, typeOfTarget);
                field.setCellValue(nOfTarget, temp);
                if(isVictory()) {
                    data.setGameEvent(EVENT::GAME_OVER);
                } else {
                    data.setGameEvent(EVENT::WAITING);
                    field.setSelectedTile(0);
                }
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

void EventHandler::generateField() {
    for(size_t c = 0; c <= 20; c+=5) {
        if(c % 2) {
            field.setCellValue(2+c, CELL_TYPE::EMPTY);
            field.setCellValue(4+c, CELL_TYPE::EMPTY);
        } else {
            field.setCellValue(2+c, CELL_TYPE::BLOCK);
            field.setCellValue(4+c, CELL_TYPE::BLOCK);
        }
    }
    std::vector<CELL_TYPE> cells(15, CELL_TYPE::RED); //Sorted vector
    for(size_t c = 0; c < 5; c++) {
        cells[c+5] = CELL_TYPE::ORANGE;
        cells[c+10] = CELL_TYPE::YELLOW;
    }
    for(size_t i = cells.size()-1; i > 0; i--) { //Fisher–Yates shuffle
        size_t j;
        j = rand() % (i + 1);
        std::swap(cells[i], cells[j]);
    }
    size_t counter = 0;
    for(size_t x = 1; x <= 5; x+=2) {
        for(size_t y = 0; y <= 4; y++) {
            field.setCellValue(y*5+x, (CELL_TYPE)cells[counter]); //filling cells
            counter++;
        }
    }
}

bool EventHandler::isVictory() {
    for(size_t c = 0; c < 3; c++) {
        CELL_TYPE lineType = field.getLineType(c);
        for(size_t y = 0; y < 5; y++) {
            if(field.getCellValue(1+c*2+y*5) != lineType) {
                return false;
            }
        }
    }
    return true;
}

bool EventHandler::isTargetNearOfTile(short nOfSelectedTile, short nOfTarget) const {
    return abs(nOfSelectedTile - nOfTarget) == (short)data.getFieldSize().x || // Up and Down
           abs(nOfSelectedTile - nOfTarget) <= 1; //Left Center(Unselect tile) Right
}
