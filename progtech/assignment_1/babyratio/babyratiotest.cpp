#include <iostream>
#include "babyratio.hpp"

using namespace std;
int main() {
    rational a(1633, 6629);
    rational b(4356, 4229 );
    a.add(b).print();
    cout << endl;
    return 0;
}
