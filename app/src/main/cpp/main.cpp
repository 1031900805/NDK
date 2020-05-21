//
// Created by heweizhen on 2020/5/11.
//
#include "cpplog.h"
#include "../../../../../sdk/ndk/21.1.6352462/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include/android/log.h"
#include <string>
#include <iostream>
#include <pthread.h>


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
#include "exception.h"

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

class CustomeEx {
public:
    char *getMsg() {
        return "自定义异常";
    }
};

void exceptionMethod() {
    CustomeEx customeEx;
    throw customeEx;
}

class CustomeExce : public exception {

};

/**
 *
 * @param param   void * 可接受任何类型的参数
 * @return
 */
void *customPThtreadMethod(void *param) {

    int num = *static_cast<int *>(param);
    printf("num->%d", num);

    for (int i = 0; i < 100; ++i) {
        LOGD("customPThtreadMethod->invoke");
    }
    return 0;
}

using namespace std;

/**
 * 线程相关测试
 */
void threadTest() {
/**
     * PTW32_DLLPORT int PTW32_CDECL pthread_create (pthread_t * tid, 1.线程ID
                            const pthread_attr_t * attr,  2.线程属性
                            void *(PTW32_CDECL *start) (void *),  3.函数指针 ---> 异步任务 java run
                            void *arg); 4.函数指针的参数传递
     */
    pthread_t pthreadID;
    int value = 99788;

    pthread_create(&pthreadID, 0, customPThtreadMethod, &value);
    //将另一个线程join到主线程中 主线程会等待这个线程执行完毕 才执行
    //如果不join main()结束 不管这个线程 结束不结束  就都结束了
    pthread_join(pthreadID, 0);
}

int main() {



//    threadTest();

    try {
        exceptionMethod();
    } catch (CustomeEx ex) {
        LOGD("异常捕获_>");
//        std::cout << "99788 异常捕获_>" << ex.getMsg() << std::endl;
    }


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
    ZiClass *ziClass = static_cast<ZiClass *>(fuClass);
    fuClass->show();
    ziClass->show();
    delete fuClass;

    FuClass *fuClass1 = new ZiClass;
    ZiClass *ziClass1 = dynamic_cast<ZiClass *>(fuClass1);
    if (ziClass1) {
        LOGD("转换成功");
        ziClass1->show();
    } else {
        LOGD("fail");
    }
    LOGD("running main");
}