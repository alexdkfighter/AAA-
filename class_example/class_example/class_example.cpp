#include <iostream>
#include "Person.h"

int main() {
    // 创建一个 Person 对象
    Person person("Alice", 30);

    // 输出姓名和年龄
    std::cout << "Name: " << person.getName() << std::endl;
    std::cout << "Age: " << person.getAge() << std::endl;

    // 修改姓名和年龄
    person.setName("Bob");
    person.setAge(25);

    // 输出修改后的姓名和年龄
    std::cout << "Updated Name: " << person.getName() << std::endl;
    std::cout << "Updated Age: " << person.getAge() << std::endl;

    return 0;
}
