// PassContext.hpp

#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include <utils.hpp>
#include <graphic/Api.hpp>
#include <graphic/pipeline/Shader.hpp>
#include <graphic/pipeline/Uniform.hpp>
#include <graphic/pipeline/Attribute.hpp>

namespace cenpy::graphic::context
{
    namespace pipeline = cenpy::graphic::pipeline;
    /**
     * @class PassContext
     * @brief Abstract base class for pass context.
     *
     * The PassContext class provides an interface for managing the details and state of a shader pass.
     * This includes a collection of shaders and uniform variables. It serves as a base for API-specific
     * implementations tailored to different graphics APIs.
     */
    template <typename API>
    class PassContext
    {
    public:
        virtual ~PassContext() = default;

        /**
         * @brief Add a shader to the pass.
         * @param shader Shader to add.
         */
        void addShader(std::shared_ptr<pipeline::IShader<API>> shader)
        {
            m_shaders.push_back(shader);
        }

        /*
         * @brief Add uniform to the pass.
         *
         * @param name Name of the uniform to add.
         * @param uniform Uniform to add.
         */
        void addUniform(const std::string &name, std::shared_ptr<pipeline::Uniform<API>> uniform)
        {
            m_uniforms[name] = uniform;
        }

        /**
         * @brief Add attribute to the pass.
         *
         * @param name Name of the attribute to add.
         * @param attribute Attribute to add.
         */
        void addAttribute(const std::string &name, std::shared_ptr<pipeline::IAttribute<API>> attribute)
        {
            m_attributes[name] = attribute;
        }

        /**
         * @brief Get the shader at the given index.
         * @param index Index of the shader to get.
         * @return Shader at the given index.
         */
        [[nodiscard]] std::shared_ptr<pipeline::IShader<API>> getShader(const int &index) const
        {
            return m_shaders[index];
        }

        /**
         * @brief Get the uniform with the given name.
         * @param name Name of the uniform to get.
         * @return Uniform with the given name.
         */
        [[nodiscard]] std::shared_ptr<pipeline::Uniform<API>> getUniform(const std::string &name) const
        {
            if (m_uniforms.contains(name))
            {
                return m_uniforms.at(name);
            }
            return nullptr;
        }

        /**
         * @brief Get the attribute with the given name.
         * @param name Name of the attribute to get.
         * @return Attribute with the given name.
         */
        [[nodiscard]] std::shared_ptr<pipeline::IAttribute<API>> getAttribute(const std::string &name) const
        {
            if (m_attributes.contains(name))
            {
                return m_attributes.at(name);
            }
            return nullptr;
        }

        /**
         * @brief Get the number of shaders in the pass.
         * @return Number of shaders in the pass.
         */
        [[nodiscard]] int getShadersCount() const
        {
            return m_shaders.size();
        }

        /**
         * @brief Get the shaders in the pass.
         * @return Shaders in the pass.
         */
        [[nodiscard]] const std::vector<std::shared_ptr<pipeline::IShader<API>>> &getShaders() const
        {
            return m_shaders;
        }

        /**
         * @brief Get the uniforms in the pass.
         * @return Uniforms in the pass.
         */
        [[nodiscard]] const std::unordered_map<std::string, std::shared_ptr<pipeline::Uniform<API>>, collection_utils::StringHash, collection_utils::StringEqual> &getUniforms() const
        {
            return m_uniforms;
        }

        /**
         * @brief Get the attributes in the pass.
         * @return Attributes in the pass.
         */
        [[nodiscard]] const std::unordered_map<std::string, std::shared_ptr<pipeline::IAttribute<API>>, collection_utils::StringHash, collection_utils::StringEqual> &getAttributes() const
        {
            return m_attributes;
        }

    private:
        std::vector<std::shared_ptr<pipeline::IShader<API>>> m_shaders;
        std::unordered_map<std::string, std::shared_ptr<pipeline::Uniform<API>>, collection_utils::StringHash, collection_utils::StringEqual> m_uniforms;
        std::unordered_map<std::string, std::shared_ptr<pipeline::IAttribute<API>>, collection_utils::StringHash, collection_utils::StringEqual> m_attributes;
    };
}
