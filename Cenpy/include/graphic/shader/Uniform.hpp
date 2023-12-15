/**
 * @file uniform.hpp
 *
 *
 * @author Djoé DENNE
 * @date 13/12/2023
 */

#pragma once

#include <type_traits>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <format>
#include <any>
#include <unordered_map>
#include <glm/glm.hpp>
#include <common/exception/TraceableException.hpp>
#ifdef __mock_gl__
#include <opengl/glFunctionMock.hpp>
#endif

namespace cenpy::graphic::shader
{
    class BaseUniform;

    /**
     * @brief Type trait to check if a type is a valid uniform type
     *
     * Default implementation returns false. Specializations provide
     * support for specific types.
     *
     * @tparam U The type to check for uniform support.
     */
    template <typename T, typename U>
    struct baseSetter
    {
        /**
         * @brief Lambda to set the uniform value based on type
         *
         * Default implementation throws an assertion error. Specializations
         * provide actual implementation for specific types.
         *.
         * @param uniform The uniform to set.
         */
        static const auto set = [](const T &)
        { static_assert(false, "Unsupported uniform type"); };
    };

    /**
     * @class BaseUniform
     * @brief Abstract base class for representing uniform variables in shaders.
     *
     * This class serves as the foundation for handling uniform variables across
     * different graphics APIs such as OpenGL, Vulkan, and DirectX. Derived classes
     * are expected to implement API-specific functionality by inheriting from this class.
     */
    class BaseUniform
    {
    public:
        virtual ~BaseUniform() = default;

        /**
         * @brief Template function to set the value of the uniform variable.
         *
         * @tparam U The type of the value to set.
         * @tparam T The derived class type (Uniform type).
         * @tparam C The setter type providing the implementation for setting the value.
         * @param value The value to set for the uniform variable.
         * @throws common::exception::TraceableException<std::runtime_error> if the type of the value does not match the type of the uniform variable.
         *
         * This function enforces type safety and delegates the setting
         * of the value to the specialized setter provided by the derived class.
         */
        template <typename U, typename T, template <typename> typename C>
            requires C<U>::value
        void set(const U &value)
        {
            if (m_value.has_value() && std::any_cast<U>(&m_value) == nullptr)
            {
                throw common::exception::TraceableException<std::runtime_error>(std::format("ERROR::UNIFORM::SET::TYPE_MISMATCH: The type of the value ({}) does not match the type of the uniform variable ({})", typeid(value).name(), typeid(m_value).name()));
            }
            else
            {
                m_value = value;
            }
            C<U>::set(*dynamic_cast<T *>(this));
        }

        /**
         * @brief Template function to get the value of the uniform variable.
         *
         * @tparam U The type of the value to retrieve.
         * @return A const reference to the stored value of the uniform variable.
         * @throws common::exception::TraceableException<std::runtime_error> if the type of the value does not match the type of the uniform variable.
         *
         * This function enforces type safety and retrieves the value
         * of the uniform variable cast to the specified type.
         */
        template <typename U>
        const U &get() const
        {
            if (std::any_cast<U>(&m_value) == nullptr)
            {
                throw common::exception::TraceableException<std::runtime_error>(std::format("ERROR::UNIFORM::GET::TYPE_MISMATCH: The type of the value ({}) does not match the type of the uniform variable ({})", typeid(U).name(), typeid(m_value).name()));
            }
            else
            {
                return *std::any_cast<U>(&m_value);
            }
        }

    private:
        std::any m_value; ///< The value of the uniform variable.
    };

    namespace opengl
    {
        class Uniform;

        template <typename U>
        struct setter : baseSetter<Uniform, U>
        {
        };

        /**
         * @class Uniform
         * @brief Represents an OpenGL uniform variable.
         *
         * This class is a specialization of the BaseUniform class tailored for OpenGL.
         * It encapsulates the OpenGL-specific details of a uniform, including its
         * location, type, and size.
         */
        class Uniform : public BaseUniform
        {

        public:
            Uniform() noexcept = default;

            /**
             * @brief Constructor for creating a Uniform object with specified parameters.
             *
             * @param location The location of the uniform variable in the shader program.
             * @param type The type of the uniform variable.
             * @param size The size of the uniform variable.
             */
            Uniform(const GLint &location, const GLenum &type, const GLuint &size) noexcept
                : m_location(location), m_type(type), m_size(size)
            {
            }

            /**
             * @brief Gets the location of the uniform variable.
             *
             * @return The location of the uniform variable.
             */
            const GLint &getLocation() const noexcept
            {
                return m_location;
            }

            /**
             * @brief Gets the type of the uniform variable.
             *
             * @return The type of the uniform variable.
             */
            const GLenum &getType() const noexcept
            {
                return m_type;
            }

            /**
             * @brief Template function to set the value of the OpenGL uniform variable.
             *
             * @tparam T The type of the value to set.
             * @param value The value to set for the uniform variable.
             *
             * This function delegates the setting of the value to the BaseUniform class,
             * enforcing type safety and using the appropriate OpenGL setter specialization.
             */
            template <typename T>
            void set(const T &value)
            {
                BaseUniform::set<T, Uniform, setter>(value);
            }

