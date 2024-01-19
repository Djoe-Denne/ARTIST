#pragma once

#include <memory>
#include <graphic/pipeline/component/attribute/Binder.hpp>
#include <graphic/pipeline/component/attribute/Setter.hpp>
#include <graphic/pipeline/component/attribute/Unbinder.hpp>

namespace cenpy::graphic::pipeline
{

    template <typename API>
    class Attribute
    {
    public:
        // Constructor
        Attribute(std::shared_ptr<typename API::AttributeContext::Binder> binder,
                  std::shared_ptr<typename API::AttributeContext::Unbinder> unbinder,
                  std::shared_ptr<typename API::AttributeContext> context)
            : m_binder(binder), m_unbinder(unbinder), m_context(context) {}

        Attribute() : Attribute(std::make_shared<typename API::AttributeContext::Binder>(),
                                std::make_shared<typename API::AttributeContext::Unbinder>(),
                                std::make_shared<typename API::AttributeContext>())
        {
        }

        Attribute(std::shared_ptr<typename API::AttributeContext> context) : Attribute(std::make_shared<typename API::AttributeContext::Binder>(),
                                                                                       std::make_shared<typename API::AttributeContext::Unbinder>(),
                                                                                       context)
        {
        }

        void bind()
        {
            if (m_binder)
            {
                m_binder->bind(m_context);
            }
        }

        template <typename T>
        void set(std::shared_ptr<T> value)
        {
            m_context->template setValue<T>(value);
            API::AttributeContext::template Setter<std::shared_ptr<T>>::set(m_context);
        }

        void unbind()
        {
            if (m_unbinder)
            {
                m_unbinder->unbind(m_context);
            }
        }

        [[nodiscard]] virtual std::shared_ptr<typename API::AttributeContext> getContext() const
        {
            return m_context;
        }

    protected:
        [[nodiscard]] virtual std::shared_ptr<typename API::AttributeContext::Binder> getBinder() const
        {
            return m_binder;
        }

        [[nodiscard]] virtual std::shared_ptr<typename API::AttributeContext::Unbinder> getUnbinder() const
        {
            return m_unbinder;
        }

    private:
        std::shared_ptr<typename API::AttributeContext::Binder> m_binder;
        std::shared_ptr<typename API::AttributeContext::Unbinder> m_unbinder;
        std::shared_ptr<typename API::AttributeContext> m_context;
    };
}
