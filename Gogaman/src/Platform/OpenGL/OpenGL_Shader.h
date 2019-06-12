#pragma once

#include "Gogaman/Graphics/Shader.h"

#include <glad.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

namespace Gogaman
{
	class OpenGL_Shader : public Shader
	{
	public:
		OpenGL_Shader();
		~OpenGL_Shader();

		virtual void Compile(const std::string &vertexShaderSource, const std::string &fragmentShaderSource, const std::string &geometryShaderSource = "") override;
		virtual void Compile(const std::string &computerShaderSource) override;

		inline virtual void Bind() const override { glUseProgram(m_ID); }

		inline void SetUniformBool(const  std::string &name, const bool value) const { glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value); }
		inline void SetUniformInt(const   std::string &name, const int value) const { glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value); }
		inline void SetUniformFloat(const std::string &name, const float value) const { glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value); }
		inline void SetUniformVec2(const  std::string &name, const glm::vec2 &value) const { glUniform2fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]); }
		inline void SetUniformVec2(const  std::string &name, const float x, const float y) const { glUniform2f(glGetUniformLocation(m_ID, name.c_str()), x, y); }
		inline void SetUniformVec3(const  std::string &name, const glm::vec3 &value) const { glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]); }
		inline void SetUniformVec3(const  std::string &name, const float x, const float y, const float z) const { glUniform3f(glGetUniformLocation(m_ID, name.c_str()), x, y, z); }
		inline void SetUniformVec4(const  std::string &name, const glm::vec4 &value) const { glUniform4fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]); }
		inline void SetUniformVec4(const  std::string &name, const float x, const float y, const float z, const float w) const { glUniform4f(glGetUniformLocation(m_ID, name.c_str()), x, y, z, w); }
		inline void SetUniformMat2(const  std::string &name, const glm::mat2 &Matrix) const { glUniformMatrix2fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &Matrix[0][0]); }
		inline void SetUniformMat3(const  std::string &name, const glm::mat3 &Matrix) const { glUniformMatrix3fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &Matrix[0][0]); }
		inline void SetUniformMat4(const  std::string &name, const glm::mat4 &Matrix) const { glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &Matrix[0][0]); }
	private:
		void CheckCompileErrors(const GLuint object, const std::string &type);
	};
}