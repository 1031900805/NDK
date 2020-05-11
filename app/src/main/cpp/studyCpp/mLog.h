//
// Created by heweizhen on 2020/5/9.
//

#ifndef NDK_MLOG_H
#define NDK_MLOG_H

#endif //NDK_MLOG_H

class MyInstance {
private:
    static MyInstance *instance;

    MyInstance();

public:
    static MyInstance *getInstance();

    void show();
};

class Student {
public:
    Student();

    ~Student();

private:
    int age;

public:
    void setMyAge(int age);

    void setYouAge(int age) const;

    friend void weAreFriend(Student *);
};

Student::Student() {

}

void Student::setMyAge(int age) {

}

//常量函数 不允许修改值
void Student::setYouAge(int age) const {

}

Student::~Student() {

}

void weAreFriend(Student *) {

}

