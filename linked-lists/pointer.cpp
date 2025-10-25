#include <iostream>
using namespace std;

int main()
{
    int a = 10;  // normal integer variable
    int *p = &a; // pointer storing the ADDRESS of variable a

    cout << "Value of a: " << a << endl;
    cout << "Address of a: " << &a << endl;
    cout << "Value stored in pointer p: " << p << endl;
    cout << "Value pointed by p: " << *p << endl;

    return 0;
}
