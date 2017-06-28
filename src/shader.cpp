#include <fstream>
#include "GL/glew.h"
#include "error/snkexception.hpp"
#include "error/glexception.hpp"
#include "shader.hpp"

namespace snk {

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
: mProgramID(0) {

    initProgram(vertexPath, fragmentPath);

}


void Shader::bind() {

    glUseProgram(mProgramID);
    checkGLError();

}


void Shader::unbind() {

    glUseProgram(0);

}


Shader::~Shader() {

    destroyProgram();

}


void Shader::initProgram(const std::string& vertexPath, const std::string& fragmentPath) {

    mProgramID = glCreateProgram();

    GLuint vertexID = loadShader(vertexPath, GL_VERTEX_SHADER);
    glAttachShader(mProgramID, vertexID);

    GLuint fragmentID = 0;
    try {

        fragmentID = loadShader(fragmentPath, GL_FRAGMENT_SHADER);

    // If loading fragment shade fails. Delete vertex shader then throw
    // exception again.
    } catch (std::exception& e) {

        glDeleteShader(vertexID);
        throw;

    }
    glAttachShader(mProgramID, fragmentID);

    glLinkProgram(mProgramID);

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);

    // Check successful link.
    GLint success = 0;
    glGetProgramiv(mProgramID, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) {

        std::string log = getProgramLog(mProgramID);
        glDeleteProgram(mProgramID);
        throw SnakeException("Error linking shader program. Info log:\n" + log);

    }

}


void Shader::destroyProgram() {

    glDeleteProgram(mProgramID);

}


GLuint loadShader(const std::string& path, GLenum type) {

    GLuint shaderID;
    std::string shaderString = getContents(path);

    shaderID = glCreateShader(type);

    const GLchar* shaderSrc = shaderString.c_str();
    glShaderSource(shaderID, 1, &shaderSrc, nullptr);
    glCompileShader(shaderID);

    GLint success = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {

        std::string log = getShaderLog(shaderID);
        glDeleteShader(shaderID);
        throw SnakeException("Error compiling shader from " + path + ". Info log:\n" + log);

    }

    return shaderID;

}


std::string getContents(const std::string& path) {

    std::ifstream inFile(path, std::ios::in);

    if (!inFile) {

        // Exception.
        throw SnakeException("Failed to open file: " + path);

    }

    std::string contents;
    std::string line;
    while (!inFile.eof()) {

        std::getline(inFile, line);
        contents += (line + '\n');

    }
    inFile.close();

    return contents;

}


std::string getProgramLog(GLuint programID) {

    if (!glIsProgram) {

        throw SnakeException("Querying program log with invalid ID");

    }

    int logLen = 0;
    int actualLen = 0;

    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLen);
    char* log = new char[logLen];
    glGetProgramInfoLog(programID, logLen, &actualLen, log);
    std::string logString;
    if (actualLen > 0) {

        logString = std::string(log);

    }
    delete[] log;

    return logString;

}


std::string getShaderLog(GLuint shaderID) {

    if (!glIsShader) {

        throw SnakeException("Querying shader log with invalid ID");

    }

    int logLen = 0;
    int actualLen = 0;

    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLen);
    char* log = new char[logLen];
    glGetShaderInfoLog(shaderID, logLen, &actualLen, log);
    std::string logString;
    if (actualLen > 0) {

        logString = std::string(log);

    }
    delete[] log;

    return logString;

}

} // namespace snk
