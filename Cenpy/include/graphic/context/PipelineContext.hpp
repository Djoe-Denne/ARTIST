// PipelineContext.hpp

#pragma once

#include <memory>
#include <graphic/Api.hpp>
#include <graphic/pipeline/Pipeline.hpp>

namespace cenpy::graphic
{
    namespace pipeline::opengl::component::pipeline
    {
        class OpenGLPipelineUser;
        class OpenGLPipelineResetter;
    }
    namespace context
    {
        namespace pipeline = cenpy::graphic::pipeline;
        template <typename API>
        class PipelineContext
        {
        public:
            virtual ~PipelineContext() = default;

            void addPass(std::shared_ptr<pipeline::Pass<API>> pass)
            {
                m_passes.push_back(pass);
            }

            [[nodiscard]] std::shared_ptr<pipeline::Pass<API>> getPass(const int &index) const
            {
                return m_passes[index];
            }

            [[nodiscard]] int getPassesCount() const
            {
                return m_passes.size();
            }

            void setCurrentPass(const int &pass)
            {
                m_currentPass = pass;
            }

            [[nodiscard]] int getCurrentPass() const
            {
                return m_currentPass;
            }

        private:
            std::vector<std::shared_ptr<pipeline::Pass<API>>> m_passes;
            int m_currentPass = -1;
        };
    }

    namespace opengl::context
    {
        class OpenGLPipelineContext : public graphic::context::PipelineContext<graphic::api::OpenGL>
        {
        public:
            using User = pipeline::opengl::component::pipeline::OpenGLPipelineUser;
            using Resetter = pipeline::opengl::component::pipeline::OpenGLPipelineResetter;
        };
    }
}