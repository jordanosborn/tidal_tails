//

#include "capture/screenshot.h"
// Created by Jordan Osborn on 13/01/2017.

// Original Code credit http://www.flashbang.se/archives/155 (Heavily modified by Jordan Osborn)

void screenshot (std::string filename){
    GLint size[4];
    glGetIntegerv(GL_VIEWPORT,size);
    glReadBuffer(GL_FRONT);
    GLint64 imageSize = size[2] * size[3] * 3;
    GLubyte *data = new GLubyte[imageSize];
    glReadPixels(0,0,size[2],size[3], GL_BGR,GL_UNSIGNED_BYTE,data);
    GLint xa= size[2] % 256;
    GLint xb= (size[2]-xa)/256;GLint ya= size[3] % 256;
    GLint yb= (size[3]-ya)/256;
    //.tga header
    GLubyte header[18]={0,0,2,0,0,0,0,0,0,0,0,0,
                              static_cast<GLubyte >(xa),
                              static_cast<GLubyte >(xb),
                              static_cast<GLubyte >(ya),
                              static_cast<GLubyte >(yb),24,0};

    std::fstream File(filename, std::ios::out | std::ios::binary);
    File.write (reinterpret_cast<char *>(header), sizeof(GLbyte)*18);
    File.write (reinterpret_cast<char *>(data), sizeof(GLbyte)*imageSize);
    File.close();

    delete[] data;
    data=NULL;
}
//