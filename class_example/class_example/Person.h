#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person {
    public:
        // 构造函数
        Person(const std::string& name, int age);

        // 获取姓名
        std::string getName() const;

        // 获取年龄
        int getAge() const;

        // 设置姓名
        void setName(const std::string& name);

        // 设置年龄
        void setAge(int age);


    private:
        std::string name;//姓名变量
        int age;
};

#endif // PERSON_H
