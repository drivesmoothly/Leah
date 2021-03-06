#include <iostream>
#include "event"
#include "functionhandler"
#include "methodhandler"

using namespace std;

void plm0()
{
    std::cout << "plm0 called" << std::endl;
}

void plm1(int value)
{
    cout << "plm1 called, value = " << value << endl;
}

void plm2(int value1, int value2)
{
    cout << "plm2 called, values= " << value1 << "," << value2 << endl;
}

class A
{
public:
    void plm0()
    {
        cout << "A::plm0 called" << endl;
    }
    void plm1(int value)
    {
        cout << "A::plm1 called, value= " << value << endl;
    }
    void plm2(int value1, int value2)
    {
        cout << "A::plm2 called, values= " << value1 << "," << value2 << endl;
    }
};

int main()
{
    // An object to call the handlers on.
    A a;

    // Declare the event
    Event<> myEvent1;
    // Register handlers
    myEvent1 += newHandler(&plm0);
    myEvent1 += newHandler(a, &A::plm0);
    // Raise the event
    myEvent1();

    cout << endl << "remove a handler" << endl;

    // Remove a handler
    myEvent1 -= newHandler(&plm0);
    // Raise the event
    myEvent1();

    cout << endl;

    // Declare the event
    Event<int> myEvent2;
    // Register handlers
    myEvent2 += newHandler(&plm1);
    myEvent2 += newHandler(a, &A::plm1);
    // Raise the event
    myEvent2(7);

    cout << endl;

    // Declare the event
    Event<int, int> myEvent3;
    // Register handlers
    myEvent3 += newHandler(&plm2);
    myEvent3 += newHandler(a, &A::plm2);
    // Raise the event
    myEvent3(7, 13);

    return 0;
}
