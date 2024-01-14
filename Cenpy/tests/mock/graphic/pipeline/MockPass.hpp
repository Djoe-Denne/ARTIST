#pragma once

#include <gmock/gmock.h>
#include <graphic/pipeline/Pass.hpp>
#include <graphic/context/MockPassContext.hpp>
#include <graphic/pipeline/MockShader.hpp>
#include <graphic/pipeline/component/pass/MockShaderAttacher.hpp>
#include <graphic/pipeline/component/pass/MockUniformReader.hpp>
#include <graphic/pipeline/component/pass/MockUser.hpp>
#include <graphic/pipeline/component/pass/MockFreer.hpp>
#include <graphic/pipeline/component/pass/MockLoader.hpp>

namespace cenpy::mock::graphic::pipeline::opengl
{
    namespace pipeline = cenpy::graphic::pipeline;

    template <typename API>
    class MockPass : public pipeline::Pass<API>
    {
    public:
        MockPass() : pipeline::Pass<API>({})
        {
        }

        MOCK_METHOD(void, use, (), (override));
        MOCK_METHOD(void, load, (), (override));

        MOCK_METHOD((const std::unordered_map<std::string, std::shared_ptr<pipeline::Uniform<API>>, collection_utils::StringHash, collection_utils::StringEqual> &), getUniforms, (), (const, override));
        MOCK_METHOD((const std::vector<std::shared_ptr<pipeline::Shader<API>>> &), getShaders, (), (const, override));
    };
}
