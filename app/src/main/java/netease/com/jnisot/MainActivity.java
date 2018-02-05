package netease.com.jnisot;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;

import java.lang.reflect.Method;

import static netease.com.jnisot.Ap.hook;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";

    final public  void f1()
    {
        Log.d(TAG, "f1: before hook");
    }
    final public  void f2()
    {
        Log.d(TAG, "f1: after hook");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        findViewById(R.id.changeHook).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                hook(getApplicationContext());
            }
        });

        findViewById(R.id.sample_text).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                TestMethod();

                try {
                    Log.d(TAG, MainActivity.class.getDeclaredMethod("onCreate").getName());
                } catch (NoSuchMethodException e) {
                    e.printStackTrace();
                }
            }
        });

        try {
            f1();
            Method f1M = MainActivity.class.getDeclaredMethod("f1");
            Method f2M = MainActivity.class.getDeclaredMethod("f2");
            showArtMethodSize(f1M, f2M);
            f1();
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        }

    }

    public native void showArtMethodSize(Method src, Method dest);

    public void TestMethod()
    {
        Log.d(TAG, "Bug Method！！！");
    }
}
