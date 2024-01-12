#pragma once

#include <gmock/gmock.h>
#include <graphic/shader/Pass.hpp>
#include <graphic/context/MockPassContext.hpp>
#include <graphic/shader/MockShader.hpp>
#include <graphic/shader/component/pass/MockShaderAttacher.hpp>
#include <graphic/shader/component/pass/MockUniformReader.hpp>
#include <graphic/shader/component/pass/MockUser.hpp>
#include <graphic/shader/component/pass/MockFreer.hpp>
#include <graphic/shader/component/pass/MockLoader.hpp>

namespace cenpy::mock::graphic::shader::opengl
{
    namespace shader = cenpy::graphic::shader;

    template <typename API>
    class MockPass : public shader::Pass<API>
    {
    public:
        MockPass() : shader::Pass<API>({})
        {
        }

        MOCK_METHOD(void, use, (), (override));
        MOCK_METHOD(void, load, (), (override));

        MOCK_METHOD((const std::unordered_map<std::string, std::shared_ptr<shader::Uniform<API>>, collection_utils::StringHash, collection_utils::StringEqual> &), getUniforms, (), (const, override));
        MOCK_METHOD((const std::vector<std::shared_ptr<shader::Shader<API>>> &), getShaders, (), (const, override));
    };
}
