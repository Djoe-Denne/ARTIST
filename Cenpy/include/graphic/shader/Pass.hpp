#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <format>
#include <type_traits>
#include <unordered_map>
#include <memory>
#include <utils.hpp>
#include <common/exception/TraceableException.hpp>
#include <graphic/shader/Shader.hpp>
#include <graphic/shader/Uniform.hpp>

namespace cenpy::graphic::shader
{
    /**
     * @brief Interface for a pass object.
     *
     * A pass being an ordered sequence of shader passes.
     */
    template <typename S, typename U, template <typename> typename C, typename D>
        requires std::is_base_of_v<BaseUniform, U> && std::is_base_of_v<BaseShader, S>
    class BasePass
    {
    public:
        virtual ~BasePass() = default;

        template <typename T>
        D &withUniform(const std::string &name, const T &value, const int &number = 1)
        {
            if (m_uniforms.contains(name))
            {
                m_uniforms[name]->set<T, U, C>(value);
                return *this;
            }
            throw common::exception::TraceableException<std::runtime_error>(std::format("ERROR::SHADER::UNIFORM_NOT_FOUND\nUniform {} not found", name));
        }

    protected:
        template <typename... Shaders>
            requires(std::is_same_v<S, Shaders> && ...)
        BasePass(const Shaders &...shaders) : m_shaders({shaders...})
        {
        }

        void load()
        {
            loadShaders();
            readUniforms(m_uniforms);
        }

        [[nodiscard]] const std::unordered_map<std::string, std::shared_ptr<BaseUniform>, collection_utils::StringHash, collection_utils::StringEqual> &getUniforms() const
        {
            return m_uniforms;
        }

        [[nodiscard]] const std::vector<BaseShader> &getShaders() const
        {
            return m_shaders;
        }

        virtual void loadShaders() = 0;
        virtual void readUniforms(std::unordered_map<std::string, std::shared_ptr<BaseUniform>, collection_utils::StringHash, collection_utils::StringEqual> &uniforms) const = 0;

    private:
        std::unordered_map<std::string, std::shared_ptr<BaseUniform>, collection_utils::StringHash, collection_utils::StringEqual> m_uniforms;
        std::vector<S> m_shaders;
    };

    namespace opengl
    {
        template <typename S = Shader, typename U = Uniform, template <typename> typename C = setter>
            requires std::is_base_of_v<BaseUniform, U> && std::is_base_of_v<BaseShader, S>
        class Pass : public BasePass<S, U, C, Pass<S, U, C>>
        {
        public:
            template <typename... Shaders>
                requires(std::is_same_v<S, Shaders> && ...)
            Pass(const Shaders &...shaders) : BasePass<S, U, C, Pass<S, U, C>>(shaders...)
            {
                BasePass<S, U, C, Pass<S, U, C>>::load();
            }

        protected:
            void readUniforms(std::unordered_map<std::string, std::shared_ptr<BaseUniform>, collection_utils::StringHash, collection_utils::StringEqual> &uniforms) const override
            {
                GLint count;
                // get number of uniforms
                glGetUniformiv(m_pass, GL_ACTIVE_UNIFORMS, &count);

                for (int i = 0; i < count; i++)
                {
                    char name[256];
                    GLsizei length;
                    GLint size;
                    GLenum type;

                    // get uniform information
                    glGetActiveUniform(m_pass, i, sizeof(name), &length, &size, &type, name);
                    name[length] = '\0';
                    GLuint location = glGetUniformLocation(m_pass, name);
                    uniforms[name] = std::make_shared<U>(location, type, size);
                }
            }

            [[nodiscard]] virtual std::shared_ptr<BaseUniform>
            createUniform(const std::string &name, const GLuint &location, const GLenum &type, const GLint &size) const

            {
                return std::make_shared<U>(location, type, size);
            }

            void loadShaders() override
            {
                m_pass = glCreateProgram();
                for (const auto &shader : BasePass<S, U, C, Pass<S, U, C>>::getShaders())
                {
                    glAttachShader(m_pass, shader.getLocation());
                }
                glLinkProgram(m_pass);

                for (const auto &shader : BasePass<S, U, C, Pass<S, U, C>>::getShaders())
                {
                    shader.free();
                }
            }

        private:
            GLuint m_pass;
        };
    } // namespace opengl
} // namespace cenpy::graphic::shader