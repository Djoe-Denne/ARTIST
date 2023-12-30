#ifdef __mock_gl__
#include <string>
#include <memory>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <opengl/glFunctionMock.hpp>
#include <graphic/shader/MockShader.hpp>
#include <graphic/shader/Pass.hpp>

namespace shader = cenpy::graphic::shader;
namespace mock = cenpy::mock;
namespace mock_shader = cenpy::mock::graphic::shader;

// PassTest.cpp

class PassTest : public ::testing::Test
{
protected:
    void TearDown() override
    {
        mock::opengl::glFunctionMock::reset();
    }
};

TEST_F(PassTest, PassCreation)
{
    // Arrange
    auto vertexShader = std::make_shared<mock_shader::MockShader>("vertex_shader_path", shader::ShaderType::VERTEX);
    auto fragmentShader = std::make_shared<mock_shader::MockShader>("fragment_shader_path", shader::ShaderType::FRAGMENT);

    // Act and Assert
    EXPECT_NO_THROW(shader::opengl::Pass<mock_shader::MockShader> pass(vertexShader, fragmentShader));
}

TEST_F(PassTest, attachShaders)
{
    // Arrange
    auto vertexShader = std::make_shared<mock_shader::MockShader>("vertex_shader_path", shader::ShaderType::VERTEX);
    auto fragmentShader = std::make_shared<mock_shader::MockShader>("fragment_shader_path", shader::ShaderType::FRAGMENT);

    EXPECT_CALL(*vertexShader, load()).Times(1);
    EXPECT_CALL(*fragmentShader, load()).Times(1);

    // Act
    shader::opengl::Pass<mock_shader::MockShader> pass(vertexShader, fragmentShader);

    // Assertions can be done here if there are any effects to be checked
}

TEST_F(PassTest, DeleteMustFree)
{
    // Arrange
    auto vertexShader = std::make_shared<mock_shader::MockShader>("vertex_shader_path", shader::ShaderType::VERTEX);
    auto fragmentShader = std::make_shared<mock_shader::MockShader>("fragment_shader_path", shader::ShaderType::FRAGMENT);

    EXPECT_CALL(*vertexShader, free()).Times(1);
    EXPECT_CALL(*fragmentShader, free()).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glDeleteProgram_mock(::testing::_)).Times(1);

    // Act
    const auto &pass = new shader::opengl::Pass<mock_shader::MockShader>(vertexShader, fragmentShader);

    delete pass;
}

TEST_F(PassTest, ShaderAttachment)
{
    // Arrange
    auto vertexShader = std::make_shared<mock_shader::MockShader>("vertex_shader_path", shader::ShaderType::VERTEX);
    auto fragmentShader = std::make_shared<mock_shader::MockShader>("fragment_shader_path", shader::ShaderType::FRAGMENT);

    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glAttachShader_mock(1, 1)).Times(2);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glLinkProgram_mock(1)).Times(1);

    // Act
    shader::opengl::Pass<mock_shader::MockShader> pass(vertexShader, fragmentShader);
}

TEST_F(PassTest, ReadUniformsGetUniformiv)
{
    // Arrange
    auto vertexShader = std::make_shared<mock_shader::MockShader>("vertex_shader_path", shader::ShaderType::VERTEX);
    auto fragmentShader = std::make_shared<mock_shader::MockShader>("fragment_shader_path", shader::ShaderType::FRAGMENT);

    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glGetProgramiv_mock(1, ::testing::_, ::testing::_)).Times(2);

    // Act
    shader::opengl::Pass<mock_shader::MockShader> pass(vertexShader, fragmentShader);
}

TEST_F(PassTest, ReadUniformsGetActiveUniform)
{
    // Arrange
    auto vertexShader = std::make_shared<mock_shader::MockShader>("vertex_shader_path", shader::ShaderType::VERTEX);
    auto fragmentShader = std::make_shared<mock_shader::MockShader>("fragment_shader_path", shader::ShaderType::FRAGMENT);

    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glGetActiveUniform_mock(1, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(1);

    // Act
    shader::opengl::Pass<mock_shader::MockShader> pass(vertexShader, fragmentShader);
}

TEST_F(PassTest, ReadUniformsGetUniformLocation)
{
    // Arrange
    auto vertexShader = std::make_shared<mock_shader::MockShader>("vertex_shader_path", shader::ShaderType::VERTEX);
    auto fragmentShader = std::make_shared<mock_shader::MockShader>("fragment_shader_path", shader::ShaderType::FRAGMENT);

    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glGetUniformLocation_mock(1, ::testing::_)).Times(1);

    // Act
    shader::opengl::Pass<mock_shader::MockShader> pass(vertexShader, fragmentShader);
}

TEST_F(PassTest, ReadUniforms)
{
    // Arrange
    auto vertexShader = std::make_shared<mock_shader::MockShader>("vertex_shader_path", shader::ShaderType::VERTEX);
    auto fragmentShader = std::make_shared<mock_shader::MockShader>("fragment_shader_path", shader::ShaderType::FRAGMENT);

    // Act
    shader::opengl::Pass<mock_shader::MockShader> pass(vertexShader, fragmentShader);

    // Assert
    EXPECT_TRUE(pass.getUniforms().contains("uniform_test"));
}

TEST_F(PassTest, TestErrorHandlingOnShaderFailure)
{
    // Arrange
    auto failingShader = std::make_shared<mock_shader::MockShader>("vertex_shader_path", shader::ShaderType::VERTEX);
    EXPECT_CALL(*failingShader, load()).WillOnce(::testing::Throw(std::runtime_error("Shader load failed")));

    // Act and Assert
    EXPECT_THROW(shader::opengl::Pass<mock_shader::MockShader> pass(failingShader), std::runtime_error);
}

TEST_F(PassTest, WithUniformShouldSetIfExist)
{
    // Arrange
    auto vertexShader = std::make_shared<mock_shader::MockShader>("vertex_shader_path", shader::ShaderType::VERTEX);
    auto fragmentShader = std::make_shared<mock_shader::MockShader>("fragment_shader_path", shader::ShaderType::FRAGMENT);
    shader::opengl::Pass<mock_shader::MockShader> pass(vertexShader, fragmentShader);

    // Expect
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glUniform1f_mock(1, 3.14f)).Times(1);

    // Act
    ASSERT_NO_THROW(pass.withUniform("uniform_test", 3.14f));

    // Assert
}

TEST_F(PassTest, UseShouldCallUseProgram)
{
    // Arrange
    auto vertexShader = std::make_shared<mock_shader::MockShader>("vertex_shader_path", shader::ShaderType::VERTEX);
    auto fragmentShader = std::make_shared<mock_shader::MockShader>("fragment_shader_path", shader::ShaderType::FRAGMENT);
    shader::opengl::Pass<mock_shader::MockShader> pass(vertexShader, fragmentShader);

    // Expect
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glUseProgram_mock(1)).Times(1);

    // Act
    pass.use();

    // Assert
    // Add any additional assertions if needed
}

#endif //::testing::__mock_gl__