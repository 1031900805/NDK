package com.example.ndk;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;

import com.example.ndk.bean.Person;

import org.greenrobot.eventbus.EventBus;
import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class JavaActivity extends AppCompatActivity {

    public static boolean returnThis = false;

    public static Person[] people = new Person[4];

    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_java);

        returnThis = true;
        EventBus.getDefault().register(this);

        doTest();

        Log.d("99788",getInfo("978"));
    }

    private static final Map<String, Person> METHOD_CACHE = new ConcurrentHashMap<>();

    private void doTest() {
        Person per = new Person("1", 2);
        METHOD_CACHE.put("xx",per);
        per.setAge(3);

        Person xx = METHOD_CACHE.get("xx");
        Log.d("99788",xx.toString());
    }

    @Subscribe(threadMode = ThreadMode.MAIN, sticky = true)
    public void onEvent(Person event) {
        Log.d("99788",getInfo("978"));
    }

    @Override
    protected void onStart() {
        super.onStart();
        returnThis = true;
    }

    @Override
    protected void onRestart() {
        super.onRestart();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        returnThis = false;
    }

    public native String getInfo(String string);
}
