
#include <string>
#include <memory>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <graphic/shader/Program.hpp>
#include <graphic/shader/Pass.hpp>
#include <graphic/shader/MockPass.hpp>
#include <graphic/shader/component/program/MockUser.hpp>
#include <graphic/shader/component/program/MockResetter.hpp>
#include <graphic/context/MockProgramContext.hpp>
#include <graphic/MockApi.hpp>
#include <TestUtils.hpp>

namespace api = cenpy::mock::graphic::api;
namespace context = cenpy::graphic::context;
namespace shader = cenpy::graphic::shader;
namespace mock = cenpy::mock;

using mock::graphic::shader::opengl::MockPass;
using mock::graphic::shader::opengl::component::program::MockResetter;
using mock::graphic::shader::opengl::component::program::MockUser;

using cenpy::test::utils::expectSpecificError;

class ProgramTest : public ::testing::Test
{
};

class MockedProgram : public shader::Program<api::MockOpenGL>
{
public:
    using shader::Program<api::MockOpenGL>::Program;

    std::shared_ptr<MockResetter<api::MockOpenGL>> getResetter() const override
    {
        return shader::Program<api::MockOpenGL>::getResetter();
    }

    std::shared_ptr<MockUser<api::MockOpenGL>> getUser() const override
    {
        return shader::Program<api::MockOpenGL>::getUser();
    }

    friend class ProgramTest;
};

TEST_F(ProgramTest, UseTest)
{
    // Arrange
    auto mockPass1 = std::make_shared<MockPass<api::MockOpenGL>>();
    auto mockPass2 = std::make_shared<MockPass<api::MockOpenGL>>();
    MockedProgram program({mockPass1, mockPass2});

    // Expect calls
    EXPECT_CALL(*program.getUser(), useProgram(::testing::_)).Times(1);

    // Act
    program.use(0); // Using first pass
}

TEST_F(ProgramTest, IteratePassesTest)
{
    // Arrange
    auto mockPass1 = std::make_shared<MockPass<api::MockOpenGL>>();
    auto mockPass2 = std::make_shared<MockPass<api::MockOpenGL>>();
    MockedProgram program({mockPass1, mockPass2});

    // Expect calls
    EXPECT_CALL(*program.getUser(), useProgram(::testing::_)).Times(2);

    // Act
    while (program.hasNext())
    {
        program.useNext();
    }
}

TEST_F(ProgramTest, ResetProgramTest)
{
    // Arrange
    MockedProgram program({nullptr});

    // Expect calls
    EXPECT_CALL(*program.getResetter(), resetProgram(::testing::_)).Times(1);

    // Act
    program.reset();
}