/**
 * @file Pass.hpp
 * @brief Defines the interface and OpenGL implementation for shader passes in a multi-pass rendering system.
 *
 * This file introduces the concept of a 'Pass', representing a sequence of shader operations in a rendering pipeline.
 * It includes the abstract BasePass class template and its OpenGL specialization. The design is flexible to support
 * other graphics APIs such as Vulkan, DirectX, and Metal under respective namespaces.
 * The 'Pass' is an integral part of the multipass shader system.
 *
 * @author Djoé DENNE
 * @date 13/12/2023
 */

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
     * @class BasePass
     * @brief Abstract base class template for a Pass in a rendering pipeline.
     *
     * BasePass defines the general structure and behavior of a Pass, which is a sequence of shader operations.
     * It is designed to be generic and extensible to accommodate various graphics APIs. The class manages a collection
     * of shaders and uniform variables, ensuring compatibility and adaptability for different rendering technologies.
     */
    template <typename S, typename U, template <typename> typename C, typename D>
        requires std::is_base_of_v<BaseUniform, U> && std::is_base_of_v<BaseShader, S>
    class BasePass
    {
    public:
        /**
         * @brief Destructor for BasePass.
         */
        virtual ~BasePass() = default;

        /**
         * @brief Adds a uniform with the specified name and value to the pass.
         *
         * @tparam T The type of the uniform value.
         * @param name The name of the uniform.
         * @param value The value of the uniform.
         * @param number The number of elements in the uniform (default is 1).
         * @return A reference to the BasePass object.
         * @throws std::runtime_error if the uniform is not found.
         */
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

        /**
         * @brief Returns a const reference to the map of uniforms in the pass.
         *
         * @return A const reference to the map of uniforms.
         */
        [[nodiscard]] const std::unordered_map<std::string, std::shared_ptr<BaseUniform>, collection_utils::StringHash, collection_utils::StringEqual> &getUniforms() const
        {
            return m_uniforms;
        }

        /**
         * @brief Returns a const reference to the vector of shaders in the pass.
         *
         * @return A const reference to the vector of shaders.
         */
        [[nodiscard]] const std::vector<S> &getShaders() const
        {
            return m_shaders;
        }

    protected:
        /**
         * @brief Constructor for BasePass.
         *
         * @tparam Shaders The types of shaders in the pass.
         * @param shaders The shared pointers to the shaders.
         */
        template <typename... Shaders>
            requires(std::is_same_v<S, Shaders> && ...)
        BasePass(const std::shared_ptr<Shaders> &...shaders) : m_shaders({shaders...})
        {
        }

        /**
         * @brief Loads the shaders and reads the uniforms.
         *
         * This method loads each shader, attaches the shaders, and reads the uniforms.
         */
        void load()
        {
            for (std::shared_ptr<S> &shader : BasePass<S, U, C, D>::getShaders())
            {
                shader->load();
            }
            attachShaders();
            readUniforms(m_uniforms);
        }

        /**
         * @brief Returns a reference to the vector of shaders in the pass.
         *
         * @return A reference to the vector of shaders.
         */
        [[nodiscard]] std::vector<std::shared_ptr<S>> &getShaders()
        {
            return m_shaders;
        }

        /**
         * @brief Attaches the shaders to the pass.
         *
         * Derived classes must implement this method to attach the shaders to the pass.
         */
        virtual void attachShaders() = 0;

        /**
         * @brief Reads the uniforms from the shaders.
         *
         * Derived classes must implement this method to read the uniforms from the shaders.
         *
         * @param uniforms The map of uniforms to populate.
         */
        virtual void readUniforms(std::unordered_map<std::string, std::shared_ptr<BaseUniform>, collection_utils::StringHash, collection_utils::StringEqual> &uniforms) const = 0;

    private:
        std::unordered_map<std::string, std::shared_ptr<BaseUniform>, collection_utils::StringHash, collection_utils::StringEqual> m_uniforms;
        std::vector<std::shared_ptr<S>> m_shaders;
    };

    namespace opengl
    {
        template <typename S = Shader, typename U = Uniform, template <typename> typename C = setter>
            requires std::is_base_of_v<BaseUniform, U> && std::is_base_of_v<BaseShader, S>
        /**
         * @brief Pass class represents a rendering pass in a graphics pipeline.
         *
         * This class is derived from the BasePass class and provides functionality for attaching shaders,
         * reading uniforms, and creating a program for the pass.
         *
         * @tparam S The shader type.
         * @tparam U The uniform type.
         * @tparam C The UniformSetter type.
         */
        class Pass : public BasePass<S, U, C, Pass<S, U, C>>
        {
        public:
            /**
             * @brief Constructs a Pass object with the specified shaders.
             *
             * @tparam Shaders The shader types.
             * @param shaders The shared pointers to the shaders.
             *
             * @note The shaders must be of the same type as the template parameter S.
             */
            template <typename... Shaders>
                requires(std::is_same_v<S, Shaders> && ...)
            Pass(const std::shared_ptr<Shaders> &...shaders) : BasePass<S, U, C, Pass<S, U, C>>(shaders...)
            {
                BasePass<S, U, C, Pass<S, U, C>>::load();
            }

        protected:
            /**
             * @brief Reads the uniforms for the pass and stores them in the provided map.
             *
             * @param uniforms The map to store the uniforms.
             *
             * @note This function is called internally by the Pass class.
             */
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

            /**
             * @brief Attaches the shaders to the pass and links the program.
             *
             * @note This function is called internally by the Pass class.
             */
            void attachShaders() override
            {
                m_pass = glCreateProgram();
                for (const std::shared_ptr<S> &shader : BasePass<S, U, C, Pass<S, U, C>>::getShaders())
                {
                    glAttachShader(m_pass, shader->getLocation());
                }
                glLinkProgram(m_pass);

                for (std::shared_ptr<S> &shader : BasePass<S, U, C, Pass<S, U, C>>::getShaders())
                {
                    shader->free();
                }
            }

        private:
            GLuint m_pass; ///< The OpenGL program ID for the pass.
        };
    } // namespace opengl
} // namespace cenpy::graphic::shader