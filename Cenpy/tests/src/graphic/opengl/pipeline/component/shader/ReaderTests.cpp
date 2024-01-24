#ifdef __mock_gl__

#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <opengl/glFunctionMock.hpp>
#include <graphic/MockApi.hpp>
#include <graphic/opengl/profile/Shader.hpp>
#include <graphic/opengl/context/ShaderContext.hpp>
#include <graphic/opengl/pipeline/component/shader/Reader.hpp>

namespace context = cenpy::graphic::opengl::context;
namespace shader = cenpy::graphic::opengl::pipeline::component::shader;
namespace mock = cenpy::mock;
namespace api = cenpy::graphic::api;
using cenpy::graphic::opengl::profile::Shader::Classic;

class ReaderTests : public ::testing::Test
{
public:
    void TearDown() override
    {
        mock::opengl::glFunctionMock::reset();
    }
};

TEST_F(ReaderTests, ReadShaderTest)
{
    // Arrange
    auto context = std::make_shared<context::OpenGLShaderContext>();
    context->setShaderPath("test-datas/shaders/vertex/good/minimal.vert");
    std::string code = R"(#version 330 core

uniform int testUniform;
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos, 1.0) * float(testUniform);
}
)";

    // Act
    shader::OpenGLShaderReader<Classic>::on(context);

    // Assert
    ASSERT_EQ(context->getShaderCode(), code);
}

#endif // __mock_gl__