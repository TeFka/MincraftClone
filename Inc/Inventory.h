#ifndef INVENTORY_H_INCLUDED
#define INVENTORY_H_INCLUDED

#include"struct.h"
#include"BlockData.h"
#include"Renderer2D.h"

struct inventorySlot{
    int itemID=0;
    int amount=0;
};

class Inventory{

private:
    int windowWidth;
    int windowHeight;

    BlockDatabase* bDatabase;
    Renderer2D* renderer;

    const int inventorySize = 100;
    const int inventoryRowSize = 10;
    int fullSlot = 69;
    std::array<inventorySlot,100> items;
    std::array<inventorySlot,10> hotBar;
    int isOpen = 0;

    void setup();

public:

    Inventory(Renderer2D*);

    void openInventory();

    void closeInventory();

    int checkIfOpen();

    void pushItem(int);

    void addItem(int, int);

    void removeItem(int);

    void clearSlot(int);

    void update(int, int);

    void renderText();

    void drawItems();

    void drawInventory();

    void drawHotbar();

    void render();

};

#endif // INVENTORY_H_INCLUDED
