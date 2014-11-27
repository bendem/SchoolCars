#include <iostream>

#include "utils/String.hpp"

using namespace std;

int main() {
    String a("test");
    cout << "one worked" << endl;
    String b('a', 5);
    cout << "the other worked" << endl;
    cout << "'" << a << "' '" << b << "'" << endl;
    cout << ((a + b + ' ') + 3) + " hello" << endl;
    cout << "'" << a << "' '" << b << "'" << endl;
    String c = b + -5 + a;
    cout << c << endl;
    cout << a.length() << b.length() << c.length();
    c = "hey";
    cout << c << endl;

    cout << (String("a") == String("a") ? "true" : "false") << endl;
    cout << (String("a") == String("b") ? "true" : "false") << endl;

    cout << (String("a") < String("a") ? "true" : "false") << endl;
    cout << (String("a") < String("b") ? "true" : "false") << endl;

    cout << (String("a") > String("a") ? "true" : "false") << endl;
    cout << (String("a") > String("b") ? "true" : "false") << endl;
    cout << (String("c") > String("b") ? "true" : "false") << endl;

    cout << String(String(String(String("hello")+1)+2)+3) << endl;

    String d, e, f, g, h, i, j;
    d = e = f= g = h = i = j = String("hello!");

    cout << d << e << f << g << h << i << j << endl;

    return 0;
}
