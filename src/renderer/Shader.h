#ifndef SHADER_H_
#define SHADER_H_

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/rotate_vector.hpp>
#include <gtx/vector_angle.hpp>
class Shader
{
private:
    void CheckCompileErrors(unsigned int shader, std::string type);
    std::string vertexCode;
    std::string fragmentCode;
public:
    unsigned int shaderID;
    Shader(const std::string &_pathVertex, const std::string& _pathFragment);
    ~Shader();

    void Use();
    void SetUniform1Int(const std::string &name, int value) const;
    void SetUniform1Float(const std::string &name, float value) const;
    void SetUniform4Float(const std::string &name, float x, float y, float z, float w) const;
    void SetUniformMat4f(const std::string &name, glm::mat4 matrix);
};
#endif