#include <iostream>
#include <stdexcept>
#include <sstream>

class AssertionFail : public std::exception {
private:
    const std::string error;
public:
    AssertionFail(const std::string& error) throw() : error(error) {}
    ~AssertionFail() throw() {}
    const char* what() throw() { return this->error.c_str(); }
};

static int assertionCount = 0;

template<class T>
void assertEquals(const T& expected, const T& value, const char* file = "?", int line = -1) {
    ++assertionCount;
    if(expected != value) {
        std::ostringstream ss;
        ss << "Expected <" << expected << ">, got <" << value << "> instead (" << file << ':' << line << ')';
        throw AssertionFail(ss.str());
    }
}

void assertTrue(bool b, const char* file, int line)  { assertEquals(true,  b, file, line); }
void assertFalse(bool b, const char* file, int line) { assertEquals(false, b, file, line); }
#define assertTrue(x) assertTrue((x), __FILE__, __LINE__)
#define assertFalse(x) assertFalse((x), __FILE__, __LINE__)

void run(void (*tests[])(void), unsigned int count) {
    unsigned int fails = 0;
    unsigned int errors = 0;
    std::cout << std::endl;
    for(unsigned int i = 0; i < count; ++i) {
        try {
            tests[i]();
            std::cout << " v | Test " << i << ": success" << std::endl;
        } catch(AssertionFail e) {
            ++fails;
            std::cerr << " x | Test " << i << ": failed assertion: " << e.what() << std::endl;
        } catch(std::exception) {
            ++errors;
            std::cerr << " x | Test " << i << ": error" << std::endl;
        }
    }
    std::cout << "   |" << std::endl << "   | => "
        << count << " test executed, "
        << assertionCount << " assertions, "
        << fails << " failed tests, "
        << errors << " errored tests."
        << std::endl << std::endl;
}
