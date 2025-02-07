#include<iostream>

class Base
{
  protected:
    int m_value;

  public:
    Base(int value)
      : m_value(value)
    {
    }

    virtual const char* getName() const { return "Base"; }
    int getValue() const { return m_value; }
};

class Derived: public Base
{
  public:
    Derived(int value)
      : Base(value)
    {
    }

    virtual const char* getName() const { return "Derived"; }
};

int main()
{
  Derived derived(5);
  std::cout << "derived is a " << derived.getName() << " and has value " << derived.getValue() << '\n';

  Base &ref = derived;
  std::cout << "ref is a " << ref.getName() << " and has value " << ref.getValue() << '\n';

  Base *ptr = &derived;
  std::cout << "ptr is a " << ptr->getName() << " and has value " << ptr->getValue() << '\n';

  while (1)
  {
    std::cout << " Watch the statement." << ptr;
  }
  

  return 0;
}
