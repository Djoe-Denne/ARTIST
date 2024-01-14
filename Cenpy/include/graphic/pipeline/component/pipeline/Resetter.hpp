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
        class IPipelineResetter
        {
        public:
            virtual ~IPipelineResetter() = default;

            virtual void resetPipeline(std::shared_ptr<typename API::PipelineContext> context)
            {
                if (!context)
                {
                    throw common::exception::TraceableException<std::runtime_error>(std::format("ERROR::SHADER::NON_VALID_CONTEXT"));
                }
                context->setCurrentPass(-1);
            }
        };
    }

    namespace opengl::component::pipeline
    {
        class OpenGLPipelineResetter : public graphic::pipeline::component::pipeline::IPipelineResetter<graphic::api::OpenGL>
        {
        };
    }
}