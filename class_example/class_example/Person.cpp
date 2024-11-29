#include "Person.h"

// ���캯����ʵ��
Person::Person(const std::string& name, int age) : name(name), age(age) {}

// ��ȡ������ʵ��
std::string Person::getName() const {
    return name;
}

// ��ȡ�����ʵ��
int Person::getAge() const {
    return age;
}

// ����������ʵ��
void Person::setName(const std::string& name) {
    this->name = name;
}

// ���������ʵ��
void Person::setAge(int age) {
    this->age = age;
}
