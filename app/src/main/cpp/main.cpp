//
// Created by heweizhen on 2020/5/11.
//
#include "cpplog.h"
#include "../../../../../sdk/ndk/21.1.6352462/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include/android/log.h"

class MyOperator {
public:
    int value;

    MyOperator operator+(const MyOperator &anOperator) {
        MyOperator temp;
        temp.value = this->value + anOperator.value;
        return temp;
    }
};

MyOperator operator-(MyOperator m1, MyOperator m2) {
    return m1 - m2;
}

//void *operator new(size_t size) {
//    return malloc(size);
//}

void operator delete(void *pVoid) {
    LOGD("delete -> 地址是->%#x", pVoid);
}

#include "MyExtends.h"

class FuClass {
public:
    virtual void show() {
        LOGD("父fu show run ");
    }
};

class ZiClass : public FuClass {
public:
    void show() {
        LOGD("子zi show run ");
    }
};

int main() {
    // 使用重载的运算符
    MyOperator myOperator1;
    myOperator1.value = 1000;

    MyOperator myOperator2;
    myOperator2.value = 1000;

    MyOperator myOperator3;
    myOperator3 = myOperator1 + myOperator2;

    Worke worke;
    worke.name = "1";
    //这里使用的是父类的show1方法 静态编译已=号左边为主
    Person *person = new Worke;
    person->show1();
    delete person;

    //会查看父类是否有虚函数
    Person *person1 = new Worke;
    person1->show3();
    delete person1;

    FuClass *fuClass = new FuClass;
    ZiClass *ziClass = static_cast<ZiClass*>(fuClass);
    fuClass->show();
    ziClass->show();
    delete fuClass;

    FuClass *fuClass1 = new ZiClass;
    ZiClass *ziClass1= dynamic_cast<ZiClass*>(fuClass1);
    if(ziClass1){
        LOGD("转换成功");
        ziClass1->show();
    } else{
        LOGD("fail");
    }
    LOGD("running main");
}