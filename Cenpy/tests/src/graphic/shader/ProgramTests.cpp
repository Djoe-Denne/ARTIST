#ifdef __mock_gl__

#include <gtest/gtest.h>
#include <opengl/glFunctionMock.hpp>
#include <graphic/shader/MockPass.hpp>
#include <graphic/context/MockProgramContext.hpp>
#include <graphic/shader/Program.hpp>
#include <graphic/MockApi.hpp>

namespace api = cenpy::mock::graphic::api;
namespace context = cenpy::graphic::context;
namespace shader = cenpy::graphic::shader;
namespace mock_shader = cenpy::mock::graphic::shader::opengl;

class ProgramTest : public ::testing::Test
{
protected:
    std::shared_ptr<mock_shader::MockPass> mockPass1 = std::make_shared<mock_shader::MockPass>();
    std::shared_ptr<mock_shader::MockPass> mockPass2 = std::make_shared<mock_shader::MockPass>();
};

TEST_F(ProgramTest, UsePassTest)
{
    shader::Program<api::MockOpenGL> program({mockPass1, mockPass2});

    EXPECT_CALL(*mockPass1, use()).Times(1);
    program.use(0);

    EXPECT_CALL(*mockPass2, use()).Times(1);
    program.use(1);
}

TEST_F(ProgramTest, IteratePassesTest)
{
    shader::Program<api::MockOpenGL> program({mockPass1, mockPass2});

    EXPECT_CALL(*mockPass1, use()).Times(1);
    EXPECT_CALL(*mockPass2, use()).Times(1);

    while (program.useNext())
    {
    }

    // Checks if it iterates through all passes
    ASSERT_EQ(program.getPassesCount(), 2);
}

TEST_F(ProgramTest, ResetProgramTest)
{
    shader::Program<api::MockOpenGL> program({mockPass1, mockPass2});

    program.use(1); // Use the second pass
    program.reset();

    // After reset, it should return to the first pass
    EXPECT_CALL(*mockPass1, use()).Times(1);
    program.useNext();
}

#endif // __mock_gl__