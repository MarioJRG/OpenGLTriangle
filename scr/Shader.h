#pragma once
#include <string>
#include "glm/glm.hpp"
#include<unordered_map>
struct ShaderSources
{
	std::string VertexShader;
	std::string FragmentShader;
};
class Shader

{
private:
	unsigned int m_RenderID;
	std::string m_filepath;
	std::unordered_map < std::string, int> m_UniformLocationCache;
public:

	Shader(const std::string& filePath);
	~Shader();

	void Bind() const;
	void UnBind() const;

	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name , float value);
	void SetUniformMat4f(const std::string& name, const glm::mat4& projection);
	void SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4);


private:
	unsigned int GetUniformLocation(const std::string& location);

	
	ShaderSources ParseShader(const std::string& filePath);
	unsigned int compilerShader(unsigned int type, const std::string& source);
	unsigned int createShader(const std::string& vertexShader, const std::string& fragmenShader);
};


