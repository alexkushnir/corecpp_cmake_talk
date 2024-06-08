#pragma once

class Foo
{
public:
    Foo() = default;
    ~Foo() = default;

    void DoFoo();

private:
    int m_foo{ 0 };
};