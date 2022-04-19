#pragma once
#include <string>
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
public:

	Shader(const std::string& filePath);
	~Shader();

	void Bind() const;
	void UnBind() const;

	void SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4);

private:
	unsigned int GetUniformLocation(const std::string& location);

	unsigned int  CompileShader(unsigned int type, const std::string& source);
	ShaderSources ParseShader(const std::string& filePath);
	unsigned int compilerShader(unsigned int type, const std::string& source);
	unsigned int createShader(const std::string& vertexShader, const std::string& fragmenShader);
};


