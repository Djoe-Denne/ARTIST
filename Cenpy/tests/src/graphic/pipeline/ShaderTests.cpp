#ifdef __mock_gl__
#include <string>
#include <memory>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <opengl/glFunctionMock.hpp>
#include <graphic/pipeline/Shader.hpp>

#include <graphic/opengl/profile/Shader.hpp>
#include <graphic/opengl/validator/Validator.hpp>

#include <graphic/opengl/pipeline/component/shader/MockReader.hpp>
#include <graphic/opengl/pipeline/component/shader/MockLoader.hpp>
#include <graphic/opengl/pipeline/component/shader/MockFreer.hpp>
#include <graphic/opengl/context/MockShaderContext.hpp>
#include <graphic/MockApi.hpp>

namespace api = cenpy::mock::graphic::api;
namespace context = cenpy::graphic::context;
namespace pipeline = cenpy::graphic::pipeline;
namespace mock = cenpy::mock;

using mock::graphic::opengl::pipeline::component::shader::MockFreer;
using mock::graphic::opengl::pipeline::component::shader::MockLoader;
using mock::graphic::opengl::pipeline::component::shader::MockReader;

using cenpy::graphic::opengl::profile::Shader::Classic;

class ShaderTest : public ::testing::Test
{
public:
    void TearDown() override
    {
        mock::opengl::glFunctionMock::reset();
        MockFreer<Classic>::reset();
        MockLoader<Classic>::reset();
        MockReader<Classic>::reset();
    }
};

TEST_F(ShaderTest, CreateShader)
{
    // Arrange
    pipeline::Shader<api::MockOpenGL, Classic> shader("test-datas/shaders/vertex/good/minimal.vert", context::ShaderType::VERTEX);

    // Expect calls
    std::string code("");
    ON_CALL(*shader.getContext(), getShaderCode()).WillByDefault(::testing::ReturnRef(code));
    EXPECT_CALL(*MockReader<Classic>::instance(), mockOn(::testing::_)).Times(1);
    EXPECT_CALL(*MockLoader<Classic>::instance(), mockOn(::testing::_)).Times(1);
    // Act
    ASSERT_NO_THROW(shader.load());
}

TEST_F(ShaderTest, CreateShader_codeAlreadyRead)
{
    // Arrange
    pipeline::Shader<api::MockOpenGL, Classic> shader("test-datas/shaders/vertex/good/minimal.vert", context::ShaderType::VERTEX);

    // Expect calls
    std::string code("test");
    ON_CALL(*shader.getContext(), getShaderCode()).WillByDefault(::testing::ReturnRef(code));
    EXPECT_CALL(*MockReader<Classic>::instance(), mockOn(::testing::_)).Times(0);
    EXPECT_CALL(*MockLoader<Classic>::instance(), mockOn(::testing::_)).Times(1);
    // Act
    ASSERT_NO_THROW(shader.load());
}

TEST_F(ShaderTest, Free)
{
    // Arrange
    pipeline::Shader<api::MockOpenGL, Classic> shader("test-datas/shaders/vertex/good/minimal.vert", context::ShaderType::VERTEX);

    // Expect calls
    EXPECT_CALL(*MockFreer<Classic>::instance(), mockOn(::testing::_)).Times(2);

    ASSERT_NO_THROW(shader.free());
}

TEST_F(ShaderTest, DeleteMustFree)
{
    // Arrange
    auto shader = new pipeline::Shader<api::MockOpenGL, Classic>("test-datas/shaders/vertex/good/minimal.vert", context::ShaderType::VERTEX);

    // Expect calls
    EXPECT_CALL(*MockFreer<Classic>::instance(), mockOn(::testing::_)).Times(1);

    ASSERT_NO_THROW(delete shader);
}

#endif //::testing::__mock_gl__