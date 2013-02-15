#include <iostream>
#include <vector>
#include "event"
#include "functionhandler"
#include "memberfunctionhandler"

using namespace std;

void plm()
{
    std::cout << "plm called" << std::endl;
}

void plm2(int value)
{
    cout << "plm2 called, value = " << value << endl;
}

void plm3(int value1, int value2)
{
    cout << "plm3 called, values= " << value1 << "," << value2 << endl;
}

class A
{
public:
    void plm() { cout << "A::plm called" << endl; }
    void plm2(int value) { cout << "A::plm2 called, value= " << value << endl; }
    void plm3(int value1, int value2) { cout << "A::plm3 called, values= " << value1 << "," << value2 << endl; }
};

int main()
{
    A a;

    Event<> myEvent;
    myEvent += newFunctionHandler(&plm);
    myEvent += newMethodHandler(a, &A::plm);
    // Launch
    myEvent();

    Event<int> anotherEvent;
    anotherEvent += newFunctionHandler(&plm2);
    anotherEvent += newMethodHandler(a, &A::plm2);
    // Launch
    anotherEvent(7);

    Event<int, int> yetAnotherEvent;
    yetAnotherEvent += newFunctionHandler(&plm3);
    yetAnotherEvent += newMethodHandler(a, &A::plm3);
    // Launch
    yetAnotherEvent(7, 13);

    Event<int, int> event4;
    event4 += newFunctionHandler(&plm3);
    event4 += newMethodHandler(a, &A::plm3);
    // Launch
    event4(7, 13);

    Event<int, int, int> event5;

    return 0;
}
