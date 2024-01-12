/**
 * @file Pass.hpp
 * @brief Defines the interface and OpenGL implementation for shader passes in a multi-pass rendering system.
 *
 * This file introduces the concept of a 'Pass', representing a sequence of shader operations in a rendering pipeline.
 * It includes the abstract Pass class template and its OpenGL specialization. The design is flexible to support
 * other graphics APIs such as Vulkan, DirectX, and Metal under respective namespaces.
 * The 'Pass' is an integral part of the multipass shader system.
 *
 * @author Djoé DENNE
 * @date 13/12/2023
 */

#pragma once

#include <GL/glew.h>
#include <vector>
#include <string>
#include <format>
#include <type_traits>
#include <unordered_map>
#include <memory>
#include <utils.hpp>
#include <common/exception/TraceableException.hpp>
#include <graphic/shader/Shader.hpp>
#include <graphic/shader/Uniform.hpp>
#include <graphic/shader/component/pass/Loader.hpp>
#include <graphic/shader/component/pass/Freer.hpp>
#include <graphic/shader/component/pass/ShaderAttacher.hpp>
#include <graphic/shader/component/pass/UniformReader.hpp>
#include <graphic/shader/component/pass/User.hpp>
#include <graphic/Api.hpp>

namespace cenpy::graphic::shader
{
    template <typename API>
    class Pass
    {
    public:
        // ... Existing constructors, destructors, methods ...
        virtual ~Pass()
        {
            free();
        }

        // New or modified methods

        // Constructor accepting components
        Pass(const std::initializer_list<std::shared_ptr<Shader<API>>> &shaders,
             std::shared_ptr<typename API::PassContext::Loader> loader,
             std::shared_ptr<typename API::PassContext::Freer> freer,
             std::shared_ptr<typename API::PassContext::ShaderAttacher> attacher,
             std::shared_ptr<typename API::PassContext::UniformReader> uniformReader,
             std::shared_ptr<typename API::PassContext::User> user,
             std::shared_ptr<typename API::PassContext> context) : m_loader(loader),
                                                                   m_freer(freer),
                                                                   m_attacher(attacher),
                                                                   m_uniformReader(uniformReader),
                                                                   m_user(user),
                                                                   m_context(context)
        {
            for (auto &shader : shaders)
            {
                m_context->addShader(shader);
            }
        }

        Pass(const std::initializer_list<std::shared_ptr<Shader<API>>> shaders)
            : Pass(shaders,
                   std::make_shared<typename API::PassContext::Loader>(),
                   std::make_shared<typename API::PassContext::Freer>(),
                   std::make_shared<typename API::PassContext::ShaderAttacher>(),
                   std::make_shared<typename API::PassContext::UniformReader>(),
                   std::make_shared<typename API::PassContext::User>(),
                   std::make_shared<typename API::PassContext>())
        {
            m_loader->setAttacher(m_attacher);
        }

        virtual void load()
        {
            for (auto &shader : m_context->getShaders())
            {
                shader->load();
            }
            if (m_loader)
            {
                m_loader->loadPass(m_context);
            }
            if (m_uniformReader)
            {
                m_uniformReader->readUniforms(m_context);
            }
        }

        virtual void use()
        {
            if (m_user)
            {
                m_user->usePass(m_context);
            }
        }

        virtual void free()
        {
            if (m_freer)
            {
                m_freer->freePass(m_context);
            }
        }

        /**
         * @brief Adds a uniform with the specified name and value to the pass.
         *
         * @tparam T The type of the uniform value.
         * @param name The name of the uniform.
         * @param value The value of the uniform.
         * @return A reference to the Pass object.
         * @throws std::runtime_error if the uniform is not found.
         */
        template <typename T>
        Pass<API> &withUniform(const std::string &name, const T &value)
        {
            if (auto uniform = m_context->getUniform(name))
            {
                uniform->template set<T>(value);
                return *this;
            }
            throw common::exception::TraceableException<std::runtime_error>(std::format("ERROR::SHADER::UNIFORM_NOT_FOUND\nUniform {} not found", name));
        }

        /**
         * @brief Returns a const reference to the map of uniforms in the pass.
         *
         * @return A const reference to the map of uniforms.
         */
        [[nodiscard]] virtual const std::unordered_map<std::string, std::shared_ptr<Uniform<API>>, collection_utils::StringHash, collection_utils::StringEqual> &getUniforms() const
        {
            return m_context->getUniforms();
        }

        /**
         * @brief Returns a const reference to the vector of shaders in the pass.
         *
         * @return A const reference to the vector of shaders.
         */
        [[nodiscard]] virtual const std::vector<std::shared_ptr<Shader<API>>> &getShaders() const
        {
            return m_context->getShaders();
        }

        /**
         * @brief Returns the pass context.
         * @return The pass context.
         */
        [[nodiscard]] virtual std::shared_ptr<typename API::PassContext> getContext() const
        {
            return m_context;
        }

    protected:
        // Component instances
        std::shared_ptr<typename API::PassContext::Loader> m_loader;               ///< The loader for the pass context.
        std::shared_ptr<typename API::PassContext::Freer> m_freer;                 ///< The freer for the pass context.
        std::shared_ptr<typename API::PassContext::ShaderAttacher> m_attacher;     ///< The shader attacher for the pass context.
        std::shared_ptr<typename API::PassContext::UniformReader> m_uniformReader; ///< The uniform reader for the pass context.
        std::shared_ptr<typename API::PassContext::User> m_user;                   ///< The user for the pass context.
        std::shared_ptr<typename API::PassContext> m_context;                      ///< The pass context.

        [[nodiscard]] virtual std::shared_ptr<typename API::PassContext::Loader> getLoader() const
        {
            return m_loader;
        }

        [[nodiscard]] virtual std::shared_ptr<typename API::PassContext::Freer> getFreer() const
        {
            return m_freer;
        }

        [[nodiscard]] virtual std::shared_ptr<typename API::PassContext::ShaderAttacher> getAttacher() const
        {
            return m_attacher;
        }

        [[nodiscard]] virtual std::shared_ptr<typename API::PassContext::UniformReader> getUniformReader() const
        {
            return m_uniformReader;
        }

        [[nodiscard]] virtual std::shared_ptr<typename API::PassContext::User> getUser() const
        {
            return m_user;
        }
    };
} // namespace cenpy::graphic::shader