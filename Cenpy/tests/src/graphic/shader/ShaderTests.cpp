#ifdef __mock_gl__
#include <string>
#include <memory>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <opengl/glFunctionMock.hpp>
#include <graphic/shader/Shader.hpp>
#include <graphic/context/MockShaderContext.hpp>
#include <graphic/MockApi.hpp>

namespace api = cenpy::mock::graphic::api;
namespace context = cenpy::graphic::context;
namespace shader = cenpy::graphic::shader;
namespace mock = cenpy::mock;

class ShaderTest : public ::testing::Test
{
public:
    void TearDown() override
    {
        mock::opengl::glFunctionMock::reset();
    }
};

TEST_F(ShaderTest, CreateShaderVert)
{
    // Arrange
    shader::Shader<api::MockOpenGL> shader("test-datas/shaders/vertex/good/minimal.vert", context::ShaderType::VERTEX);

    // Expect calls
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glCreateShader_mock(GL_VERTEX_SHADER)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glShaderSource_mock(1, 1, ::testing::_, ::testing::_)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glCompileShader_mock(1)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glGetShaderiv_mock(1, ::testing::_, ::testing::_)).Times(1);

    // Act
    ASSERT_NO_THROW(shader.load());
}

TEST_F(ShaderTest, CreateShaderFrag)
{
    // Arrange
    shader::Shader<api::MockOpenGL> shader("test-datas/shaders/fragment/good/minimal.frag", context::ShaderType::FRAGMENT);

    // Expect calls
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glCreateShader_mock(GL_FRAGMENT_SHADER)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glShaderSource_mock(1, 1, ::testing::_, ::testing::_)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glCompileShader_mock(1)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glGetShaderiv_mock(1, ::testing::_, ::testing::_)).Times(1);

    // Act
    ASSERT_NO_THROW(shader.load());
}

TEST_F(ShaderTest, CreateShaderGeom)
{
    // Arrange
    shader::Shader<api::MockOpenGL> shader("test-datas/shaders/geometry/good/minimal.geom", context::ShaderType::GEOMETRY);

    // Expect calls
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glCreateShader_mock(GL_GEOMETRY_SHADER)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glShaderSource_mock(1, 1, ::testing::_, ::testing::_)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glCompileShader_mock(1)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glGetShaderiv_mock(1, ::testing::_, ::testing::_)).Times(1);

    // Act
    ASSERT_NO_THROW(shader.load());
}

TEST_F(ShaderTest, CreateShaderTesselaionControl)
{
    // Arrange
    shader::Shader<api::MockOpenGL> shader("test-datas/shaders/tesselaion_control/good/minimal.tesc", context::ShaderType::TESS_CONTROL);

    // Expect calls
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glCreateShader_mock(GL_TESS_CONTROL_SHADER)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glShaderSource_mock(1, 1, ::testing::_, ::testing::_)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glCompileShader_mock(1)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glGetShaderiv_mock(1, ::testing::_, ::testing::_)).Times(1);

    // Act
    ASSERT_NO_THROW(shader.load());
}

TEST_F(ShaderTest, CreateShaderCompute)
{
    // Arrange
    shader::Shader<api::MockOpenGL> shader("test-datas/shaders/compute/good/minimal.comp", context::ShaderType::COMPUTE);

    // Expect calls
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glCreateShader_mock(GL_COMPUTE_SHADER)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glShaderSource_mock(1, 1, ::testing::_, ::testing::_)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glCompileShader_mock(1)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glGetShaderiv_mock(1, ::testing::_, ::testing::_)).Times(1);

    // Act
    ASSERT_NO_THROW(shader.load());
}

TEST_F(ShaderTest, GetLocation)
{
    // Arrange
    shader::Shader<api::MockOpenGL> shader("test-datas/shaders/vertex/good/minimal.vert", context::ShaderType::VERTEX);

    // Expect calls
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glCreateShader_mock(GL_VERTEX_SHADER)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glShaderSource_mock(1, 1, ::testing::_, ::testing::_)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glCompileShader_mock(1)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glGetShaderiv_mock(1, ::testing::_, ::testing::_)).Times(1);

    // Act
    ASSERT_NO_THROW(shader.load());

    ASSERT_EQ(shader.getContext()->getShaderID(), 1);
}

TEST_F(ShaderTest, GetShaderCode)
{
    // Arrange
    shader::Shader<api::MockOpenGL> shader("test-datas/shaders/vertex/good/minimal.vert", context::ShaderType::VERTEX);

    // Expect calls
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glCreateShader_mock(GL_VERTEX_SHADER)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glShaderSource_mock(1, 1, ::testing::_, ::testing::_)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glCompileShader_mock(1)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glGetShaderiv_mock(1, ::testing::_, ::testing::_)).Times(1);

    // Act
    ASSERT_NO_THROW(shader.load());

    std::string code = R"(#version 330 core

uniform int testUniform;
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos, 1.0) * float(testUniform);
}
)";

    ASSERT_EQ(shader.getShaderCode(), code);
}

TEST_F(ShaderTest, GetShaderType)
{
    // Arrange
    shader::Shader<api::MockOpenGL> shader("test-datas/shaders/vertex/good/minimal.vert", context::ShaderType::VERTEX);

    // Expect calls
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glCreateShader_mock(GL_VERTEX_SHADER)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glShaderSource_mock(1, 1, ::testing::_, ::testing::_)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glCompileShader_mock(1)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glGetShaderiv_mock(1, ::testing::_, ::testing::_)).Times(1);

    // Act
    ASSERT_NO_THROW(shader.load());

    ASSERT_EQ(shader.getShaderType(), context::ShaderType::VERTEX);
}

TEST_F(ShaderTest, Free)
{
    // Arrange
    shader::Shader<api::MockOpenGL> shader("test-datas/shaders/vertex/good/minimal.vert", context::ShaderType::VERTEX);

    // Expect calls
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glDeleteShader_mock(::testing::_)).Times(2);

    ASSERT_NO_THROW(shader.free());
}

TEST_F(ShaderTest, DeleteMustFree)
{
    // Arrange
    auto shader = new shader::Shader<api::MockOpenGL>("test-datas/shaders/vertex/good/minimal.vert", context::ShaderType::VERTEX);

    // Expect calls
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glDeleteShader_mock(::testing::_)).Times(1);

    ASSERT_NO_THROW(delete shader);
}

#endif //::testing::__mock_gl__