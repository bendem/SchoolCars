#ifndef CODEPREDICATE_HPP
#define CODEPREDICATE_HPP

#include "Option.hpp"
#include "utils/Predicate.hpp"

class CodePredicate : public Predicate<Option> {

private:
    String code;

public:
    CodePredicate(const String& code) : code(code) {}
    bool test(const Option& param) const { return param.getCode() == this->code; }

};

#endif
