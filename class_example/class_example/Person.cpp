#include "Person.h"

// 构造函数的实现
Person::Person(const std::string& name, int age) : name(name), age(age) {}

// 获取姓名的实现
std::string Person::getName() const {
    return name;
}

// 获取年龄的实现
int Person::getAge() const {
    return age;
}

// 设置姓名的实现
void Person::setName(const std::string& name) {
    this->name = name;
}

// 设置年龄的实现
void Person::setAge(int age) {
    this->age = age;
}
