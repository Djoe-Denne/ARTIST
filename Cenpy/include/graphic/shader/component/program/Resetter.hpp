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
        class IProgramResetter
        {
        public:
            virtual ~IProgramResetter() = default;

            virtual void resetProgram(std::shared_ptr<typename API::ProgramContext> context)
            {
                if (!context)
                {
                    throw common::exception::TraceableException<std::runtime_error>(std::format("ERROR::SHADER::NON_VALID_CONTEXT"));
                }
                context->setCurrentPass(-1);
            }
        };
    }

    namespace opengl::component::program
    {
        class OpenGLProgramResetter : public graphic::shader::component::program::IProgramResetter<graphic::api::OpenGL>
        {
        };
    }
}