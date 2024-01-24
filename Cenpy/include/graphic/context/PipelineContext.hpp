// PipelineContext.hpp

#pragma once

#include <memory>
#include <graphic/Api.hpp>
#include <graphic/pipeline/Pass.hpp>

namespace cenpy::graphic::context
{
    namespace pipeline = cenpy::graphic::pipeline;
    template <typename API>
    class PipelineContext
    {
    public:
        virtual ~PipelineContext() = default;

        void addPass(std::shared_ptr<pipeline::IPass<API>> pass)
        {
            m_passes.push_back(pass);
        }

        [[nodiscard]] std::shared_ptr<pipeline::IPass<API>> getPass(const int &index) const
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
        std::vector<std::shared_ptr<pipeline::IPass<API>>> m_passes;
        int m_currentPass = -1;
    };
}