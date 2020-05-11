//
// Created by heweizhen on 2020/5/11.
//
#include <iostream>
#include "cpplog.h"
#include "../../../../../sdk/ndk/21.1.6352462/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include/android/log.h"

#ifndef NDK_MYEXTENDS_H
#define NDK_MYEXTENDS_H

#endif //NDK_MYEXTENDS_H

class Person {
private:
    int age;
    int sex;

public:
    char *name = "99788";

    void show1() {
        LOGD("show1 invoke");
    }

    virtual void show2() {
        LOGD("show2 invoke virtual");
    }

    //纯虚函数 相当于抽象方法
    virtual void show3() = 0;
};

//公开继承才可以获取父类东西  private默认的 不可获取
class Worke : public Person {
public:
    void show1() {
        LOGD("stub show1 invoke");
    }

    void show3() {
        LOGD("stub show3 invoke");
    }
};