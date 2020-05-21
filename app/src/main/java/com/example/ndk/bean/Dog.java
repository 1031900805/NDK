package com.example.ndk.bean;

import android.util.Log;

/**
 * @author zwq 2020/5/21
 * @describe :
 */
public class Dog {

    private String name;
    private int age;

    public Dog() {
        Log.d("99788", "Dog: 构造方法被C++中直接实例化了....");
    }

    public Dog(String name, int age) {
        this.name = name;
        this.age = age;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    @Override
    public String toString() {
        return "Dog{" +
                "name='" + name + '\'' +
                ", age=" + age +
                '}';
    }
}
