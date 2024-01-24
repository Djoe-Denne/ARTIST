#pragma once

#include <memory>
#include <graphic/Api.hpp>
#include <graphic/context/AttributeContext.hpp>
#include <graphic/validator/ComponentConcept.hpp>

namespace cenpy::graphic::pipeline
{

    template <typename API>
    class IAttribute
    {
    public:
        // Constructor
        IAttribute(std::shared_ptr<typename API::AttributeContext> context)
            : m_context(context) {}

        IAttribute() : IAttribute(std::make_shared<typename API::AttributeContext>())
        {
        }

        void bind()
        {
            bind(m_context);
        }

        template <typename T>
        void set(std::shared_ptr<T> value)
        {
            m_context->template setValue<T>(value);

            if constexpr (graphic::validator::HasComponent<typename API::AttributeContext::Setter<std::shared_ptr<int>>>)
            {
                API::AttributeContext::template Setter<std::shared_ptr<int>>::on(m_context);
            }
            else
            {
                throw common::exception::TraceableException<std::runtime_error>("ERROR::ATTRIBUTE::UNSUPPORTED_TYPE");
            }
        }

        void unbind()
        {
            unbind(m_context);
        }

        [[nodiscard]] virtual std::shared_ptr<typename API::AttributeContext> getContext() const
        {
            return m_context;
        }

    protected:
        virtual void unbind(std::shared_ptr<typename API::AttributeContext> context) = 0;
        virtual void bind(std::shared_ptr<typename API::AttributeContext> context) = 0;

    private:
        std::shared_ptr<typename API::AttributeContext> m_context;
    };

    template <typename API, auto PROFILE>
        requires(API::Validator::template validateAttribute<API, PROFILE>())
    class Attribute : public IAttribute<API>
    {
    public:
        using IAttribute<API>::IAttribute;
        using IAttribute<API>::bind;
        using IAttribute<API>::unbind;
        using IAttribute<API>::set;

    protected:
        void bind(std::shared_ptr<typename API::AttributeContext> context) override
        {
            if constexpr (graphic::validator::HasComponent<typename API::AttributeContext::Binder<PROFILE>>)
            {
                API::AttributeContext::template Binder<PROFILE>::on(context);
            }
        }

        void unbind(std::shared_ptr<typename API::AttributeContext> context) override
        {
            if constexpr (graphic::validator::HasComponent<typename API::AttributeContext::Unbinder<PROFILE>>)
            {
                API::AttributeContext::template Unbinder<PROFILE>::on(context);
            }
        }
    };
}
