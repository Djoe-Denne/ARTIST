// file: Freer.hpp

#pragma once

#include <string>
#include <memory>
#include <graphic/Api.hpp>
#include <graphic/context/ShaderContext.hpp>

namespace cenpy::graphic::pipeline::component::shader
{

    /**
     * @interface IShaderFreer
     * @brief Interface for shader freeing operations.
     *
     * IShaderFreer defines an interface for freeing shaders. It allows for the
     * implementation of API-specific mechanisms to release shader resources.
     */
    template <typename API>
    class IShaderFreer
    {
    public:
        virtual ~IShaderFreer() = default;

        /**
         * @brief Free the resources associated with the shader in the given context.
         * @param context ShaderContext for managing shader-specific details.
         */
        virtual void freeShader(std::shared_ptr<typename API::ShaderContext> context) = 0;
    };
}

namespace cenpy::graphic::pipeline::opengl::component::shader
{
    /**
     * @class OpenGLShaderFreer
     * @brief OpenGL implementation of IShaderFreer.
     *
     * OpenGLShaderFreer is responsible for freeing or deleting shaders in an OpenGL context.
     * It ensures that OpenGL shader objects are properly deleted and resources are released.
     */
    class OpenGLShaderFreer : public graphic::pipeline::component::shader::IShaderFreer<graphic::api::OpenGL>
    {
    public:
        void freeShader(std::shared_ptr<typename graphic::api::OpenGL::ShaderContext> openglContext) override
        {
            GLuint shaderID = openglContext->getShaderID();

            if (shaderID != 0)
            {
                glDeleteShader(shaderID);
                openglContext->setShaderID(0); // Reset the shader ID in the context
            }
        }
    };
}
