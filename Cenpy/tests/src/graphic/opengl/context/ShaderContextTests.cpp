#include <gtest/gtest.h>
#include <graphic/opengl/context/ShaderContext.hpp>

using namespace cenpy::graphic::context;
using namespace cenpy::graphic::opengl::context;

// Test fixture for ShaderContext
class ShaderContextTests : public ::testing::Test
{
protected:
    // Create a new instance of ShaderContext for each test case
    void SetUp() override
    {
        m_shaderContext = std::make_unique<OpenGLShaderContext>();
    }

    // Clean up resources after each test case
    void TearDown() override
    {
        m_shaderContext.reset();
    }

    std::unique_ptr<OpenGLShaderContext> m_shaderContext;
};

// Test case for setting and getting shader type
TEST_F(ShaderContextTests, SetAndGetShaderTypeforVertexShader)
{
    ShaderType shaderType = ShaderType::VERTEX;
    m_shaderContext->setShaderType(shaderType);
    EXPECT_EQ(m_shaderContext->getShaderType(), shaderType);
    EXPECT_EQ(m_shaderContext->getGLShaderType(), GL_VERTEX_SHADER);
}

TEST_F(ShaderContextTests, SetAndGetShaderTypeforFragmentShader)
{
    ShaderType shaderType = ShaderType::FRAGMENT;
    m_shaderContext->setShaderType(shaderType);
    EXPECT_EQ(m_shaderContext->getShaderType(), shaderType);
    EXPECT_EQ(m_shaderContext->getGLShaderType(), GL_FRAGMENT_SHADER);
}

TEST_F(ShaderContextTests, SetAndGetShaderTypeforGeometryShader)
{
    ShaderType shaderType = ShaderType::GEOMETRY;
    m_shaderContext->setShaderType(shaderType);
    EXPECT_EQ(m_shaderContext->getShaderType(), shaderType);
    EXPECT_EQ(m_shaderContext->getGLShaderType(), GL_GEOMETRY_SHADER);
}

TEST_F(ShaderContextTests, SetAndGetShaderTypeforTessellationControlShader)
{
    ShaderType shaderType = ShaderType::TESS_CONTROL;
    m_shaderContext->setShaderType(shaderType);
    EXPECT_EQ(m_shaderContext->getShaderType(), shaderType);
    EXPECT_EQ(m_shaderContext->getGLShaderType(), GL_TESS_CONTROL_SHADER);
}

TEST_F(ShaderContextTests, SetAndGetShaderTypeforTessellationEvaluationShader)
{
    ShaderType shaderType = ShaderType::TESS_EVALUATION;
    m_shaderContext->setShaderType(shaderType);
    EXPECT_EQ(m_shaderContext->getShaderType(), shaderType);
    EXPECT_EQ(m_shaderContext->getGLShaderType(), GL_TESS_EVALUATION_SHADER);
}

TEST_F(ShaderContextTests, SetAndGetShaderTypeforComputeShader)
{
    ShaderType shaderType = ShaderType::COMPUTE;
    m_shaderContext->setShaderType(shaderType);
    EXPECT_EQ(m_shaderContext->getShaderType(), shaderType);
    EXPECT_EQ(m_shaderContext->getGLShaderType(), GL_COMPUTE_SHADER);
}

// Add more test cases as needed
