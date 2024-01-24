#pragma once
#include <memory>
#include <type_traits>
#include <graphic/validator/ComponentConcept.hpp>

namespace cenpy::graphic::opengl::validator
{
    using cenpy::graphic::validator::HasComponent;
    using cenpy::graphic::validator::HasOnMethod;

    template <typename API, auto PROFILE>
    concept OpenGLAttributeFlow = requires {
        requires HasComponent<typename API::AttributeContext::Binder<PROFILE>>;
        requires HasComponent<typename API::AttributeContext::Unbinder<PROFILE>>;
        requires HasComponent<typename API::AttributeContext::template Setter<int>>;

        requires HasOnMethod<typename API::AttributeContext::Binder<PROFILE>, typename API::AttributeContext>;
        requires HasOnMethod<typename API::AttributeContext::Unbinder<PROFILE>, typename API::AttributeContext>;
        requires HasOnMethod<typename API::AttributeContext::template Setter<int>, typename API::AttributeContext>;
    };
}