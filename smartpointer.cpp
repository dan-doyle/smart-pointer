#include <iostream>

using namespace std;

template <typename T>
class myshared {
    private:
        long *ref_count; // count of shared must be in dynamic memory and each instance of class shares acces
        T* ptr;
    public:
        myshared(T *ptr_) : ptr(ptr_) { // receives a pointer to an object allocated on the stack
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
            // the object's previous assignment may be it's only one
            if (this != &other) {
                (*ref_count)--;
                if(*ref_count == 0) {
                    delete ptr;
                    delete ref_count;
                }
                // we have access to the myshared object we are assigning since this operator is a method!
                ref_count = other.ref_count;
                (*ref_count)++;
                ptr = other.ptr;
                return *this;
            }
            // else we are assigning to itself and the ref count does not change
        }
        // Overload * operator
        T* operator->() {
            // implementing this, the operator overload is called first and then, after, '->' actually runs. We see its functionality in main
            return ptr;
        }
        // Overload & operator
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

int main() {
    // Create a shared pointer to a Foo object
    myshared<Foo> p(new Foo);

    // Use the -> operator to access the member function of the underlying object
    p->bar();

    myshared<int> d(new int(9));
    cout << "Should print 9: " << *d << endl;

    myshared<int> e(new int(8));
    d = e;
    cout << "Should print 8: " << *d << endl;
}