// AttributeContext.hpp

#pragma once

#include <gmock/gmock.h>
#include <graphic/MockApi.hpp>
#include <graphic/context/AttributeContext.hpp>

namespace cenpy::mock::graphic
{
    namespace pipeline::opengl::component::attribute
    {
        struct MockBinder;
        template <typename A>
        struct MockSetter;
        struct MockUnbinder;

    }

    namespace opengl::context
    {
        template <typename API>
        class MockAttributeContext : public cenpy::graphic::context::AttributeContext<API>
        {
        public:
            using Binder = pipeline::opengl::component::attribute::MockBinder;
            template <typename A>
            using Setter = pipeline::opengl::component::attribute::MockSetter<A>;
            using Unbinder = pipeline::opengl::component::attribute::MockUnbinder;

            MOCK_METHOD(void, setAttributeID, (GLuint attributeId), ());
            MOCK_METHOD(GLuint, getAttributeID, (), (const));
            MOCK_METHOD(void, setGLType, (GLenum type), ());
            MOCK_METHOD(GLenum, getGLType, (), (const));
            MOCK_METHOD(void, setSize, (GLuint size), ());
            MOCK_METHOD(GLuint, getGLSize, (), (const));
            MOCK_METHOD(void, setBufferID, (GLuint bufferId), ());
            MOCK_METHOD(GLuint, getBufferID, (), (const));
        };
    }
}