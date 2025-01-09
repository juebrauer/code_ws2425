#include <iostream>

class A
{
    public:
        A(int value) {
            important_value = value;
            std::cout << "constructor called.\n";
        }

        ~A() {
            std::cout << "destructor called.\n";
        }

    private:

        int important_value;

};


int main()
{
    //A a1(42);
    A* a1 = new A(42);
    delete a1;
}