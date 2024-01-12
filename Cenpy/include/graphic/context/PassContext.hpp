// PassContext.hpp

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <unordered_map>
#include <memory>
#include <utils.hpp>
#include <graphic/Api.hpp>
#include <graphic/shader/Shader.hpp>
#include <graphic/shader/Uniform.hpp>

namespace cenpy::graphic
{
    namespace shader::opengl::component::pass
    {
        class OpenGLLoader;
        class OpenGLPassFreer;
        class OpenGLShaderAttacher;
        class OpenGLPassUniformReader;
        class OpenGLPassUser;
    }
    namespace context
    {
        namespace shader = cenpy::graphic::shader;
        /**
         * @class PassContext
         * @brief Abstract base class for pass context.
         *
         * The PassContext class provides an interface for managing the details and state of a shader pass.
         * This includes a collection of shaders and uniform variables. It serves as a base for API-specific
         * implementations tailored to different graphics APIs.
         */
        template <typename API>
        class PassContext
        {
        public:
            virtual ~PassContext() = default;

            /**
             * @brief Add a shader to the pass.
             * @param shader Shader to add.
             */
            void addShader(std::shared_ptr<shader::Shader<API>> shader)
            {
                m_shaders.push_back(shader);
            }

            /*
             * @brief Add uniform to the pass.
             *
             * @param name Name of the uniform to add.
             * @param uniform Uniform to add.
             */
            void addUniform(const std::string &name, std::shared_ptr<shader::Uniform<API>> uniform)
            {
                m_uniforms[name] = uniform;
            }

            /**
             * @brief Get the shader at the given index.
             * @param index Index of the shader to get.
             * @return Shader at the given index.
             */
            [[nodiscard]] std::shared_ptr<shader::Shader<API>> getShader(const int &index) const
            {
                return m_shaders[index];
            }

            /**
             * @brief Get the uniform with the given name.
             * @param name Name of the uniform to get.
             * @return Uniform with the given name.
             */
            [[nodiscard]] std::shared_ptr<shader::Uniform<API>> getUniform(const std::string &name) const
            {
                if (m_uniforms.contains(name))
                {
                    return m_uniforms.at(name);
                }
                return nullptr;
            }

            /**
             * @brief Get the number of shaders in the pass.
             * @return Number of shaders in the pass.
             */
            [[nodiscard]] int getShadersCount() const
            {
                return m_shaders.size();
            }

            /**
             * @brief Get the shaders in the pass.
             * @return Shaders in the pass.
             */
            [[nodiscard]] const std::vector<std::shared_ptr<shader::Shader<API>>> &getShaders() const
            {
                return m_shaders;
            }

            /**
             * @brief Get the uniforms in the pass.
             * @return Uniforms in the pass.
             */
            [[nodiscard]] const std::unordered_map<std::string, std::shared_ptr<shader::Uniform<API>>, collection_utils::StringHash, collection_utils::StringEqual> &getUniforms() const
            {
                return m_uniforms;
            }

        private:
            std::vector<std::shared_ptr<shader::Shader<API>>> m_shaders;
            std::unordered_map<std::string, std::shared_ptr<shader::Uniform<API>>, collection_utils::StringHash, collection_utils::StringEqual> m_uniforms;
        };
    }

    namespace opengl::context
    {
        /**
         * @class OpenGLPassContext
         * @brief OpenGL-specific implementation of PassContext.
         *
         * OpenGLPassContext manages the details and state of a shader pass for OpenGL.
         * This includes handling of OpenGL-specific data such as program IDs, as well
         * as the list of shaders and uniform variables.
         */
        class OpenGLPassContext : public graphic::context::PassContext<graphic::api::OpenGL>
        {
        public:
            using Loader = shader::opengl::component::pass::OpenGLLoader;
            using Freer = shader::opengl::component::pass::OpenGLPassFreer;
            using ShaderAttacher = shader::opengl::component::pass::OpenGLShaderAttacher;
            using UniformReader = shader::opengl::component::pass::OpenGLPassUniformReader;
            using User = shader::opengl::component::pass::OpenGLPassUser;

            OpenGLPassContext() : m_programId(0) {}

            void setProgramId(GLuint programId)
            {
                m_programId = programId;
            }

            GLuint getProgramId() const
            {
                return m_programId;
            }

            // Implement methods for managing shaders and uniforms
            // ...

        private:
            GLuint m_programId; // OpenGL program ID
        };
    }
}