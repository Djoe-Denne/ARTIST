#pragma once

#include <memory>
#include <graphic/Api.hpp>
#include <graphic/context/ProgramContext.hpp>
#include <common/exception/TraceableException.hpp>

namespace cenpy::graphic::shader
{
    namespace component::program
    {
        template <typename API>
        class IProgramUser
        {
        public:
            virtual ~IProgramUser() = default;

            virtual void useProgram(std::shared_ptr<typename API::ProgramContext> context)
            {
                if (!context)
                {
                    throw common::exception::TraceableException<std::runtime_error>(std::format("ERROR::SHADER::NON_VALID_CONTEXT"));
                }
                context->getPass(context->getCurrentPass())->use();
            }
        };
    }

    namespace opengl::component::program
    {
        class OpenGLProgramUser : public graphic::shader::component::program::IProgramUser<graphic::api::OpenGL>
        {
        };
    }
}