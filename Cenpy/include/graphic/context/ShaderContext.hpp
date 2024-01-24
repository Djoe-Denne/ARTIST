// ShaderContext.hpp

#pragma once

namespace cenpy::graphic::context
{
    enum class ShaderType
    {
        VERTEX,
        FRAGMENT,
        GEOMETRY,
        TESS_CONTROL,
        TESS_EVALUATION,
        COMPUTE
    };

    /**
     * @class ShaderContext
     * @brief Abstract base class for shader context.
     *
     * The ShaderContext class provides an interface for managing shader-specific
     * details and state. It serves as a base for API-specific implementations
     * to handle shader resources and state management in a way that is tailored
     * to each graphics API.
     */
    template <typename API>
    class ShaderContext
    {
    public:
        virtual ~ShaderContext() = default;

        virtual void setShaderType(ShaderType shaderType)
        {
            m_shaderType = shaderType;
        }

        [[nodiscard]] virtual graphic::context::ShaderType getShaderType() const
        {
            return m_shaderType;
        }

        virtual void setShaderPath(const std::string &shaderPath)
        {
            m_shaderPath = shaderPath;
        }

        [[nodiscard]] virtual const std::string &getShaderPath() const
        {
            return m_shaderPath;
        }

        virtual void setShaderCode(const std::string &shaderCode)
        {
            m_shaderCode = shaderCode;
        }

        [[nodiscard]] virtual const std::string &getShaderCode() const
        {
            return m_shaderCode;
        }

    private:
        ShaderType m_shaderType;  ///< Shader type
        std::string m_shaderPath; // Path to the shader source code
        std::string m_shaderCode; // The code of the shader
    };

}