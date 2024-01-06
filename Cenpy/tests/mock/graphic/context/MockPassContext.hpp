// PassContext.hpp

#pragma once

#include <graphic/MockApi.hpp>
#include <graphic/context/PassContext.hpp>
#include <graphic/shader/component/pass/MockLoader.hpp>
#include <graphic/shader/component/pass/MockFreer.hpp>
#include <graphic/shader/component/pass/MockShaderAttacher.hpp>
#include <graphic/shader/component/pass/MockUniformReader.hpp>
#include <graphic/shader/component/pass/MockUser.hpp>

namespace cenpy::mock::graphic
{
    namespace opengl::context
    {
        class MockPassContext : public cenpy::graphic::context::PassContext<graphic::api::MockOpenGL>
        {
        public:
            using Loader = shader::opengl::component::pass::MockLoader;
            using Freer = shader::opengl::component::pass::MockFreer;
            using ShaderAttacher = shader::opengl::component::pass::MockShaderAttacher;
            using UniformReader = shader::opengl::component::pass::MockUniformReader;
            using User = shader::opengl::component::pass::MockUser;
        };
    }
}