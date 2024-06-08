#pragma once 

class FooBar
{
public:
    FooBar() = default;
    ~FooBar() = default;

    void DoFooBar();

private:
    int m_foobar{ 0 };
};