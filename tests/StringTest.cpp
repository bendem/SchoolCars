#include "Test.hpp"
#include "utils/String.hpp"

using namespace std;

void stringLengthTest();
void stringReplaceFirstTest();
void stringReplaceTest();
void stringIndexOfTest();
void stringEmptyCtorTest();
void stringCharIntCtorTest();
void stringStringIntCtorTest();
void stringCharCtorTest();

int main(int /*argc*/, char** /*argv*/) {
    void (*tests[])(void) = {
        &stringEmptyCtorTest,
        &stringCharIntCtorTest,
        &stringStringIntCtorTest,
        &stringCharCtorTest,
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
    assertTrue(s.isEmpty());
}

void stringCharIntCtorTest() {
    String empty('c', 0);
    String ccc('c', 3);
    assertTrue(empty.isEmpty());
    assertEquals(String("ccc"), ccc);
}

void stringStringIntCtorTest() {
    String empty("a", 0);
    String ccc("c", 3);
    String acacac("ac", 3);
    assertTrue(empty.isEmpty());
    assertEquals(String("ccc"), ccc);
    assertEquals(String("acacac"), acacac);
}

void stringCharCtorTest() {
    String a("a");
    assertEquals(0, strcmp("a", a));
    String ab("ab");
    assertEquals(0, strcmp("ab", ab));
    assertFalse(strcmp(a, ab) == 0);
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
