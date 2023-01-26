#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <optional>
#include <sstream>
#include <algorithm>
#include <cassert>

namespace graphix
{

using ShaderId = unsigned;
using ShaderType = unsigned;

struct Shaders {
	Shaders(std::string const& vertexS, std::string const& fragmentS)
		: vertex{vertexS}, fragment{fragmentS} {}
	std::string vertex{};
	std::string fragment{};
};

enum class EShaderType {
	NONE = -1, VERTEX = 0, FRAGMENT = 1
};

class ShaderUtil
{
  public:
	static std::optional<Shaders> readShaders(std::string const& fileName) {
		std::optional<Shaders> shaders{};
		std::ifstream shaderFile{fileName};
		std::stringstream ss[2];
		std::string line{};

		EShaderType type { EShaderType::NONE };
		while(getline(shaderFile, line)) 
		{
			if(line.empty()) continue; // ignore empty lines
			if(line.find("#shader") != std::string::npos) {
				if(line.find("vertex") != std::string::npos) {
					type = EShaderType::VERTEX;
				}
				else {
					type = EShaderType::FRAGMENT;
				}
			}	
			else {
				assert(type != EShaderType::NONE);
				ss[(int)type] << line << '\n';
			}
		}

		return std::make_optional<Shaders>(ss[int(EShaderType::VERTEX)].str(), ss[int(EShaderType::FRAGMENT)].str());
	}

	static std::optional<std::string> readShader(std::string const& fileName) {
		return readShader(fileName.c_str());
	}

	static std::optional<std::string> readShader(char const* fileName)
	{
		std::optional<std::string>{};
		std::ifstream shaderFile{fileName};
		if (not shaderFile)
		{
			std::cerr << "Shader file: " << fileName << " could not be accesed!\n";
			return std::nullopt;
		}
		return std::make_optional(std::string(
			std::istreambuf_iterator<char>(shaderFile),
			std::istreambuf_iterator<char>()));
	}
};
} // namespace graphix
