// ProgramContext.hpp

#pragma once

#include <memory>
#include <graphic/Api.hpp>
#include <graphic/shader/Program.hpp>

namespace cenpy::graphic
{
    namespace shader::opengl::component::program
    {
        class OpenGLProgramUser;
        class OpenGLProgramResetter;
    }
    namespace context
    {
        namespace shader = cenpy::graphic::shader;
        template <typename API>
        class ProgramContext
        {
        public:
            virtual ~ProgramContext() = default;

            void addPass(std::shared_ptr<shader::Pass<API>> pass)
            {
                m_passes.push_back(pass);
            }

            [[nodiscard]] std::shared_ptr<shader::Pass<API>> getPass(const int &index) const
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
            std::vector<std::shared_ptr<shader::Pass<API>>> m_passes;
            int m_currentPass = -1;
        };
    }

    namespace opengl::context
    {
        class OpenGLProgramContext : public graphic::context::ProgramContext<graphic::api::OpenGL>
        {
        public:
            using User = shader::opengl::component::program::OpenGLProgramUser;
            using Resetter = shader::opengl::component::program::OpenGLProgramResetter;
        };
    }
}