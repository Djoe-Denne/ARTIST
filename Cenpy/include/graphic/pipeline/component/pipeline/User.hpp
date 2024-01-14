#pragma once

#include <memory>
#include <graphic/Api.hpp>
#include <graphic/context/PipelineContext.hpp>
#include <common/exception/TraceableException.hpp>

namespace cenpy::graphic::pipeline
{
    namespace component::pipeline
    {
        template <typename API>
        class IPipelineUser
        {
        public:
            virtual ~IPipelineUser() = default;

            virtual void usePipeline(std::shared_ptr<typename API::PipelineContext> context)
            {
                if (!context)
                {
                    throw common::exception::TraceableException<std::runtime_error>(std::format("ERROR::SHADER::NON_VALID_CONTEXT"));
                }
                context->getPass(context->getCurrentPass())->use();
            }
        };
    }

    namespace opengl::component::pipeline
    {
        class OpenGLPipelineUser : public graphic::pipeline::component::pipeline::IPipelineUser<graphic::api::OpenGL>
        {
        };
    }
}