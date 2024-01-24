#pragma once

#include <vector>
#include <string>
#include <format>
#include <iostream>
#include <unordered_map>
#include <memory>
#include <utils.hpp>
#include <common/exception/TraceableException.hpp>
#include <graphic/pipeline/Pass.hpp>
#include <graphic/context/PipelineContext.hpp>
#include <graphic/validator/ComponentConcept.hpp>

namespace cenpy::graphic::pipeline
{
    template <typename API>
    class IPipeline
    {
    public:
        IPipeline(const std::initializer_list<std::shared_ptr<IPass<API>>> &passes,
                  std::shared_ptr<typename API::PipelineContext> context)
            : m_context(context)
        {
            for (auto &pass : passes)
            {
                m_context->addPass(pass);
            }
        }

        explicit IPipeline(const std::initializer_list<std::shared_ptr<IPass<API>>> &passes) : IPipeline(passes,
                                                                                                         std::make_shared<typename API::PipelineContext>())
        {
        }

        [[nodiscard]] std::shared_ptr<IPass<API>> forPass(const int &pass)
        {
            return m_context->getPass(pass);
        }

        [[nodiscard]] virtual int getPassesCount() const
        {
            return m_context->getPassesCount();
        }

        [[nodiscard]] bool hasNext() const
        {
            return m_context->getCurrentPass() + 1 < getPassesCount();
        }

        virtual bool useNext()
        {
            if (hasNext())
            {
                use(m_context->getCurrentPass() + 1);
                return hasNext();
            }
            reset();
            return false;
        }

        virtual void use(const int &pass)
        {
            m_context->setCurrentPass(pass);
            use(m_context);
        }

        /**
         * @brief Resets the pipeline to its initial state. unset pipeline in OpenGL context.
         */
        virtual void reset()
        {
            reset(m_context);
        }

        [[nodiscard]] virtual std::shared_ptr<typename API::PipelineContext> getContext() const
        {
            return m_context;
        }

    protected:
        virtual void use(std::shared_ptr<typename API::PipelineContext> context) = 0;
        virtual void reset(std::shared_ptr<typename API::PipelineContext> context) = 0;

    private:
        std::shared_ptr<typename API::PipelineContext> m_context;
    };

    template <typename API, auto PROFILE>
        requires(API::Validator::template validatePipeline<API, PROFILE>())
    class Pipeline : public IPipeline<API>
    {
    public:
        using IPipeline<API>::IPipeline;
        using IPipeline<API>::use;
        using IPipeline<API>::reset;

    protected:
        void use(std::shared_ptr<typename API::PipelineContext> context) override
        {
            if constexpr (graphic::validator::HasComponent<typename API::PipelineContext::User<PROFILE>>)
            {
                API::PipelineContext::template User<PROFILE>::on(context);
            }
        }

        void reset(std::shared_ptr<typename API::PipelineContext> context) override
        {
            if constexpr (graphic::validator::HasComponent<typename API::PipelineContext::Resetter<PROFILE>>)
            {
                API::PipelineContext::template Resetter<PROFILE>::on(context);
            }
        }
    };

} // namespace cenpy::graphic::pipeline