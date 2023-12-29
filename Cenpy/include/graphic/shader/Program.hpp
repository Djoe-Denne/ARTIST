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

namespace cenpy::graphic::shader
{

    template <typename P, typename S, typename U, template <typename> typename C, typename D>
        requires std::is_base_of_v<BaseUniform, U> && std::is_base_of_v<BasePass<S, U, C, P>, P> && std::is_base_of_v<BaseShader, S>
    class BaseProgram
    {
    public:
        virtual ~BaseProgram() = default;

        template <typename T>
        [[nodiscard]] P &forPass(const int &pass)
        {
            return *m_passes[pass];
        }

        [[nodiscard]] virtual int getPassesCount() const
        {
            return m_passes.size();
        }

        virtual void use(const int &pass)
        {
            m_passes[pass]->use();
            m_currentPass = pass;
        }

        [[nodiscard]] bool hasNext() const
        {
            return m_currentPass < getPassesCount() - 1;
        }

        virtual bool useNext()
        {
            if (hasNext())
            {
                use(++m_currentPass);
                return hasNext();
            }
            reset();
            return false;
        }

        /**
         * @brief Resets the program to its initial state. unset program in OpenGL context.
         */
        virtual void reset()
        {
            m_currentPass = -1;
        }

    protected:
        BaseProgram(const std::initializer_list<std::shared_ptr<P>> &passes) : m_passes(passes)
        {
        }

    private:
        std::vector<std::shared_ptr<P>> m_passes;
        int m_currentPass = -1;
    };

    namespace opengl
    {
        template <typename S = Shader, typename U = Uniform, template <typename> typename C = setter, typename P = Pass<S, U, C>>
            requires std::is_base_of_v<BaseUniform, U> && std::is_base_of_v<BasePass<S, U, C, P>, P> && std::is_base_of_v<BaseShader, S>
        class Program : public BaseProgram<P, S, U, C, Program<S, U, C, P>>
        {
        public:
            Program(const std::initializer_list<std::shared_ptr<P>> &passes) : BaseProgram<P, S, U, C, Program<S, U, C, P>>(passes)
            {
            }
        };
    } // namespace opengl
} // namespace cenpy::graphic::shader