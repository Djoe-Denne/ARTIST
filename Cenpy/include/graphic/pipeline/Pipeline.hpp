#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <format>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <type_traits>
#include <unordered_map>
#include <memory>
#include <utils.hpp>
#include <common/exception/TraceableException.hpp>
#include <graphic/pipeline/Pass.hpp>
#include <graphic/pipeline/component/pipeline/User.hpp>
#include <graphic/pipeline/component/pipeline/Resetter.hpp>

namespace cenpy::graphic::pipeline
{
    template <typename API>
    class Pipeline
    {
    public:
        virtual ~Pipeline() = default;

        Pipeline(const std::initializer_list<std::shared_ptr<Pass<API>>> &passes,
                std::shared_ptr<typename API::PipelineContext::User> user,
                std::shared_ptr<typename API::PipelineContext::Resetter> resetter,
                std::shared_ptr<typename API::PipelineContext> context)
            : m_user(user), m_resetter(resetter), m_context(context)
        {
            for (auto &pass : passes)
            {
                m_context->addPass(pass);
            }
        }

        explicit Pipeline(const std::initializer_list<std::shared_ptr<Pass<API>>> &passes) : Pipeline(passes,
                                                                                                    std::make_shared<typename API::PipelineContext::User>(),
                                                                                                    std::make_shared<typename API::PipelineContext::Resetter>(),
                                                                                                    std::make_shared<typename API::PipelineContext>())
        {
        }

        [[nodiscard]] Pass<API> &forPass(const int &pass)
        {
            return *m_context->getPass(pass);
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
            if (m_user)
            {
                m_context->setCurrentPass(pass);
                m_user->usePipeline(m_context);
            }
        }

        /**
         * @brief Resets the pipeline to its initial state. unset pipeline in OpenGL context.
         */
        virtual void reset()
        {
            if (m_resetter)
            {
                m_resetter->resetPipeline(m_context);
            }
        }

        [[nodiscard]] virtual std::shared_ptr<typename API::PipelineContext> getContext() const
        {
            return m_context;
        }

    protected:
        [[nodiscard]] virtual std::shared_ptr<typename API::PipelineContext::User> getUser() const
        {
            return m_user;
        }

        [[nodiscard]] virtual std::shared_ptr<typename API::PipelineContext::Resetter> getResetter() const
        {
            return m_resetter;
        }

    private:
        std::shared_ptr<typename API::PipelineContext::User> m_user;
        std::shared_ptr<typename API::PipelineContext::Resetter> m_resetter;
        std::shared_ptr<typename API::PipelineContext> m_context;
    };

} // namespace cenpy::graphic::pipeline