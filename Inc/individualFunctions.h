
long long GetCurrentTimeMillis()
{
#ifdef WIN32
    //return GetTickCount();
#else
    timeval t;
    gettimeofday(&t, NULL);

    long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
    return ret;
#endif
}

int getRandomInt(){
    return (100*(rand()/RAND_MAX));
}
//column major
/*glm::mat4 getAssimp4f(const aiMatrix4x4 daAssimp){
        glm::mat4 m;
        m[0][0] = daAssimp.a1; m[1][0] = daAssimp.b1; m[2][0] = daAssimp.c1; m[3][0] = daAssimp.d1;
        m[0][1] = daAssimp.a2; m[1][1] = daAssimp.b2; m[2][1] = daAssimp.c2; m[3][1] = daAssimp.d2;
        m[0][2] = daAssimp.a3; m[1][2] = daAssimp.b3; m[2][2] = daAssimp.c3; m[3][2] = daAssimp.d3;
        m[0][3] = daAssimp.a4; m[1][3] = daAssimp.b4; m[2][3] = daAssimp.c4; m[3][3] = daAssimp.d4;
        return m;
}*/
//row major
glm::mat4 getAssimp4f(const aiMatrix4x4 daAssimp){
        glm::mat4 m;
        m[0][0] = daAssimp.a1; m[0][1] = daAssimp.b1; m[0][2] = daAssimp.c1; m[0][3] = daAssimp.d1;
        m[1][0] = daAssimp.a2; m[1][1] = daAssimp.b2; m[1][2] = daAssimp.c2; m[1][3] = daAssimp.d2;
        m[2][0] = daAssimp.a3; m[2][1] = daAssimp.b3; m[2][2] = daAssimp.c3; m[2][3] = daAssimp.d3;
        m[3][0] = daAssimp.a4; m[3][1] = daAssimp.b4; m[3][2] = daAssimp.c4; m[3][3] = daAssimp.d4;
        return m;
}
//column major
/*glm::mat4 getAssimp3f(const aiMatrix3x3 daAssimp){
        glm::mat4 m;
        m[0][0] = daAssimp.a1; m[1][0] = daAssimp.b1; m[2][0] = daAssimp.c1; m[3][0] = 0.0f;
        m[0][1] = daAssimp.a2; m[1][1] = daAssimp.b2; m[2][1] = daAssimp.c2; m[3][1] = 0.0f;
        m[0][2] = daAssimp.a3; m[1][2] = daAssimp.b3; m[2][2] = daAssimp.c3; m[3][2] = 0.0f;
        m[0][3] = 0.0f; m[1][3] = 0.0f; m[2][3] = 0.0f; m[3][3] = 1.0f;
        return m;
}*/
//row major
glm::mat4 getAssimp3f(const aiMatrix3x3 daAssimp){
        glm::mat4 m;
        m[0][0] = daAssimp.a1; m[0][1] = daAssimp.b1; m[0][2] = daAssimp.c1; m[0][3] = 0.0f;
        m[1][0] = daAssimp.a2; m[1][1] = daAssimp.b2; m[1][2] = daAssimp.c2; m[1][3] = 0.0f;
        m[2][0] = daAssimp.a3; m[2][1] = daAssimp.b3; m[2][2] = daAssimp.c3; m[2][3] = 0.0f;
        m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
        return m;
}

glm::mat4 InitRotateTransform(glm::mat4 originMa, float x, float y, float z)
{
    glm::mat4 rx=glm::mat4(1.0),ry=glm::mat4(1.0),rz=glm::mat4(1.0);

    rx[0][0] = 1.0f; rx[0][1] = 0.0f   ; rx[0][2] = 0.0f    ; rx[0][3] = 0.0f;
    rx[0][1] = 0.0f; rx[0][1] = cosf(x); rx[0][2] = -sinf(x); rx[1][3] = 0.0f;
    rx[0][2] = 0.0f; rx[0][2] = sinf(x); rx[0][2] = cosf(x) ; rx[2][3] = 0.0f;
    rx[0][3] = 0.0f; rx[0][3] = 0.0f   ; rx[0][2] = 0.0f    ; rx[3][3] = 1.0f;

    ry[0][0] = cosf(y); ry[0][1] = 0.0f; ry[0][2] = -sinf(y); ry[0][3] = 0.0f;
    ry[1][0] = 0.0f   ; ry[1][1] = 1.0f; ry[1][2] = 0.0f    ; ry[1][3] = 0.0f;
    ry[2][0] = sinf(y); ry[2][1] = 0.0f; ry[2][2] = cosf(y) ; ry[2][3] = 0.0f;
    ry[3][0] = 0.0f   ; ry[3][1] = 0.0f; ry[3][2] = 0.0f    ; ry[3][3] = 1.0f;

    rz[0][0] = cosf(z); rz[0][1] = -sinf(z); rz[0][2] = 0.0f; rz[0][3] = 0.0f;
    rz[1][0] = sinf(z); rz[1][1] = cosf(z) ; rz[1][2] = 0.0f; rz[1][3] = 0.0f;
    rz[2][0] = 0.0f   ; rz[2][1] = 0.0f    ; rz[2][2] = 1.0f; rz[2][3] = 0.0f;
    rz[3][0] = 0.0f   ; rz[3][1] = 0.0f    ; rz[3][2] = 0.0f; rz[3][3] = 1.0f;

    return rz * ry * rx;
}
