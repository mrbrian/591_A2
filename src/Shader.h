#ifndef SHADER_H
#define SHADER_H

#include "GL/glew.h"
#include <iostream>
#include <fstream>

class Shader
{
public:
    Shader();

    virtual void startup (int mIdx, int tIdx) = 0;

    virtual void shutdown () = 0;

    virtual void createVertexBuffer( std::string model, std::string texture ) = 0;

    virtual void render() = 0;

    virtual ~Shader();

protected:

    virtual GLuint compile_shaders ( const char* vertexFilename, const char* fragmentFilename );

    virtual GLuint compile_shaders( const char* vertexFilename, const char* fragmentFilename, const char* geometryFilename );

    GLchar* loadshader (std::string filename);

    void unloadshader (GLchar** ShaderSource);

    unsigned long getFileLength (std::ifstream& file);

};

#endif // SHADER_H
