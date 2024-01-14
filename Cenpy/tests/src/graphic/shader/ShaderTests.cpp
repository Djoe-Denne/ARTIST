#ifdef __mock_gl__
#include <string>
#include <memory>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <opengl/glFunctionMock.hpp>
#include <graphic/pipeline/Shader.hpp>
#include <graphic/pipeline/component/shader/MockReader.hpp>
#include <graphic/pipeline/component/shader/MockLoader.hpp>
#include <graphic/pipeline/component/shader/MockFreer.hpp>
#include <graphic/context/MockShaderContext.hpp>
#include <graphic/MockApi.hpp>

namespace api = cenpy::mock::graphic::api;
namespace context = cenpy::graphic::context;
namespace pipeline = cenpy::graphic::pipeline;
namespace mock = cenpy::mock;

using mock::graphic::pipeline::opengl::component::shader::MockFreer;
using mock::graphic::pipeline::opengl::component::shader::MockLoader;
using mock::graphic::pipeline::opengl::component::shader::MockReader;

class ShaderTest : public ::testing::Test
{
public:
    void TearDown() override
    {
        mock::opengl::glFunctionMock::reset();
    }
};

class MockedShader : public pipeline::Shader<api::MockOpenGL>
{
public:
    using pipeline::Shader<api::MockOpenGL>::Shader;

    std::shared_ptr<MockLoader<api::MockOpenGL>> getLoader() const override
    {
        return pipeline::Shader<api::MockOpenGL>::getLoader();
    }

    std::shared_ptr<MockReader<api::MockOpenGL>> getReader() const override
    {
        return pipeline::Shader<api::MockOpenGL>::getReader();
    }

    std::shared_ptr<MockFreer<api::MockOpenGL>> getFreer() const override
    {
        return pipeline::Shader<api::MockOpenGL>::getFreer();
    }

    friend class ShaderTest;
};

TEST_F(ShaderTest, CreateShader)
{
    // Arrange
    MockedShader shader("test-datas/shaders/vertex/good/minimal.vert", context::ShaderType::VERTEX);

    // Expect calls
    std::string code("");
    ON_CALL(*shader.getContext(), getShaderCode()).WillByDefault(::testing::ReturnRef(code));
    EXPECT_CALL(*shader.getReader(), readShader(::testing::_)).Times(1);
    EXPECT_CALL(*shader.getLoader(), loadShader(::testing::_)).Times(1);
    // Act
    ASSERT_NO_THROW(shader.load());
}

TEST_F(ShaderTest, CreateShader_codeAlreadyRead)
{
    // Arrange
    MockedShader shader("test-datas/shaders/vertex/good/minimal.vert", context::ShaderType::VERTEX);

    // Expect calls
    std::string code("test");
    ON_CALL(*shader.getContext(), getShaderCode()).WillByDefault(::testing::ReturnRef(code));
    EXPECT_CALL(*shader.getReader(), readShader(::testing::_)).Times(0);
    EXPECT_CALL(*shader.getLoader(), loadShader(::testing::_)).Times(1);
    // Act
    ASSERT_NO_THROW(shader.load());
}

TEST_F(ShaderTest, Free)
{
    // Arrange
    MockedShader shader("test-datas/shaders/vertex/good/minimal.vert", context::ShaderType::VERTEX);

    // Expect calls
    EXPECT_CALL(*shader.getFreer(), freeShader(::testing::_)).Times(2);

    ASSERT_NO_THROW(shader.free());
}

TEST_F(ShaderTest, DeleteMustFree)
{
    // Arrange
    auto shader = new MockedShader("test-datas/shaders/vertex/good/minimal.vert", context::ShaderType::VERTEX);

    // Expect calls
    EXPECT_CALL(*shader->getFreer(), freeShader(::testing::_)).Times(1);

    ASSERT_NO_THROW(delete shader);
}

#endif //::testing::__mock_gl__