#include <gtest/gtest.h>
#include <memory>
#include <iostream>
#include <common/pattern/observer/Subject.hpp>
#include <concepts>

// Fake class that will be used as a subject
class FakeClass
{
public:
    int getValue() const
    {
        return m_value;
    }

    int getValue1()
    {
        return m_value;
    }

    void setValue(int newValue)
    {
        m_value = newValue;
    }

    void toggle()
    {
        m_toggle = !m_toggle;
    }

    bool getToggle() const
    {
        return m_toggle;
    }

private:
    int m_value = 0;
    bool m_toggle = false;
};

// Fake observer class
class FakeObserver : public cenpy::common::pattern::observer::Observer<FakeClass>
{
public:
    void update(const FakeClass &data) override
    {
        updatedValue = data.getValue();
        toggle = data.getToggle();
    }

    int getUpdatedValue() const
    {
        return updatedValue;
    }

    bool getToggle() const
    {
        return toggle;
    }

private:
    int updatedValue = 0;
    bool toggle;
};

class FakeClassDelegate : public cenpy::common::pattern::delegate::ClassDelegate<FakeClass>
{
public:
    FakeClassDelegate(std::shared_ptr<FakeClass> instance) : cenpy::common::pattern::delegate::ClassDelegate<FakeClass>(instance, nullptr, nullptr) { init(); }
    FakeClassDelegate(std::shared_ptr<FakeClass> instance, cenpy::common::pattern::delegate::MethodDelegateBase::HookType beforeFunc, cenpy::common::pattern::delegate::MethodDelegateBase::HookType afterFunc) : cenpy::common::pattern::delegate::ClassDelegate<FakeClass>(instance, beforeFunc, afterFunc) { init(); }
    void init()
    {
        auto getValue1 = new cenpy::common::pattern::delegate::MethodDelegate(&FakeClass::getValue1);
        std::shared_ptr<cenpy::common::pattern::delegate::MethodDelegateBase> getValue1Ptr(getValue1);
        auto setValue = new cenpy::common::pattern::delegate::MethodDelegate(&FakeClass::setValue);
        std::shared_ptr<cenpy::common::pattern::delegate::MethodDelegateBase> setValuePtr(setValue);
        auto toggle = new cenpy::common::pattern::delegate::MethodDelegate(&FakeClass::toggle);
        std::shared_ptr<cenpy::common::pattern::delegate::MethodDelegateBase> togglePtr(toggle);
        cenpy::common::pattern::delegate::ClassDelegate<FakeClass>::init({{"getValue1", getValue1Ptr}, {"setValue", setValuePtr}, {"toggle", togglePtr}});
    }
    virtual ~FakeClassDelegate() = default;
    template <typename... Args>
    auto getValue1(Args... args) -> decltype(cenpy::common::pattern::delegate::ClassDelegate<FakeClass>::getInstance()->getValue1(args...))
    {
        auto methodDelegate = dynamic_cast<cenpy::common::pattern::delegate::MethodDelegate<decltype(cenpy::common::pattern::delegate::ClassDelegate<FakeClass>::getInstance()->getValue1(args...)), FakeClass, Args...> *>(getMethod("getValue1").get());
        return (*methodDelegate)(args...);
    }
    template <typename... Args>
    auto setValue(Args... args) -> decltype(cenpy::common::pattern::delegate::ClassDelegate<FakeClass>::getInstance()->setValue(args...))
    {
        auto methodDelegate = dynamic_cast<cenpy::common::pattern::delegate::MethodDelegate<decltype(cenpy::common::pattern::delegate::ClassDelegate<FakeClass>::getInstance()->setValue(args...)), FakeClass, Args...> *>(getMethod("setValue").get());
        return (*methodDelegate)(args...);
    }
    template <typename... Args>
    auto toggle(Args... args) -> decltype(cenpy::common::pattern::delegate::ClassDelegate<FakeClass>::getInstance()->toggle(args...))
    {
        auto methodDelegate = dynamic_cast<cenpy::common::pattern::delegate::MethodDelegate<decltype(cenpy::common::pattern::delegate::ClassDelegate<FakeClass>::getInstance()->toggle(args...)), FakeClass, Args...> *>(getMethod("toggle").get());
        return (*methodDelegate)(args...);
    }
};
class FakeClassSubject : public FakeClassDelegate, public cenpy::common::pattern::observer::Subject<FakeClass>
{
public:
    FakeClassSubject(std::shared_ptr<FakeClass> instance) : cenpy::common::pattern::observer::Subject<FakeClass>(), FakeClassDelegate(instance, nullptr, cenpy::common::pattern::delegate::MethodDelegateBase::HookType(&notifyObserversFor)) { FakeClassDelegate::bind(this); }
    static void notifyObserversFor(const std::any &it) { std::any_cast<FakeClassSubject *>(it)->notifyObservers(); }
    void notifyObservers() override
    {
        for (const auto &observer : cenpy::common::pattern::observer::Subject<FakeClass>::getObservers())
        {
            observer->update(*FakeClassDelegate::getInstance());
        }
    }
};

// Test fixture for the unit tests
class SubjectTest : public testing::Test
{
protected:
    void SetUp() override
    {
        fakeClassInstance = std::make_shared<FakeClass>();
        fakeObserver = std::make_shared<FakeObserver>();
        fakeClassSubject = std::make_shared<FakeClassSubject>(fakeClassInstance);
    }

protected:
    std::shared_ptr<FakeClass> fakeClassInstance;
    std::shared_ptr<FakeObserver> fakeObserver;
    std::shared_ptr<FakeClassSubject> fakeClassSubject;
};

// Unit test for the SUBJECT macro
TEST_F(SubjectTest, ObserverIsNotified)
{
    // Add the fake observer to the subject
    fakeClassSubject->addObserver(fakeObserver);

    // Update the fake class (this should notify the observer)
    fakeClassSubject->setValue(42);

    // Check if the observer was notified with the correct value
    EXPECT_EQ(fakeObserver->getUpdatedValue(), 42);

    // Update the fake class again
    fakeClassSubject->toggle();

    // Check if the observer was notified with the correct value
    EXPECT_EQ(fakeObserver->getToggle(), true);

    EXPECT_EQ(fakeClassSubject->getValue1(), 42);
}
