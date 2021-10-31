#include "../Inc/Renderer2D.h"

Renderer2D::Renderer2D(){

}

void Renderer2D::setupText(const char* filePath){

    FT_Library ft;
    if(FT_Init_FreeType(&ft))
    {
        std::cout<<"No freetype"<<std::endl;
    }
    FT_Face fc;
    if(FT_New_Face(ft, filePath,0,&fc))
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
        this->characters.insert(std::pair<char,Character>(m,ch));
    }

    //this->allShaders[CHAR_PROG]->set1i(0,"textr");

    FT_Done_Face(fc);
    FT_Done_FreeType(ft);

    glGenVertexArrays(1,&this->textVAO);
    glGenBuffers(1,&this->textVBO);
    glBindVertexArray(this->textVAO);
    glBindBuffer(GL_ARRAY_BUFFER,this->textVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*6*4,NULL,GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

 void Renderer2D::init(const char* filePath, const char* vertexPath, const char* fragPath){
        glGenVertexArrays(1, &this->basicVAO);
        glGenVertexArrays(1,&this->transVAO);
        glGenBuffers(1, &this->basicVBO);
        glGenBuffers(1,&this->transVBO);
        setupText(filePath);
        this->charProg = new Shader(vertexPath, fragPath);
}

void Renderer2D::update(int width, int height){
    this->windowWidth = (float)width;
    this->windowHeight = (float)height;
}

void Renderer2D::updateBasicVAO()
{
    glBindVertexArray(this->basicVAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->basicVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex2D)*this->basicVertices.size(), this->basicVertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex2D), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,2, GL_FLOAT, GL_FALSE, sizeof(vertex2D), (void*)offsetof(vertex2D, textr));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2,4, GL_FLOAT, GL_FALSE, sizeof(vertex2D), (void*)offsetof(vertex2D, col));
    glEnableVertexAttribArray(2);
    glVertexAttribIPointer(3, 1, GL_UNSIGNED_INT, sizeof(vertex2D), (void*)offsetof(vertex2D, textNr));
    glEnableVertexAttribArray(3);
    glBindVertexArray(0);
}

void Renderer2D::updateTransVAO()
{
    glBindVertexArray(this->transVAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->transVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex2D)*this->transparentVertices.size(), this->transparentVertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex2D), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,2, GL_FLOAT, GL_FALSE, sizeof(vertex2D), (void*)offsetof(vertex2D, textr));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2,4, GL_FLOAT, GL_FALSE, sizeof(vertex2D), (void*)offsetof(vertex2D, col));
    glEnableVertexAttribArray(2);
    glVertexAttribIPointer(3, 1, GL_UNSIGNED_INT, sizeof(vertex2D), (void*)offsetof(vertex2D, textNr));
    glEnableVertexAttribArray(3);
    glBindVertexArray(0);
}

void Renderer2D::setTexture(Texture *textr)
{
        this->textures.push_back(textr);
        this->textureAmount++;
}

void Renderer2D::writeText(std::string text, GLfloat wPart, GLfloat hPart,GLfloat scale,glm::vec3 color)
{
    GLfloat x = float(this->windowWidth)*wPart;
    GLfloat y = float(this->windowHeight)*hPart;
    glEnable(GL_BLEND);
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
    glm::mat4 proj = glm::ortho(0.0f, float(this->windowWidth), 0.0f, float(this->windowHeight),-1.0f,1.0f);
    this->charProg->setMat4(proj,"projectionMatrix");
    this->charProg->setVec3f(color,"textCol");
    this->charProg->use();
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(this->textVAO);
    std::string::const_iterator c;
    GLfloat sum = 0;
    for(c=text.begin(); c!=text.end(); c++)
    {
        Character ch = this->characters[*c];
        sum+=(ch.advance >> 6) * scale;
    }
    x=x-sum/2;
    for(c=text.begin(); c!=text.end(); c++)
    {
        Character ch = this->characters[*c];
        GLfloat xPos = x+ch.bear.x*scale;
        GLfloat yPos = y-((ch.siz.y-ch.bear.y)*scale);
        GLfloat chW = ch.siz.x*scale;
        GLfloat chH = ch.siz.y*scale;
        GLfloat chVertices[6][4]=
        {
            {xPos,yPos+chH,0.0,0.0},
            {xPos,yPos,0.0,1.0},
            {xPos+chW,yPos,1.0,1.0},
            {xPos,yPos+chH,0.0,0.0},
            {xPos+chW,yPos,1.0,1.0},
            {xPos+chW,yPos+chH,1.0,0.0}
        };
        glBindTexture(GL_TEXTURE_2D,ch.text);
        glBindBuffer(GL_ARRAY_BUFFER,this->textVBO);
        glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(chVertices),chVertices);
        glDrawArrays(GL_TRIANGLES,0,6);
        x += (ch.advance >> 6) * scale;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D,0);
    glDisable(GL_BLEND);
}

