package netease.com.jnisot;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;

import static netease.com.jnisot.Ap.hook;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";
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

    }


    public void TestMethod()
    {
        Log.d(TAG, "Bug Method！！！");
    }
}
