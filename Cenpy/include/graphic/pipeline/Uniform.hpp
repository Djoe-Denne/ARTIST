/**
 * @file uniform.hpp
 * @brief Defines classes and templates for managing shader uniform variables across various graphics APIs.
 *
 * The uniform management system is designed to be flexible and extensible to support multiple graphics APIs
 * such as OpenGL, Vulkan, DirectX, and Metal. This file contains the Uniform class, which serves as an
 * abstract foundation, and various template specializations and type traits for handling different uniform types.
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
#include <graphic/context/UniformContext.hpp>
#include <graphic/validator/ComponentConcept.hpp>
#include <common/exception/TraceableException.hpp>

#include <graphic/opengl/pipeline/component/uniform/Setter.hpp>
#include <graphic/opengl/validator/Validator.hpp>

namespace cenpy::graphic::pipeline
{
    /**
     * @class Uniform
     * @brief Abstract base class for representing uniform variables in shaders.
     *
     * This class provides a foundational interface for handling uniform variables.
     * It is designed to be extended by specific implementations for different graphics APIs
     * such as OpenGL, Vulkan, DirectX, and Metal. The class includes template methods for
     * setting and getting uniform values with type safety, enforced through specialized setters.
     */
    template <typename API>
        requires(API::Validator::template validateUniform<API>())
    class Uniform
    {
    public:
        explicit Uniform(std::shared_ptr<typename API::UniformContext> context) : m_context(context) {}

        Uniform() : Uniform(std::make_shared<typename API::UniformContext>())
        {
        }

        /**
         * @brief Sets the value of the uniform variable.
         *
         * This method is used to set the value of the uniform variable. It is implemented
         * by the API-specific Uniform class, which provides the necessary context for
         * setting the value.
         *
         * @param value The value to set the uniform variable to.
         */
        template <typename T>
        void set(const T &value)
        {
            if constexpr (graphic::validator::HasComponent<typename API::UniformContext::template Setter<T>>)
            {
                m_context->template setValue<T>(value);
                API::UniformContext::template Setter<T>::on(m_context);
            }
            else
            {
                throw common::exception::TraceableException<std::runtime_error>("ERROR::UNIFORM::UNSUPPORTED_TYPE");
            }
        }

        /**
         * @brief Gets the value of the uniform variable.
         *
         * This method is used to get the value of the uniform variable. It is implemented
         * by the API-specific Uniform class, which provides the necessary context for
         * getting the value.
         *
         * @return The value of the uniform variable.
         */
        template <typename T>
        const T &get() const
        {
            return m_context->template getValue<T>();
        }

        std::shared_ptr<typename API::UniformContext> getContext() const
        {
            return m_context;
        }

    private:
        std::shared_ptr<typename API::UniformContext> m_context; // API-specific shader context
    };

} // namespace cenpy::graphic::pipeline
