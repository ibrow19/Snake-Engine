#include <fstream>
#include <GL/glew.h>
#include <snk/error/snkexception.hpp>
#include <snk/error/glexception.hpp>
#include <snk/shader/shader.hpp>

namespace snk {

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
: mProgramId(0) {

    initProgram(vertexPath, fragmentPath);

}


Shader::~Shader() {

    destroyProgram();

}


void Shader::bind() const {

    glUseProgram(mProgramId);

}


void Shader::unbind() const {

    glUseProgram(0);

}


GLint Shader::getAttribute(const std::string& attribute) const {

    GLint attributeId = glGetAttribLocation(mProgramId, attribute.c_str());
    if (attributeId == -1) {

        throw SnakeException("Could not locate shader attribure: " + attribute);

    }
    return attributeId;

}


GLint Shader::getUniform(const std::string& uniform) const {

    GLint uniformId = glGetUniformLocation(mProgramId, uniform.c_str());
    if (uniformId == -1) {

        throw SnakeException("Could not locate shader uniform: " + uniform);

    }
    return uniformId;

}


void Shader::initProgram(const std::string& vertexPath, const std::string& fragmentPath) {

    mProgramId = glCreateProgram();

    GLuint vertexId = loadShader(vertexPath, GL_VERTEX_SHADER);
    glAttachShader(mProgramId, vertexId);

    GLuint fragmentId = 0;
    try {

        fragmentId = loadShader(fragmentPath, GL_FRAGMENT_SHADER);

    // If loading fragment shade fails. Delete vertex shader then throw
    // exception again.
    } catch (std::exception& e) {

        glDeleteShader(vertexId);
        throw;

    }
    glAttachShader(mProgramId, fragmentId);

    glLinkProgram(mProgramId);

    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);

    // Check successful link.
    GLint success = 0;
    glGetProgramiv(mProgramId, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) {

        std::string log = getProgramLog(mProgramId);
        glDeleteProgram(mProgramId);
        throw SnakeException("Error linking shader program. Info log:\n" + log);

    }

}


void Shader::destroyProgram() {

    glDeleteProgram(mProgramId);

}


GLuint loadShader(const std::string& path, GLenum type) {

    GLuint shaderId;
    std::string shaderString = getContents(path);

    shaderId = glCreateShader(type);

    const GLchar* shaderSrc = shaderString.c_str();
    glShaderSource(shaderId, 1, &shaderSrc, nullptr);
    glCompileShader(shaderId);

    GLint success = 0;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {

        std::string log = getShaderLog(shaderId);
        glDeleteShader(shaderId);
        throw SnakeException("Error compiling shader from " + path + ". Info log:\n" + log);

    }

    return shaderId;

}


std::string getContents(const std::string& path) {

    std::ifstream inFile;
    inFile.open(path);
    if (!inFile.is_open()) {

        // Exception.
        throw SnakeException("Failed to open file: " + path);

    }

    std::string contents;
    std::string line;

    // TODO: test.
    while (std::getline(inFile, line)) {
        
        contents += (line + '\n');

    }
    inFile.close();

    return contents;

}


// TODO: test.
std::string getProgramLog(GLuint programId) {

    if (!glIsProgram(programId)) {

        throw SnakeException("Querying program log with invalid Id");

    }

    int logLen = 0;
    int actualLen = 0;

    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLen);
    char* log = new char[logLen];
    glGetProgramInfoLog(programId, logLen, &actualLen, log);
    std::string logString;
    if (actualLen > 0) {

        logString = std::string(log);

    }
    delete[] log;

    return logString;

}


std::string getShaderLog(GLuint shaderId) {

    if (!glIsShader(shaderId)) {

        throw SnakeException("Querying shader log with invalid Id");

    }

    int logLen = 0;
    int actualLen = 0;

    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLen);
    char* log = new char[logLen];
    glGetShaderInfoLog(shaderId, logLen, &actualLen, log);
    std::string logString;
    if (actualLen > 0) {

        logString = std::string(log);

    }
    delete[] log;

    return logString;

}


} // namespace snk