void Renderer2D::setBasicSprite(float posX, float posY, float sizX, float sizY, glm::vec4 color, int textN, float textureBegin,float textureEnd)
{
    this->basicVertices.push_back(vertex2D{glm::vec2(this->windowWidth*(posX-sizX/2),this->windowHeight*(posY+sizY/2)),
                                  glm::vec2(textureBegin,1.0),color,textN-1});
    this->basicVertices.push_back(vertex2D{glm::vec2(this->windowWidth*(posX-sizX/2),this->windowHeight*(posY-sizY/2)),
                                  glm::vec2(textureBegin,0.0),color,textN-1});
    this->basicVertices.push_back(vertex2D{glm::vec2(this->windowWidth*(posX+sizX/2),this->windowHeight*(posY-sizY/2)),
                                  glm::vec2(textureEnd,0.0),color,textN-1});
    this->basicVertices.push_back(vertex2D{glm::vec2(this->windowWidth*(posX-sizX/2),this->windowHeight*(posY+sizY/2)),
                                  glm::vec2(textureBegin,1.0),color,textN-1});
    this->basicVertices.push_back(vertex2D{glm::vec2(this->windowWidth*(posX+sizX/2),this->windowHeight*(posY-sizY/2)),
                                  glm::vec2(textureEnd,0.0),color,textN-1});
    this->basicVertices.push_back(vertex2D{glm::vec2(this->windowWidth*(posX+sizX/2),this->windowHeight*(posY+sizY/2)),
                                  glm::vec2(textureEnd,1.0),color,textN-1});
}
void Renderer2D::setTransparentSprite(float posX, float posY, float sizX, float sizY, glm::vec4 color, int textN, float textureBegin,float textureEnd)
{
    this->transparentVertices.push_back(vertex2D{glm::vec2(this->windowWidth*(posX-sizX/2),this->windowHeight*(posY+sizY/2)),
                                  glm::vec2(textureBegin,1.0),color,textN-1});
    this->transparentVertices.push_back(vertex2D{glm::vec2(this->windowWidth*(posX-sizX/2),this->windowHeight*(posY-sizY/2)),
                                  glm::vec2(textureBegin,0.0),color,textN-1});
    this->transparentVertices.push_back(vertex2D{glm::vec2(this->windowWidth*(posX+sizX/2),this->windowHeight*(posY-sizY/2)),
                                  glm::vec2(textureEnd,0.0),color,textN-1});
    this->transparentVertices.push_back(vertex2D{glm::vec2(this->windowWidth*(posX-sizX/2),this->windowHeight*(posY+sizY/2)),
                                  glm::vec2(textureBegin,1.0),color,textN-1});
    this->transparentVertices.push_back(vertex2D{glm::vec2(this->windowWidth*(posX+sizX/2),this->windowHeight*(posY-sizY/2)),
                                  glm::vec2(textureEnd,0.0),color,textN-1});
    this->transparentVertices.push_back(vertex2D{glm::vec2(this->windowWidth*(posX+sizX/2),this->windowHeight*(posY+sizY/2)),
                                  glm::vec2(textureEnd,1.0),color,textN-1});
}

void Renderer2D::clearVerts()
{
    this->basicVertices.clear();
    this->transparentVertices.clear();
}

void Renderer2D::drawBasic(Shader* shad)
{
    this->updateBasicVAO();
    //blocks
    for(int i = 0; i<this->textures.size(); i++)
    {
        std::stringstream ms;
        std::string mIndex;
        ms<<i;
        mIndex=ms.str();
        shad->set1i(this->textures[i]->getUnit(),("textr["+mIndex+"]").c_str());
        this->textures[i]->bindT();
    }
    glBindVertexArray(this->basicVAO);
    shad->use();
    glDrawArrays(GL_TRIANGLES,0,this->basicVertices.size());
}

void Renderer2D::drawTransparent(Shader* shad)
{
    this->updateTransVAO();
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glBindVertexArray(this->transVAO);
    shad->use();
    glDrawArrays(GL_TRIANGLES,0,this->transparentVertices.size());
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}

void Renderer2D::render2D(Shader* shad)
{
    this->drawBasic(shad);
    if(this->transparentVertices.size()>0)
    {
        drawTransparent(shad);
    }
}
