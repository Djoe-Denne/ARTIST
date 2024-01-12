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
#include <graphic/shader/Pass.hpp>
#include <graphic/shader/component/program/User.hpp>
#include <graphic/shader/component/program/Resetter.hpp>

namespace cenpy::graphic::shader
{
    template <typename API>
    class Program
    {
    public:
        virtual ~Program() = default;

        Program(const std::initializer_list<std::shared_ptr<Pass<API>>> &passes,
                std::shared_ptr<typename API::ProgramContext::User> user,
                std::shared_ptr<typename API::ProgramContext::Resetter> resetter,
                std::shared_ptr<typename API::ProgramContext> context)
            : m_user(user), m_resetter(resetter), m_context(context)
        {
            for (auto &pass : passes)
            {
                m_context->addPass(pass);
            }
        }

        explicit Program(const std::initializer_list<std::shared_ptr<Pass<API>>> &passes) : Program(passes,
                                                                                                    std::make_shared<typename API::ProgramContext::User>(),
                                                                                                    std::make_shared<typename API::ProgramContext::Resetter>(),
                                                                                                    std::make_shared<typename API::ProgramContext>())
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
                m_user->useProgram(m_context);
            }
        }

        /**
         * @brief Resets the program to its initial state. unset program in OpenGL context.
         */
        virtual void reset()
        {
            if (m_resetter)
            {
                m_resetter->resetProgram(m_context);
            }
        }

        [[nodiscard]] virtual std::shared_ptr<typename API::ProgramContext> getContext() const
        {
            return m_context;
        }

    protected:
        [[nodiscard]] virtual std::shared_ptr<typename API::ProgramContext::User> getUser() const
        {
            return m_user;
        }

        [[nodiscard]] virtual std::shared_ptr<typename API::ProgramContext::Resetter> getResetter() const
        {
            return m_resetter;
        }

    private:
        std::shared_ptr<typename API::ProgramContext::User> m_user;
        std::shared_ptr<typename API::ProgramContext::Resetter> m_resetter;
        std::shared_ptr<typename API::ProgramContext> m_context;
    };

} // namespace cenpy::graphic::shader