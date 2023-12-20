#ifdef __mock_gl__
#include <any>
#include <iostream>
#include <string>
#include <memory>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <opengl/glFunctionMock.hpp>
#include <graphic/shader/MockUniform.hpp>
#include <graphic/shader/Program.hpp>

namespace shader = cenpy::graphic::shader::opengl;
namespace mock = cenpy::mock;
namespace shaderMock = mock::graphic::shader;

template <typename U>
struct mockUniformSetter : cenpy::graphic::shader::baseSetter<mock::graphic::shader::MockUniform, U>
{
};

class ProgramTest : public ::testing::Test
{
public:
};

TEST_F(ProgramTest, CreateProgram)
{
    // Arrange

    // Act
    // ASSERT_NO_THROW(shader::Program shader("test-datas/shaders/vertex/good/minimal.vert", "test-datas/shaders/fargment/good/minimal.frag"));

    // Assert
}

TEST_F(ProgramTest, CreateProgramWithBadVertexProgram)
{
    // Arrange

    // Act
    // ASSERT_THROW(shader::Program shader("test-datas/shaders/vertex/bad/minimal.vert", "test-datas/shaders/fargment/good/minimal.frag"), std::runtime_error);

    // Assert
}

TEST_F(ProgramTest, CreateProgramWithBadFragmentProgram)
{
    // Arrange

    // Act
    // ASSERT_THROW(shader::Program shader("test-datas/shaders/vertex/good/minimal.vert", "test-datas/shaders/fargment/bad/minimal.frag"), std::runtime_error);

    // Assert
}

TEST_F(ProgramTest, CreateProgramWithBadVertexAndFragmentProgram)
{
    // Arrange

    // Act
    // ASSERT_THROW(shader::Program shader("test-datas/shaders/vertex/bad/minimal.vert", "test-datas/shaders/fargment/bad/minimal.frag"), std::runtime_error);

    // Assert
}

TEST_F(ProgramTest, AddUniform)
{ /*
     // Arrange
     shader::Program<shaderMock::MockUniform, shaderMock::mockUniformSetter> shader("test-datas/shaders/vertex/good/minimal.vert", "test-datas/shaders/fargment/good/minimal.frag");

     // Expected call
     EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glUniform1f_mock(1, 3.14f))
         .Times(1);

     // Act
     shader.prepare().withUniform("uniform_test", 3.14f);*/

    // Assert
}
#endif // __mock_gl__