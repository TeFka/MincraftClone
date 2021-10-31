#include "../Inc/Inventory.h"

Inventory::Inventory(Renderer2D* rendr)
{
    this->renderer = rendr;
    this->bDatabase = new BlockDatabase();
}

void Inventory::setup()
{

}

void Inventory::openInventory(){
    this->isOpen = 1;
}

void Inventory::closeInventory(){
    this->isOpen = 0;
}

int Inventory::checkIfOpen(){
    return this->isOpen;
}

void Inventory::pushItem(int ID)
{
    int firstEmpty = 100;
    int emptyFound = 0;
    for(int i = 0;i<this->inventorySize;i++)
    {
        if(!emptyFound){
        if(this->items[i].itemID==0){
            firstEmpty = i;
            emptyFound = 1;
        }
        }
        if(this->items[i].itemID==ID){
            this->items[i].amount++;
            return;
        }
    }
    this->items[firstEmpty].itemID=ID;
    this->items[firstEmpty].amount=1;
}

void Inventory::addItem(int invSlot, int ID)
{
    if(this->items[invSlot].itemID==ID)
    {
        this->items[invSlot].amount++;
    }
    else
    {
        if(this->items[invSlot].amount==0){
            this->items[invSlot].amount = 1;
            this->items[invSlot].itemID==ID;
        }
        else{
            this->pushItem(ID);
        }
    }
}

void Inventory::clearSlot(int invSlot)
{
    if(this->items[invSlot].itemID>0)
    {
        this->items[invSlot].amount=0;
        this->items[invSlot].itemID = 0;
    }
}

void Inventory::removeItem(int invSlot)
{
    if(this->items[invSlot].itemID>0)
    {
        this->items[invSlot].amount--;
        if(this->items[invSlot].amount==0)
        {
            this->items[invSlot].itemID = 0;
        }
    }
}

void Inventory::update(int width, int height){
    this->windowWidth = width;
    this->windowHeight = height;
}

void Inventory::drawInventory()
{
    this->renderer->setBasicSprite(0.51f,0.59f, 0.72f, 0.76, glm::vec4(0.4,0.4,0.4,1.0),16);
    for(int i = 0;i<this->inventorySize;i++){
        this->renderer->setBasicSprite(0.2f+((float)(i%this->inventoryRowSize)*0.07f), 0.93f-((float)(i/this->inventoryRowSize)*0.075f),0.06f,0.06f,
                                       glm::vec4(0.8,0.8,0.8,1.0),16);
    }
}

void Inventory::drawItems(){
    for(int i = 0;i<this->inventorySize;i++){
        if(this->items[i].itemID>0){
        this->renderer->setBasicSprite(0.2+((float)(i%this->inventoryRowSize)*0.07),0.93-((float)(i/this->inventoryRowSize)*0.075),0.05f,0.05f,
                                       glm::vec4(0.8,0.8,0.8,1.0),1,
                                       this->bDatabase->blockTypes[this->items[i].itemID].sideTextureBegin,
                                       this->bDatabase->blockTypes[this->items[i].itemID].sideTextureEnd);
        }
    }
}

void Inventory::drawHotbar(){
    this->renderer->setBasicSprite(0.51f,0.1f,0.72f,0.1f,glm::vec4(0.4,0.4,0.4,1.0),16);
    for(int i = 0;i<this->inventoryRowSize;i++){
        this->renderer->setBasicSprite(0.2f+((float)i*0.07f),0.1f,0.06f,0.06f, glm::vec4(0.8,0.8,0.8,1.0),16);
    }
}

void Inventory::renderText(){
    if(this->isOpen){
    for(int i = 0;i<this->inventorySize;i++){
            if(this->items[i].itemID!=0){
                std::stringstream wordTransfer;
                std::string word;
                wordTransfer<<(this->items[i].amount);
                word = wordTransfer.str();
                this->renderer->writeText(word, 0.22f+((float)(i%this->inventoryRowSize)*0.07f), 0.91f-((float)(i/this->inventoryRowSize)*0.075f),
                                            0.4f,glm::vec3(0.0,1.0,0.0));
            }
        }
    }
}

void Inventory::render(){
    if(this->isOpen){
        drawInventory();
        this->drawItems();
    }
    this->drawHotbar();
}
