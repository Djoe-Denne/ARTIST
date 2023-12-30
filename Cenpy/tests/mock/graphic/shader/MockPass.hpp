#pragma once

#include <gmock/gmock.h>
#include <graphic/shader/Pass.hpp>
#include <graphic/shader/MockShader.hpp>

namespace cenpy::mock::graphic::shader
{
    namespace shader = cenpy::graphic::shader;

    class MockPass : public shader::BasePass<MockShader, shader::opengl::Uniform, shader::opengl::setter, MockPass>
    {
    public:
        MockPass() : shader::BasePass<MockShader, shader::opengl::Uniform, shader::opengl::setter, MockPass>(std::make_shared<MockShader>())
        {
        }

        MOCK_METHOD(void, use, (), (override));
        MOCK_METHOD(void, load, (), (override));
        MOCK_METHOD(void, readUniforms, ((std::unordered_map<std::string, std::shared_ptr<shader::BaseUniform>, cenpy::collection_utils::StringHash, cenpy::collection_utils::StringEqual> &)), (const, override));
    };
}