        private:
            GLint m_location; ///< The map of program IDs to uniform locations.
            GLenum m_type;    ///< The type of the uniform variable.
            GLuint m_size;    ///< The size of the uniform variable.
        };

        /**
         * @brief Specialization for GLfloat with corresponding setter
         */
        template <>
        struct setter<float> : std::true_type
        {
            static constexpr auto set =
                [](const Uniform &uniform)
            { glUniform1f(uniform.getLocation(), uniform.get<float>()); };
        };

        /**
         * @brief Specialization for GLdouble with corresponding setter
         */
        template <>
        struct setter<double> : std::true_type
        {
            static constexpr auto set =
                [](const Uniform &uniform)
            { glUniform1d(uniform.getLocation(), uniform.get<double>()); };
        };

        /**
         * @brief Specialization for GLint with corresponding setter
         */
        template <>
        struct setter<int> : std::true_type
        {
            static constexpr auto set =
                [](const Uniform &uniform)
            { glUniform1i(uniform.getLocation(), uniform.get<int>()); };
        };

        /**
         * @brief Specialization for GLuint with corresponding setter
         */
        template <>
        struct setter<unsigned int> : std::true_type
        {
            static constexpr auto set =
                [](const Uniform &uniform)
            { glUniform1ui(uniform.getLocation(), uniform.get<unsigned int>()); };
        };

        /**
         * @brief Specialization for GLshort with corresponding setter
         */
        template <>
        struct setter<short> : std::true_type
        {
            static constexpr auto set =
                [](const Uniform &uniform)
            { glUniform1i(uniform.getLocation(), uniform.get<short>()); };
        };

        /**
         * @brief Specialization for GLushort with corresponding setter
         */
        template <>
        struct setter<unsigned short> : std::true_type
        {
            static constexpr auto set =
                [](const Uniform &uniform)
            { glUniform1i(uniform.getLocation(), uniform.get<unsigned short>()); };
        };

        /**
         * @brief Specialization for GLbyte with corresponding setter
         */
        template <>
        struct setter<char> : std::true_type
        {
            static constexpr auto set =
                [](const Uniform &uniform)
            { glUniform1i(uniform.getLocation(), uniform.get<char>()); };
        };

        /**
         * @brief Specialization for GLubyte with corresponding setter
         */
        template <>
        struct setter<unsigned char> : std::true_type
        {
            static constexpr auto set =
                [](const Uniform &uniform)
            { glUniform1i(uniform.getLocation(), uniform.get<unsigned char>()); };
        };

        /**
         * @brief Specialization for glm::vec2 with corresponding setter
         */
        template <>
        struct setter<glm::vec2> : std::true_type
        {
            static constexpr auto set =
                [](const Uniform &uniform)
            {
                glm::vec2 vec2 = uniform.get<glm::vec2>();
                glUniform2f(uniform.getLocation(), vec2.x, vec2.y);
            };
        };

        /**
         * @brief Specialization for glm::vec3 with corresponding setter
         */
        template <>
        struct setter<glm::vec3> : std::true_type
        {
            static constexpr auto set =
                [](const Uniform &uniform)
            {
                glm::vec3 vec3 = uniform.get<glm::vec3>();
                glUniform3f(uniform.getLocation(), vec3.x, vec3.y, vec3.z);
            };
        };

        /**
         * @brief Specialization for glm::vec4 with corresponding setter
         */
        template <>
        struct setter<glm::vec4> : std::true_type
        {
            static constexpr auto set =
                [](const Uniform &uniform)
            {
                glm::vec4 vec4 = uniform.get<glm::vec4>();
                glUniform4f(uniform.getLocation(), vec4.x, vec4.y, vec4.z, vec4.w);
            };
        };

        /**
         * @brief Specialization for glm::mat2 with corresponding setter
         */
        template <>
        struct setter<glm::mat2> : std::true_type
        {
            static constexpr auto set =
                [](const Uniform &uniform)
            { glUniformMatrix2fv(uniform.getLocation(), 1, GL_FALSE, &uniform.get<glm::mat2>()[0][0]); };
        };

        /**
         * @brief Specialization for glm::mat3 with corresponding setter
         */
        template <>
        struct setter<glm::mat3> : std::true_type
        {
            static constexpr auto set =
                [](const Uniform &uniform)
            { glUniformMatrix3fv(uniform.getLocation(), 1, GL_FALSE, &uniform.get<glm::mat3>()[0][0]); };
        };

        /**
         * @brief Specialization for glm::mat4 with corresponding setter
         */
        template <>
        struct setter<glm::mat4> : std::true_type
        {
            static constexpr auto set =
                [](const Uniform &uniform)
            { glUniformMatrix4fv(uniform.getLocation(), 1, GL_FALSE, &uniform.get<glm::mat4>()[0][0]); };
        };
    }
} // namespace cenpy::graphic::shader
