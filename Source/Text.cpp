
#include "./Text.h"


Text::Text(){



}

Text::Text(std::string newValue)
{

    textValue = newValue;

}
Text::~Text()
{


}

float Text::checkTextLength(std::string theString, float scale)
{

    float theLength = 0;
    for(std::string::const_iterator c=theString.begin(); c!=theString.end(); c++)
    {
        Character ch = characters[*c];
        theLength += ((ch.bear.x+ch.siz.x)*scale);
    }
    return theLength;
}

float Text::checkTextMaxHeight(std::string theString, float scale)
{

    float theMax = 0;
    for( std::string::const_iterator c=theString.begin(); c!=theString.end(); c++)
    {
        Character ch = characters[*c];
        if(theMax<ch.siz.y*scale)
        {

            theMax = ch.siz.y*scale;

        }
    }
    return theMax;
}


void Text::setTextFont(std::string filePath)
{

    FT_Library ft;
    if(FT_Init_FreeType(&ft))
    {
        std::cout<<"No freetype"<<std::endl;
    }
    FT_Face fc;
    if(FT_New_Face(ft, filePath.c_str(),0,&fc))
    {
        std::cout<<"No freetype face"<<std::endl;
    }
    FT_Set_Pixel_Sizes(fc,0,48);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);

    for(int m = 0; m<128; m++)
    {
        if(FT_Load_Char(fc,m,FT_LOAD_RENDER))
        {
            std::cout<<"Error: No glyph"<<std::endl;
        }
        GLuint textch;
        glGenTextures(1,&textch);
        glBindTexture(GL_TEXTURE_2D,textch);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RED,
                     fc->glyph->bitmap.width,fc->glyph->bitmap.rows,
                     0,GL_RED,GL_UNSIGNED_BYTE,fc->glyph->bitmap.buffer);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        Character ch =
        {
            textch,
            glm::vec2(fc->glyph->bitmap.width,fc->glyph->bitmap.rows),
            glm::vec2(fc->glyph->bitmap_left,fc->glyph->bitmap_top),
            fc->glyph->advance.x
        };
        if(m=='g' || m=='y'|| m=='p'){
            ch.bear.y = ch.bear.y - ch.siz.y*0.3;
        }
        characters.insert(std::pair<char,Character>(m,ch));
    }

    FT_Done_Face(fc);
    FT_Done_FreeType(ft);

}

void Text::setTextValue(std::string newValue){

    textValue = newValue;

}

void Text::setPosition(glm::vec2 newPos){

    position = newPos;

}

void Text::setScale(int newScale){

    scale = newScale;

}

void Text::setColor(glm::vec4 newColor){

    color = newColor;

}
