#include "Test.hpp"
#include "utils/String.hpp"

using namespace std;

void stringReplaceFirstTest();
void stringReplaceTest();
void stringIndexOfTest();

int main(int /*argc*/, char** /*argv*/) {
    void (*tests[])(void) = {
        &stringIndexOfTest,
        &stringReplaceFirstTest,
        &stringReplaceTest,
    };
    run(tests, sizeof(tests) / sizeof(*tests));

    return 0;
}

void stringIndexOfTest() {
    String tmp("abcdefgabcdefg");
    assertEquals(0, tmp.indexOf("a"));
    assertEquals(0, tmp.indexOf("ab"));
    assertEquals(0, tmp.indexOf("abc"));
    assertEquals(4, tmp.indexOf("e"));
    assertEquals(4, tmp.indexOf("efg"));
    assertEquals(-1, tmp.indexOf("z"));
    assertEquals(-1, tmp.indexOf("z"));
    assertEquals(-1, tmp.indexOf("zae"));
    assertEquals(-1, tmp.indexOf("ae"));
}

void stringReplaceFirstTest() {
    String tmp("abcdefg");

    assertEquals<String>("abcdezz", tmp.replaceFirst("fg", "zz"));
    assertEquals<String>("zzcdefg", tmp.replaceFirst("ab", "zz"));
    assertEquals<String>("zzbcdefg", tmp.replaceFirst("a", "zz"));
    assertEquals<String>("zcdefg", tmp.replaceFirst("ab", "z"));
    assertEquals<String>("abcdefg", tmp);
}

void stringReplaceTest() {
    String tmp("abcabcabc");
    assertEquals<String>("aaa", tmp.replace("abc", "a"));
    assertEquals<String>("abcabcabc", tmp);
}
