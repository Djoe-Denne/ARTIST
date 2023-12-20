
#pragma once

#include <gmock/gmock.h>
#include <graphic/shader/Uniform.hpp>

namespace cenpy::mock::graphic::shader
{
    using namespace cenpy::graphic::shader;

    class MockUniform;

    template <typename U>
    struct mockUniformSetter : baseSetter<MockUniform, U>
    {
    };

    /**
     * @brief Specialization for GLfloat with corresponding setter
     */
    template <>
    struct mockUniformSetter<float> : std::true_type
    {
        static constexpr auto set =
            [](const MockUniform &uniform)
        { glUniform1f(1, 3.14f); };
    };

    class MockUniform : public BaseUniform
    {
    public:
        MockUniform(GLuint location, GLenum type, GLint size) : BaseUniform()
        {
        }
    };

} // namespace cenpy::graphic::shader
