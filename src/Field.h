#ifndef TESTSFML_FIELD_H
#define TESTSFML_FIELD_H

#include <vector>

#include <SFML/Graphics.hpp>
using namespace sf;

enum class CELL_TYPE {EMPTY, BLOCK, RED, ORANGE, YELLOW};

Color getColorByType(CELL_TYPE type);

class Field {
public:
    Field(size_t length, size_t height);

    void setSelectedTile(size_t cellNumber) {nOfSelectedTile = cellNumber;}
    void setTarget(size_t cellNumber) {nOfTarget = cellNumber;}
    void setCellValue(size_t cellNumber, CELL_TYPE value);

    size_t getNOfSelectedTile() const {return nOfSelectedTile;}
    size_t getNOfTarget() const {return nOfTarget;}
    CELL_TYPE getCellValue(size_t cellNumber) const;
    CELL_TYPE getLineType(size_t lineNumber) const;
private:
    std::vector<std::vector<CELL_TYPE>> field;
    size_t nOfSelectedTile, nOfTarget; //number of selected tile || ==||== of target
    std::vector<CELL_TYPE> lines;
};

#endif
