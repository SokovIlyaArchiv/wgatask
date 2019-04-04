#include "Field.h"

Color getColorByType(CELL_TYPE type) {
    switch (type) {
        case CELL_TYPE::EMPTY:
            return {242, 243, 244, 255};
        case CELL_TYPE::BLOCK:
            return {30, 30, 30, 255};
        case CELL_TYPE::RED:
            return {255, 3, 62, 255};
        case CELL_TYPE::YELLOW:
            return {255, 233, 16, 255};
        case CELL_TYPE::ORANGE:
            return {255, 130, 20, 255};
        default:
            return {0, 0, 0, 255};
    }
}

Field::Field(size_t length, size_t height) {
    field.resize(height);
    for(auto& row : field) {
        row.resize(length);
    }
    lines.resize(3, CELL_TYPE::YELLOW);
    lines[1] = CELL_TYPE::ORANGE;
    lines[2] = CELL_TYPE::RED;
}

void Field::setCellValue(size_t cellNumber, CELL_TYPE value) {
    if(cellNumber != 0 && cellNumber <= field.size()*field.back().size()) {
        size_t X = (cellNumber-1)%field.back().size(), Y = (cellNumber-1)/field.back().size();
        field[Y][X] = value;
    }
}


CELL_TYPE Field::getCellValue(size_t cellNumber) const{
    if(cellNumber != 0 && cellNumber <= field.size()*field.back().size()) {
        size_t X = (cellNumber-1)%field.back().size(), Y = (cellNumber-1)/field.back().size();
        return  field[Y][X];
    }
    return CELL_TYPE::EMPTY;
}

CELL_TYPE Field::getLineType(size_t lineNumber) const {
    {return (lineNumber < 3)? lines[lineNumber] : CELL_TYPE::EMPTY;}
}