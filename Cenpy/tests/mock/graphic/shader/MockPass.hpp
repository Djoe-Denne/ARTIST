#pragma once

#include <gmock/gmock.h>
#include <graphic/shader/Pass.hpp>

namespace cenpy::mock::graphic::shader
{
    namespace shader = cenpy::graphic::shader;

    class MockPass : public shader::BasePass<shader::opengl::Shader, shader::opengl::Uniform, shader::opengl::setter, MockPass>
    {
    public:
        MockPass()
        {
        }

        MOCK_METHOD(void, use, (), (override));
        MOCK_METHOD(void, load, (), (override));
        MOCK_METHOD(void, readUniforms, ((std::unordered_map<std::string, std::shared_ptr<shader::BaseUniform>, cenpy::collection_utils::StringHash, cenpy::collection_utils::StringEqual> &)), (const, override));
    };
}
