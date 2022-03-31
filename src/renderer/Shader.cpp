#include "Shader.h"


Shader::Shader(const std::string &_pathVertex, const std::string& _pathFragment){
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vShaderFile.open(_pathVertex);
        fShaderFile.open(_pathFragment);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure &e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    CheckCompileErrors(vertex, "VERTEX");
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    CheckCompileErrors(fragment, "FRAGMENT");
    shaderID= glCreateProgram();
    glAttachShader(shaderID, vertex);
    glAttachShader(shaderID, fragment);
    glLinkProgram(shaderID);
    CheckCompileErrors(shaderID, "PROGRAM");
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}
Shader::~Shader(){

}

void Shader::CheckCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}
void Shader::Use(){
    glUseProgram(shaderID);
}
void Shader::SetUniform1Int(const std::string &name, int value) const{
    glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
}
void Shader::SetUniform1Float(const std::string &name, float value) const{
    glUniform1f(glGetUniformLocation(shaderID, name.c_str()), value);
}
void Shader::SetUniform4Float(const std::string &name, float x, float y, float z, float w) const{
    glUniform4f(glGetUniformLocation(shaderID, name.c_str()),x,y,z,w);
}

void Shader::SetUniformMat4f(const std::string &name, glm::mat4 matrix)
{
    int location = glGetUniformLocation(shaderID, name.c_str());
    if (location == -1)
    {

        std::cout << "Warning: uniform " << name << "doesn't exist" << std::endl;
    }
    glUniformMatrix4fv(glGetUniformLocation(shaderID,name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}