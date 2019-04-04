#ifndef TESTSFML_INTERFACEDRAWER_H
#define TESTSFML_INTERFACEDRAWER_H

#include "Data.h"

class InterfaceDrawer : public Drawable {
public:
    InterfaceDrawer(Data& data);
    void draw(RenderTarget& target, RenderStates states) const override;
private:
    void drawField(RenderTarget& target, RenderStates states) const;
    void drawLineColorBlocks(RenderTarget& target, RenderStates states) const;
    void drawGameOverSprite(RenderTarget& target, RenderStates states) const;

    Texture gameOverTexture;

    Data& data;
    Field& field;
};

#endif
