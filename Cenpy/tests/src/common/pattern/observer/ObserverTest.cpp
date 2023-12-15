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

SUBJECT(FakeClass, getValue1, setValue, toggle)

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
