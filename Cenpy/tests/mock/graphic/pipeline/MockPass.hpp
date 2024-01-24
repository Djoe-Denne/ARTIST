#pragma once

#include <gmock/gmock.h>
#include <graphic/pipeline/MockShader.hpp>
#include <graphic/opengl/context/MockPassContext.hpp>
#include <graphic/opengl/pipeline/component/pass/MockShaderAttacher.hpp>
#include <graphic/opengl/pipeline/component/pass/MockUniformReader.hpp>
#include <graphic/opengl/pipeline/component/pass/MockAttributeReader.hpp>
#include <graphic/opengl/pipeline/component/pass/MockUser.hpp>
#include <graphic/opengl/pipeline/component/pass/MockFreer.hpp>
#include <graphic/opengl/pipeline/component/pass/MockLoader.hpp>
#include <graphic/pipeline/Pass.hpp>

namespace cenpy::mock::graphic::pipeline::opengl
{
    namespace pipeline = cenpy::graphic::pipeline;

    template <typename API>
    class MockPass : public pipeline::IPass<API>
    {
    public:
        MockPass() : pipeline::IPass<API>({})
        {
        }

        MOCK_METHOD(void, use, (), (override));
        MOCK_METHOD(void, load, (), (override));

        MOCK_METHOD((const std::unordered_map<std::string, std::shared_ptr<pipeline::Uniform<API>>, collection_utils::StringHash, collection_utils::StringEqual> &), getUniforms, (), (const, override));
        MOCK_METHOD((const std::vector<std::shared_ptr<pipeline::IShader<API>>> &), getShaders, (), (const, override));

    protected:
        MOCK_METHOD(void, readUniforms, (std::shared_ptr<typename API::PassContext> context), (override));
        MOCK_METHOD(void, free, (std::shared_ptr<typename API::PassContext> context), (override));
        MOCK_METHOD(void, use, (std::shared_ptr<typename API::PassContext> context), (override));
        MOCK_METHOD(void, load, (std::shared_ptr<typename API::PassContext> context), (override));

        MOCK_METHOD((std::shared_ptr<pipeline::IPass<API>>), shared, (), (const, override));
    };
}
