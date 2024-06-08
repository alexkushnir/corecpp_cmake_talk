#pragma once 

class Bar
{
public:
    Bar() = default;
    ~Bar() = default;

    void DoBar();

private:
    int m_bar{ 0 };
};