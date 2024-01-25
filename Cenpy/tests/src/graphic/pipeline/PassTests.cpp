#ifdef __mock_gl__
#include <string>
#include <memory>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <opengl/glFunctionMock.hpp>
#include <graphic/pipeline/Pass.hpp>

#include <graphic/opengl/profile/Pass.hpp>
#include <graphic/opengl/validator/Validator.hpp>

#include <graphic/opengl/pipeline/component/pass/MockShaderAttacher.hpp>
#include <graphic/opengl/pipeline/component/pass/MockUniformReader.hpp>
#include <graphic/opengl/pipeline/component/pass/MockAttributeReader.hpp>
#include <graphic/opengl/pipeline/component/pass/MockUser.hpp>
#include <graphic/opengl/pipeline/component/pass/MockFreer.hpp>
#include <graphic/opengl/pipeline/component/pass/MockLoader.hpp>
#include <graphic/pipeline/MockShader.hpp>
#include <graphic/pipeline/MockUniform.hpp>
#include <graphic/pipeline/MockAttribute.hpp>
#include <graphic/opengl/context/MockPassContext.hpp>
#include <graphic/MockApi.hpp>
#include <TestUtils.hpp>

namespace api = cenpy::mock::graphic::api;
namespace context = cenpy::graphic::context;
namespace pipeline = cenpy::graphic::pipeline;
namespace mock = cenpy::mock;

using mock::graphic::opengl::pipeline::component::pass::MockAttributeReader;
using mock::graphic::opengl::pipeline::component::pass::MockFreer;
using mock::graphic::opengl::pipeline::component::pass::MockLoader;
using mock::graphic::opengl::pipeline::component::pass::MockShaderAttacher;
using mock::graphic::opengl::pipeline::component::pass::MockUniformReader;
using mock::graphic::opengl::pipeline::component::pass::MockUser;
using mock::graphic::pipeline::MockAttribute;
using mock::graphic::pipeline::MockShader;
using mock::graphic::pipeline::MockUniform;

using cenpy::graphic::opengl::profile::Pass::Classic;
using cenpy::test::utils::expectSpecificError;
class PassTest : public ::testing::Test
{
public:
    void TearDown() override
    {
        mock::opengl::glFunctionMock::reset();
        MockFreer<Classic>::reset();
        MockLoader<Classic>::reset();
        MockShaderAttacher<Classic>::reset();
        MockUniformReader<Classic>::reset();
        MockUser<Classic>::reset();
        MockAttributeReader<Classic>::reset();
    }
};

TEST_F(PassTest, LoadPass)
{
    // Arrange
    auto mockShader = std::make_shared<MockShader<api::MockOpenGL>>();
    pipeline::Pass<api::MockOpenGL, Classic> pass({mockShader});

    // Expect calls
    EXPECT_CALL(*api::MockOpenGL::PassContext::Loader<Classic>::instance(), mockOn(::testing::_)).Times(1);
    EXPECT_CALL(*api::MockOpenGL::PassContext::UniformReader<Classic>::instance(), mockOn(::testing::_)).Times(1);

    // Act
    ASSERT_NO_THROW(pass.load());
}

TEST_F(PassTest, WithUniforms)
{
    // Arrange
    auto mockShader = std::make_shared<MockShader<api::MockOpenGL>>();
    auto mockUniform = std::make_shared<MockUniform<api::MockOpenGL>>();
    pipeline::Pass<api::MockOpenGL, Classic> pass({mockShader});

    // Expect calls
    EXPECT_CALL(*api::MockOpenGL::PassContext::UniformReader<Classic>::instance(), mockOn(::testing::_)).WillOnce(::testing::Invoke([&](std::shared_ptr<context::PassContext<api::MockOpenGL>> context)
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
    pipeline::Pass<api::MockOpenGL, Classic> pass({mockShader});
    pass.load();

    // Act
    expectSpecificError([&pass]()
                        { pass.withUniform("test", 1.0f); },
                        cenpy::common::exception::TraceableException<std::runtime_error>("ERROR::SHADER::UNIFORM_NOT_FOUND"));
}

TEST_F(PassTest, UsePass)
{
    // Arrange
    pipeline::Pass<api::MockOpenGL, Classic> pass({});

    // Expect calls
    EXPECT_CALL(*api::MockOpenGL::PassContext::User<Classic>::instance(), mockOn(::testing::_)).Times(1);

    // Act
    ASSERT_NO_THROW(pass.use());
}

TEST_F(PassTest, FreePass)
{
    // Arrange
    pipeline::Pass<api::MockOpenGL, Classic> pass({});

    // Expect calls
    EXPECT_CALL(*api::MockOpenGL::PassContext::Freer<Classic>::instance(), mockOn(::testing::_)).Times(2);

    // Act
    ASSERT_NO_THROW(pass.free());
}

TEST_F(PassTest, GetUniforms)
{
    // Arrange
    auto mockShader = std::make_shared<MockShader<api::MockOpenGL>>();
    auto mockUniform = std::make_shared<MockUniform<api::MockOpenGL>>();
    pipeline::Pass<api::MockOpenGL, Classic> pass({mockShader});

    // Expect calls
    EXPECT_CALL(*api::MockOpenGL::PassContext::UniformReader<Classic>::instance(), mockOn(::testing::_)).WillOnce(::testing::Invoke([&](std::shared_ptr<context::PassContext<api::MockOpenGL>> context)
                                                                                                                                    { context->addUniform("test", mockUniform); }));

    pass.load();
    // Act
    ASSERT_EQ(pass.getUniforms().size(), 1);
    ASSERT_TRUE(pass.getUniforms().contains("test"));
}

TEST_F(PassTest, GetAttributes)
{
    // Arrange
    auto mockShader = std::make_shared<MockShader<api::MockOpenGL>>();
    auto mockAttribute = std::make_shared<MockAttribute<api::MockOpenGL>>();
    pipeline::Pass<api::MockOpenGL, Classic> pass({mockShader});

    // Expect calls
    EXPECT_CALL(*api::MockOpenGL::PassContext::AttributeReader<Classic>::instance(), mockOn(::testing::_)).WillOnce(::testing::Invoke([&](std::shared_ptr<context::PassContext<api::MockOpenGL>> context)
                                                                                                                                      { context->addAttribute("test", mockAttribute); }));

    pass.load();
    // Act
    ASSERT_EQ(pass.getAttributes().size(), 1);
    ASSERT_TRUE(pass.getAttributes().contains("test"));
}

TEST_F(PassTest, GetShader)
{
    // Arrange
    auto mockShader = std::make_shared<MockShader<api::MockOpenGL>>();
    pipeline::Pass<api::MockOpenGL, Classic> pass({mockShader});

    // Act
    ASSERT_EQ(pass.getShaders()[0], mockShader);
}

TEST_F(PassTest, GetContext)
{
    // Arrange
    auto mockShader = std::make_shared<MockShader<api::MockOpenGL>>();
    pipeline::Pass<api::MockOpenGL, Classic> pass({mockShader});

    // Act
    ASSERT_NE(pass.getContext(), nullptr);
}

#endif //::testing::__mock_gl__