#pragma once

#include <memory>
#include <graphic/Api.hpp>

namespace cenpy::graphic::shader
{
    namespace shader = cenpy::graphic::shader;
    namespace component::pass
    {
        /**
         * @interface IPassFreer
         * @brief Interface for freeing resources of shader passes.
         *
         * This interface defines a method for freeing resources associated with a shader pass,
         * such as detaching shaders and deleting programs.
         */
        template <typename API>
        class IPassFreer
        {
        public:
            virtual ~IPassFreer() = default;

            /**
             * @brief Free resources and state for a shader pass.
             * @param context PassContext for managing pass-specific details.
             *
             * Implementations of this method should handle the cleanup and resource release
             * for a shader pass.
             */
            virtual void freePass(std::shared_ptr<typename API::PassContext> context) = 0;
        };
    }

    namespace opengl::component::pass
    {
        /**
         * @class OpenGLPassFreer
         * @brief OpenGL implementation of IPassFreer.
         *
         * Handles the freeing of resources for an OpenGL shader pass, including detaching shaders
         * and deleting the OpenGL program.
         */
        class OpenGLPassFreer : public graphic::shader::component::pass::IPassFreer<graphic::api::OpenGL>
        {
        public:
            void freePass(std::shared_ptr<typename graphic::api::OpenGL::PassContext> openglContext) override;
        };
    }
}
