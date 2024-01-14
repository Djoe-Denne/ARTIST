#ifdef __mock_gl__
#include <string>
#include <memory>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <opengl/glFunctionMock.hpp>
#include <graphic/pipeline/Pass.hpp>
#include <graphic/pipeline/component/pass/MockShaderAttacher.hpp>
#include <graphic/pipeline/component/pass/MockUniformReader.hpp>
#include <graphic/pipeline/component/pass/MockUser.hpp>
#include <graphic/pipeline/component/pass/MockFreer.hpp>
#include <graphic/pipeline/component/pass/MockLoader.hpp>
#include <graphic/pipeline/MockShader.hpp>
#include <graphic/pipeline/MockUniform.hpp>
#include <graphic/context/MockPassContext.hpp>
#include <graphic/MockApi.hpp>
#include <TestUtils.hpp>

namespace api = cenpy::mock::graphic::api;
namespace context = cenpy::graphic::context;
namespace pipeline = cenpy::graphic::pipeline;
namespace mock = cenpy::mock;

using mock::graphic::pipeline::MockShader;
using mock::graphic::pipeline::MockUniform;
using mock::graphic::pipeline::opengl::component::pass::MockFreer;
using mock::graphic::pipeline::opengl::component::pass::MockLoader;
using mock::graphic::pipeline::opengl::component::pass::MockShaderAttacher;
using mock::graphic::pipeline::opengl::component::pass::MockUniformReader;
using mock::graphic::pipeline::opengl::component::pass::MockUser;

using cenpy::test::utils::expectSpecificError;
class PassTest : public ::testing::Test
{
public:
    void TearDown() override
    {
        mock::opengl::glFunctionMock::reset();
    }
};

class MockedPass : public pipeline::Pass<api::MockOpenGL>
{
public:
    using pipeline::Pass<api::MockOpenGL>::Pass;

    std::shared_ptr<MockLoader<api::MockOpenGL>> getLoader() const override
    {
        return pipeline::Pass<api::MockOpenGL>::getLoader();
    }

    std::shared_ptr<MockFreer<api::MockOpenGL>> getFreer() const override
    {
        return pipeline::Pass<api::MockOpenGL>::getFreer();
    }

    std::shared_ptr<MockShaderAttacher<api::MockOpenGL>> getAttacher() const override
    {
        return pipeline::Pass<api::MockOpenGL>::getAttacher();
    }

    std::shared_ptr<MockUniformReader<api::MockOpenGL>> getUniformReader() const override
    {
        return pipeline::Pass<api::MockOpenGL>::getUniformReader();
    }

    std::shared_ptr<MockUser<api::MockOpenGL>> getUser() const override
    {
        return pipeline::Pass<api::MockOpenGL>::getUser();
    }

    friend class PassTest;
};

TEST_F(PassTest, LoadPass)
{
    // Arrange
    auto mockShader = std::make_shared<MockShader<api::MockOpenGL>>();
    MockedPass pass({mockShader});

    // Expect calls
    EXPECT_CALL(*pass.getLoader(), loadPass(::testing::_)).Times(1);
    EXPECT_CALL(*pass.getUniformReader(), readUniforms(::testing::_)).Times(1);

    // Act
    ASSERT_NO_THROW(pass.load());
}

TEST_F(PassTest, WithUniforms)
{
    // Arrange
    auto mockShader = std::make_shared<MockShader<api::MockOpenGL>>();
    auto mockUniform = std::make_shared<MockUniform<api::MockOpenGL>>();
    MockedPass pass({mockShader});

    // Expect calls
    EXPECT_CALL(*pass.getUniformReader(), readUniforms(::testing::_)).WillOnce(::testing::Invoke([&](std::shared_ptr<context::PassContext<api::MockOpenGL>> context)
                                                                                                 { context->addUniform("test", mockUniform); }));
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glUniform1f_mock(::testing::_, ::testing::_)).Times(1);

    pass.load();

    // Act
    ASSERT_NO_THROW(pass.withUniform("test", 1.0f));
}

TEST_F(PassTest, WithUniforms_NoUniform)
{
    // Arrange
    auto mockShader = std::make_shared<MockShader<api::MockOpenGL>>();
    auto mockUniform = std::make_shared<MockUniform<api::MockOpenGL>>();
    MockedPass pass({mockShader});
    pass.load();

    // Act
    expectSpecificError([&pass]()
                        { pass.withUniform("test", 1.0f); },
                        cenpy::common::exception::TraceableException<std::runtime_error>("ERROR::SHADER::UNIFORM_NOT_FOUND"));
}

TEST_F(PassTest, UsePass)
{
    // Arrange
    MockedPass pass({});

    // Expect calls
    EXPECT_CALL(*pass.getUser(), usePass(::testing::_)).Times(1);

    // Act
    ASSERT_NO_THROW(pass.use());
}

TEST_F(PassTest, FreePass)
{
    // Arrange
    MockedPass pass({});

    // Expect calls
    EXPECT_CALL(*pass.getFreer(), freePass(::testing::_)).Times(2);

    // Act
    ASSERT_NO_THROW(pass.free());
}

#endif //::testing::__mock_gl__