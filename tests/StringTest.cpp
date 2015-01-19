#include "Test.hpp"
#include "utils/String.hpp"

using namespace std;

void stringLengthTest();
void stringReplaceFirstTest();
void stringReplaceTest();
void stringIndexOfTest();
void stringEmptyCtorTest();

int main(int /*argc*/, char** /*argv*/) {
    void (*tests[])(void) = {
        &stringEmptyCtorTest,
        &stringLengthTest,
        &stringIndexOfTest,
        &stringReplaceFirstTest,
        &stringReplaceTest,
    };
    run(tests, sizeof(tests) / sizeof(*tests));

    return 0;
}

void stringEmptyCtorTest() {
    String s;
    assertEquals<unsigned int>(0, s.length());
    assertTrue(s == String(""));
    assertTrue(s == String());
}

void stringLengthTest() {
    assertEquals<unsigned int>(0, String().length());
    assertEquals<unsigned int>(0, String("").length());
    assertEquals<unsigned int>(1, String("a").length());
    assertEquals<unsigned int>(2, String("aa").length());
    String tmp;
    tmp = "";
    assertEquals<unsigned int>(0, tmp.length());
    tmp = "a";
    assertEquals<unsigned int>(1, tmp.length());
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
