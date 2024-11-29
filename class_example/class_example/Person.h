#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person {
    public:
        // ���캯��
        Person(const std::string& name, int age);

        // ��ȡ����
        std::string getName() const;

        // ��ȡ����
        int getAge() const;

        // ��������
        void setName(const std::string& name);

        // ��������
        void setAge(int age);


    private:
        std::string name;//��������
        int age;
};

#endif // PERSON_H
