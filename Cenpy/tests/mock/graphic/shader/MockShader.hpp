#include <gmock/gmock.h>
#include <graphic/shader/Shader.hpp>

namespace cenpy::mock::graphic::shader
{
    namespace shader = cenpy::graphic::shader;

    class MockShader : public shader::opengl::Shader
    {
    public:
        MockShader()
            : Shader("", shader::ShaderType::VERTEX)
        {
            ON_CALL(*this, getLocation).WillByDefault(::testing::Return((GLuint)1));
        }
        MockShader(const std::string &shaderPath, const shader::ShaderType &shaderType)
            : Shader(shaderPath, shaderType)
        {
            ON_CALL(*this, getLocation).WillByDefault(::testing::Return((GLuint)1));
        }

        MOCK_METHOD(void, free, (), (override));
        MOCK_METHOD(void, load, (), (override));
        MOCK_METHOD(GLuint, getLocation, (), (const, override));
    };

}
