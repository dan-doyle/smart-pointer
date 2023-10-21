#include <iostream>

using namespace std;

template <typename T>
class myshared {
    private:
        long *ref_count; // count of shared must be in dynamic memory and each instance of class shares acces
        T* ptr;
    public:
        myshared(T *ptr_) : ptr(ptr_) {
            ref_count = new long(1);
        }

        // Copy constructor
        // const ensures the 'other' object we pass in cannot be copied, we pass by reference for efficiency
        myshared(const myshared& other) {
            // A new object is created so here we make it identical to the 'other' instance
            ref_count = other.ref_count;
            *ref_count += 1;
            ptr = other.ptr;
        }

        // Destructor
        ~myshared() {
            *ref_count -= 1;
            if(*ref_count == 0) {
                delete ptr;
                delete ref_count;
            }
        }

        // overload assignment operator
        myshared& operator=(const myshared& other) {
            // we have access to the myshared object we are assigning since this operator is a method!
            *ref_count += 1;
            ptr = other.ptr;
            return *this;
        }

        T* operator->() {
            // implementing this, the operator overload is called first and then, after, '->' actually runs. We see its functionality in main
            return ptr;
        }
        T& operator*() {
            return *ptr;
        }
};

class Foo {
public:
    void bar() {
        std::cout << "Inside Foo::bar()" << std::endl;
    }
};