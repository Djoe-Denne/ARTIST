#pragma once

#include <memory>
#include <graphic/Api.hpp>
#include <graphic/context/ProgramContext.hpp>

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