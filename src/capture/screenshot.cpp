#include "capture/screenshot.h"
// Original Code credit http://www.flashbang.se/archives/155 (Heavily modified by Jordan Osborn)

void screenshot (std::string filename){
    GLint size[4];
    glGetIntegerv(GL_VIEWPORT,size);
    glReadBuffer(GL_FRONT);
    GLint64 imageSize = size[2] * size[3] * 3;
    GLubyte *data = new GLubyte[imageSize];
    glReadPixels(0,0,size[2],size[3], GL_BGR,GL_UNSIGNED_BYTE,data);
    GLint x0= size[2] % 256;
    GLint x1= (size[2]-x0)/256;
    GLint y0= size[3] % 256;
    GLint y1= (size[3]-y0)/256;
    //.tga header
    GLubyte header[18]={0,0,2,0,0,0,0,0,0,0,0,0,
                              static_cast<GLubyte >(x0),
                              static_cast<GLubyte >(x1),
                              static_cast<GLubyte >(y0),
                              static_cast<GLubyte >(y1),24,0};

    std::fstream File(filename, std::ios::out | std::ios::binary);
    File.write (reinterpret_cast<char *>(header), sizeof(GLbyte)*18);
    File.write (reinterpret_cast<char *>(data), sizeof(GLbyte)*imageSize);
    File.close();

    delete[] data;
    data=NULL;
}
//