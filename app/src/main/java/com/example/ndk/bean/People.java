package com.example.ndk.bean;

import android.util.Log;

/**
 * @author zwq 2020/5/21
 * @describe :
 */
public class People {
    private static final String TAG = People.class.getSimpleName()+"99788";

    public void setStudent(Dog student) {
        Log.d(TAG, "setStudent: " + student.toString());
    }
}
