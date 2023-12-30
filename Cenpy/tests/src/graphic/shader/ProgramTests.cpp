#ifdef __mock_gl__

#include <gtest/gtest.h>
#include <opengl/glFunctionMock.hpp>
#include <graphic/shader/MockPass.hpp>
#include <graphic/shader/Program.hpp>

namespace shader = cenpy::graphic::shader;
namespace mock_shader = cenpy::mock::graphic::shader;

class ProgramTest : public ::testing::Test
{
protected:
    std::shared_ptr<mock_shader::MockPass> mockPass1 = std::make_shared<mock_shader::MockPass>();
    std::shared_ptr<mock_shader::MockPass> mockPass2 = std::make_shared<mock_shader::MockPass>();
};

TEST_F(ProgramTest, UsePassTest)
{
    shader::opengl::Program<mock_shader::MockShader, shader::opengl::Uniform, shader::opengl::setter, mock_shader::MockPass> program({mockPass1, mockPass2});

    EXPECT_CALL(*mockPass1, use()).Times(1);
    program.use(0);

    EXPECT_CALL(*mockPass2, use()).Times(1);
    program.use(1);
}

TEST_F(ProgramTest, IteratePassesTest)
{
    shader::opengl::Program<mock_shader::MockShader, shader::opengl::Uniform, shader::opengl::setter, mock_shader::MockPass> program({mockPass1, mockPass2});

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
    shader::opengl::Program<mock_shader::MockShader, shader::opengl::Uniform, shader::opengl::setter, mock_shader::MockPass> program({mockPass1, mockPass2});

    program.use(1); // Use the second pass
    program.reset();

    // After reset, it should return to the first pass
    EXPECT_CALL(*mockPass1, use()).Times(1);
    program.useNext();
}

#endif // __mock_gl__