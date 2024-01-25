// UniformContext.hpp

#pragma once

#include <gmock/gmock.h>
#include <graphic/MockApi.hpp>
#include <graphic/opengl/context/UniformContext.hpp>
#include <graphic/opengl/pipeline/component/uniform/MockSetter.hpp>

namespace cenpy::mock::graphic::opengl::context
{

    class MockUniformContext : public cenpy::graphic::context::UniformContext<graphic::api::MockOpenGL>
    {
    public:
        template <typename T>
        using Setter = opengl::pipeline::component::uniform::MockSetter<T>;

        MOCK_METHOD(void, setUniformID, (GLuint uniformId), ());
        MOCK_METHOD(GLuint, getUniformID, (), (const));
        MOCK_METHOD(void, setGLType, (GLenum type), ());
        MOCK_METHOD(GLenum, getGLType, (), (const));
        MOCK_METHOD(void, setSize, (GLuint size), ());
        MOCK_METHOD(GLuint, getGLSize, (), (const));
    };
}
