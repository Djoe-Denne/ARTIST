#ifdef __mock_gl__
#include <string>
#include <memory>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <opengl/glFunctionMock.hpp>
#include <graphic/shader/Shader.hpp>

namespace shader = cenpy::graphic::shader;
namespace mock = cenpy::mock;

class ShaderTest : public ::testing::Test
{
public:
};

TEST_F(ShaderTest, CreateShaderVert)
{
    // Arrange
    shader::opengl::Shader shader("test-datas/shaders/vertex/good/minimal.vert", shader::ShaderType::VERTEX);

    // Expect calls
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glCreateShader_mock(GL_VERTEX_SHADER)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glShaderSource_mock(1, 1, ::testing::_, ::testing::_)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glCompileShader_mock(1)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glGetShaderiv_mock(1, ::testing::_, ::testing::_)).Times(1);

    // Act
    ASSERT_NO_THROW(shader.load());

    shader.free();
}

TEST_F(ShaderTest, CreateShaderFrag)
{
    // Arrange
    shader::opengl::Shader shader("test-datas/shaders/fragment/good/minimal.frag", shader::ShaderType::FRAGMENT);

    // Expect calls
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glCreateShader_mock(GL_FRAGMENT_SHADER)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glShaderSource_mock(1, 1, ::testing::_, ::testing::_)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glCompileShader_mock(1)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glGetShaderiv_mock(1, ::testing::_, ::testing::_)).Times(1);

    // Act
    ASSERT_NO_THROW(shader.load());

    shader.free();
}

TEST_F(ShaderTest, CreateShaderGeom)
{
    // Arrange
    shader::opengl::Shader shader("test-datas/shaders/geometry/good/minimal.geom", shader::ShaderType::GEOMETRY);

    // Expect calls
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glCreateShader_mock(GL_GEOMETRY_SHADER)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glShaderSource_mock(1, 1, ::testing::_, ::testing::_)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glCompileShader_mock(1)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glGetShaderiv_mock(1, ::testing::_, ::testing::_)).Times(1);

    // Act
    ASSERT_NO_THROW(shader.load());

    shader.free();
}

TEST_F(ShaderTest, CreateShaderTesselaionControl)
{
    // Arrange
    shader::opengl::Shader shader("test-datas/shaders/tesselaion_control/good/minimal.tesc", shader::ShaderType::TESS_CONTROL);

    // Expect calls
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glCreateShader_mock(GL_TESS_CONTROL_SHADER)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glShaderSource_mock(1, 1, ::testing::_, ::testing::_)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glCompileShader_mock(1)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glGetShaderiv_mock(1, ::testing::_, ::testing::_)).Times(1);

    // Act
    ASSERT_NO_THROW(shader.load());

    shader.free();
}

TEST_F(ShaderTest, CreateShaderCompute)
{
    // Arrange
    shader::opengl::Shader shader("test-datas/shaders/compute/good/minimal.comp", shader::ShaderType::COMPUTE);

    // Expect calls
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glCreateShader_mock(GL_COMPUTE_SHADER)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glShaderSource_mock(1, 1, ::testing::_, ::testing::_)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glCompileShader_mock(1)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glGetShaderiv_mock(1, ::testing::_, ::testing::_)).Times(1);

    // Act
    ASSERT_NO_THROW(shader.load());

    shader.free();
}

TEST_F(ShaderTest, GetLocation)
{
    // Arrange
    shader::opengl::Shader shader("test-datas/shaders/vertex/good/minimal.vert", shader::ShaderType::VERTEX);

    // Expect calls
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glCreateShader_mock(GL_VERTEX_SHADER)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glShaderSource_mock(1, 1, ::testing::_, ::testing::_)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glCompileShader_mock(1)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glGetShaderiv_mock(1, ::testing::_, ::testing::_)).Times(1);

    // Act
    ASSERT_NO_THROW(shader.load());

    ASSERT_EQ(shader.getLocation(), 1);

    shader.free();
}

TEST_F(ShaderTest, GetShaderCode)
{
    // Arrange
    shader::opengl::Shader shader("test-datas/shaders/vertex/good/minimal.vert", shader::ShaderType::VERTEX);

    // Expect calls
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glCreateShader_mock(GL_VERTEX_SHADER)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glShaderSource_mock(1, 1, ::testing::_, ::testing::_)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glCompileShader_mock(1)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glGetShaderiv_mock(1, ::testing::_, ::testing::_)).Times(1);

    // Act
    ASSERT_NO_THROW(shader.load());

    ASSERT_EQ(shader.getShaderCode(), "#version 330 core\n\nvoid main()\n{\n    gl_Position = vec4(0.0, 0.0, 0.0, 1.0);\n}\n");

    shader.free();
}

TEST_F(ShaderTest, GetShaderType)
{
    // Arrange
    shader::opengl::Shader shader("test-datas/shaders/vertex/good/minimal.vert", shader::ShaderType::VERTEX);

    // Expect calls
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glCreateShader_mock(GL_VERTEX_SHADER)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glShaderSource_mock(1, 1, ::testing::_, ::testing::_)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glCompileShader_mock(1)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glGetShaderiv_mock(1, ::testing::_, ::testing::_)).Times(1);

    // Act
    ASSERT_NO_THROW(shader.load());

    ASSERT_EQ(shader.getShaderType(), shader::ShaderType::VERTEX);

    shader.free();
}

#endif //::testing::__mock_gl__