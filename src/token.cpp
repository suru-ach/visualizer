#include "token.h"

#include <string>
using std::to_string;

// This is for token creation
string Object::toString() {
    switch(type) {
        case Object_str:
            return str;
        case Object_bool:
            return boolean ? "1" : "0";
        case Object_nil:
            return "nil";
        default:
            return to_string(num);
    }
}

Object Object::make_num_obj(double num) {
    Object num_obj;
    num_obj.num = num;
    num_obj.type = Object_num;
    return num_obj;
}

Object Object::make_str_obj(string str) {
    Object str_obj;
    str_obj.str = str;
    str_obj.type = Object_str;
    return str_obj;
}

Object Object::make_bool_obj(bool boolean) {
    Object bool_obj;
    bool_obj.boolean = boolean;
    bool_obj.type = Object_bool;
    return bool_obj;
}

Object Object::make_nil_obj() {
    Object nil_obj;
    nil_obj.nil = nullptr;
    nil_obj.type = Object_nil;
    return nil_obj;
}

// Token's toString

string Token::toString() {
    return to_string(type) + " " + lexeme + " " + literal.toString();
} 
