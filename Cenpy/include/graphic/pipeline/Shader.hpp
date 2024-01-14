/**
 * @file Shader.hpp
 * @brief Defines the shader interface and OpenGL implementation for shader objects.
 *
 * This file contains the abstract definition of a shader object and its OpenGL-specific implementation.
 * The shader system is designed to be adaptable for multiple graphics APIs, including Vulkan, DirectX, and Metal.
 * The current implementation under the 'cenpy::graphic::pipeline::opengl' namespace is tailored for OpenGL.
 *
 * @author Djoé DENNE
 * @date 13/12/2023
 */

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <string>
#include <format>
#include <fstream>
#include <common/exception/TraceableException.hpp>
#include <graphic/context/ShaderContext.hpp>
#include <graphic/pipeline/component/shader/Loader.hpp>
#include <graphic/pipeline/component/shader/Freer.hpp>
#include <graphic/pipeline/component/shader/Reader.hpp>

namespace cenpy::graphic::pipeline
{
    /**
     * @class Shader
     * @brief Represents the base class for a shader, managing its lifecycle using composition.
     *
     * The Shader class abstracts the shader object, managing its loading, operation, and cleanup.
     * It delegates shader-specific operations to specialized components and maintains its own ShaderContext,
     * which encapsulates all necessary state and API-specific details.
     *
     *
     * @tparam API The graphics API context type to be used. This API class must define
     *             ShaderContext, Loader, and Freer types within its scope. These types
     *             correspond to the specific implementations for the chosen graphics API.
     *             For example, if using OpenGL, the API class should define the respective
     *             OpenGL context, loader, and freer.
     *
     * Design Considerations:
     * - Composition over Inheritance: The class uses separate components for loading and freeing shader resources.
     * - Encapsulation: It encapsulates shader operations and context, providing a clear and unified interface.
     * - Resource Management: Utilizes smart pointers for automatic resource management and safer code.
     */
    template <typename API>
    class Shader
    {
    public:
        /**
         * @brief Destructor for Shader.
         */

        virtual ~Shader()
        {
            free();
        }

        /**
         * @brief Constructor for Shader.
         * @param shaderPath Path to the shader source file.
         * @param shaderType Type of the shader (e.g., vertex, fragment).
         * @param loader Unique pointer to the shader loader component.
         * @param freer Unique pointer to the shader freer component.
         * @param context Unique pointer to the ShaderContext, managing API-specific shader details.
         */
        Shader(const std::string &shaderPath, context::ShaderType shaderType,
               std::shared_ptr<typename API::ShaderContext::Loader> loader,
               std::shared_ptr<typename API::ShaderContext::Freer> freer,
               std::shared_ptr<typename API::ShaderContext::Reader> reader,
               std::shared_ptr<typename API::ShaderContext> context) : m_loader(loader),
                                                                       m_freer(freer),
                                                                       m_reader(reader),
                                                                       m_context(context)
        {
            m_context->setShaderType(shaderType);
            m_context->setShaderPath(shaderPath);
            // Implementation to read shader code from file can be added here
        }

        /**
         * @brief Templated constructor for creating a shader with an API-specific context.
         *
         * This constructor template allows for the automatic creation and setup of an API-specific
         * shader context, loader, and freer. It's designed to simplify the instantiation process
         * by inferring the required components based on the provided API template parameter.
         *
         * @param shaderPath Path to the shader source file. This path is used to read the shader
         *                   code from the file system.
         * @param shaderType The type of the shader (e.g., vertex, fragment). This information is
         *                   used by the shader context and loader for appropriate handling.
         *
         * Example Usage:
         *   Shader<OpenGL> myShader("vertex_shader.glsl", ShaderType::VERTEX);
         * This line creates a shader object for OpenGL, automatically setting up the OpenGL
         * shader context, loader, and freer.
         */
        Shader(const std::string &shaderPath, context::ShaderType shaderType)
            : Shader(shaderPath, shaderType,
                     std::make_shared<typename API::ShaderContext::Loader>(),
                     std::make_shared<typename API::ShaderContext::Freer>(),
                     std::make_shared<typename API::ShaderContext::Reader>(),
                     std::make_shared<typename API::ShaderContext>())
        {
        }

        /**
         * @brief Get the path of the shader file.
         * @return The path of the shader file.
         */
        [[nodiscard]] const std::string &getShaderPath() const
        {
            return m_context->getShaderPath();
        }

        /**
         * @brief Get the type of the shader.
         * @return The type of the shader.
         */
        [[nodiscard]] context::ShaderType getShaderType() const
        {
            return m_context->getShaderType();
        }

        /**
         * @brief Get the code of the shader.
         * @return The code of the shader.
         */
        [[nodiscard]] const std::string &getShaderCode() const
        {
            return m_context->getShaderCode();
        }

        /**
         * @brief Get the shader Context.
         * @return The shader Context.
         */
        [[nodiscard]] virtual const std::shared_ptr<typename API::ShaderContext> &getContext() const
        {
            return m_context;
        }

        /**
         * @brief Loads the shader into the rendering system.
         */
        virtual void load()
        {
            if (m_context && m_loader)
            {
                if (m_context->getShaderCode().empty())
                {
                    m_reader->readShader(m_context);
                }
                m_loader->loadShader(m_context);
            }
        }

        /**
         * @brief Frees the shader resources.
         */
        virtual void free()
        {
            if (m_context)
            {
                m_freer->freeShader(m_context);
            }
        }

    protected:
        /**
         * @brief Get the loader object for the shader.
         *
         * @return std::shared_ptr<typename API::ShaderContext::Loader> The loader object.
         */
        [[nodiscard]] virtual std::shared_ptr<typename API::ShaderContext::Loader> getLoader() const
        {
            return m_loader;
        }

        /**
         * @brief Get the freer object for the shader.
         *
         * @return std::shared_ptr<typename API::ShaderContext::Freer> The freer object.
         */
        [[nodiscard]] virtual std::shared_ptr<typename API::ShaderContext::Freer> getFreer() const
        {
            return m_freer;
        }

        /**
         * @brief Get the reader object for the shader.
         *
         * @return std::shared_ptr<typename API::ShaderContext::Reader> The reader object.
         */
        [[nodiscard]] virtual std::shared_ptr<typename API::ShaderContext::Reader> getReader() const
        {
            return m_reader;
        }

    private:
        std::shared_ptr<typename API::ShaderContext::Loader> m_loader; // Component responsible for loading the shader
        std::shared_ptr<typename API::ShaderContext::Freer> m_freer;   // Component responsible for freeing the shader
        std::shared_ptr<typename API::ShaderContext::Reader> m_reader; // Component responsible for reading the shader
        std::shared_ptr<typename API::ShaderContext> m_context;        // API-specific shader context
    };
} // namespace cenpy::graphic::pipeline