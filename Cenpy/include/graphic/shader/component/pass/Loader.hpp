#pragma once

#include <memory>
#include <graphic/Api.hpp>
#include <graphic/shader/component/pass/ShaderAttacher.hpp>

namespace cenpy::graphic::shader
{
    namespace component::pass
    {
        /**
         * @interface IPassLoader
         * @brief Interface for loading shader passes.
         */
        template <typename API>
        class IPassLoader
        {
        public:
            virtual ~IPassLoader() = default;

            /**
             * @brief Load resources and state for a shader pass.
             * @param context PassContext for managing pass-specific details.
             */
            virtual void loadPass(std::shared_ptr<typename API::PassContext> context) = 0;
        };
    }

    namespace opengl::component::pass
    {
        class OpenGLPassLoader : public graphic::shader::component::pass::IPassLoader<graphic::api::OpenGL>
        {
        public:
            OpenGLPassLoader() = default;
            OpenGLPassLoader(const std::shared_ptr<graphic::shader::component::pass::IShaderAttacher<graphic::api::OpenGL>> attacher) : m_attacher(attacher) {}

            void setAttacher(const std::shared_ptr<graphic::shader::component::pass::IShaderAttacher<graphic::api::OpenGL>> attacher) { m_attacher = attacher; }

            void loadPass(std::shared_ptr<typename graphic::api::OpenGL::PassContext> openglContext) override;

            /**
             * @brief Checks for link errors in an OpenGL program.
             * @param programId The ID of the OpenGL program to check.
             * @return True if no linking errors are found, false otherwise.
             */
            bool checkLinkErrors(GLuint programId) const;

        private:
            std::shared_ptr<graphic::shader::component::pass::IShaderAttacher<graphic::api::OpenGL>> m_attacher;
        };
    }

}