package com.example.ndk

import android.content.Intent
import android.os.Bundle
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.example.ndk.bean.Person
import kotlinx.android.synthetic.main.activity_main.*
import org.greenrobot.eventbus.EventBus

class MainActivity : AppCompatActivity() {
    companion object {
        init {
            System.loadLibrary("native-lib")
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        sample_text.text = stringFromJNI()

        btn_toJava.setOnClickListener { startActivity(Intent(this, JavaActivity::class.java)) }

        btn_jni.setOnClickListener { startActivity(Intent(this,JNIActivity::class.java)) }

        Toast.makeText(this, "${test(10, 15)}", Toast.LENGTH_SHORT).show()

        testType(
            true, 1, '1', 1, 1, 1f, 1.1, "str", 1,
            IntArray(1), arrayOf("x"), BooleanArray(1),
            Person("name", 18)
        )

        btn_test_mode.setOnClickListener {
            startActivity(Intent(this, JavaActivity::class.java))
        }

        EventBus.getDefault().postSticky(Person("", 1))
    }

    override fun onDestroy() {
        super.onDestroy()
        EventBus.getDefault().unregister(this)
    }

    private external fun stringFromJNI(): String

    external fun test(int1: Int, int2: Int): Boolean

    external fun testType(
        boolean: Boolean,
        byte: Byte,
        char: Char,
        short: Short,
        long: Long,
        float: Float,
        double: Double,
        string: String,
        int: Int,
        intArray: IntArray,
        stringArray: Array<String>,
        booleanArray: BooleanArray,
        person: Person
    )
}
