package netease.com.jnisot;

import android.app.Application;
import android.content.Context;

import java.io.File;
import java.io.IOException;
import java.lang.reflect.Method;

import dalvik.system.DexFile;

/**
 * Created by shs1330 on 2018/2/1.
 */

public class Ap extends Application {
    private static final String TAG = "MainActivity";

    @Override
    public void onCreate() {
        super.onCreate();
    }

    public static void hook(Context context)
    {
        FileHelper.extractAssets(context, "Hello.apk");

        File dexFile = context.getFileStreamPath("Hello.apk");
        File optDexFile = context.getFileStreamPath("Hello.dex");

        DexFile file = null;
        try {
            file = DexFile.loadDex(dexFile.getAbsolutePath(), optDexFile.getAbsolutePath(), Context.MODE_PRIVATE);
        } catch (IOException e) {
            e.printStackTrace();
        }

        final DexFile finalFile = file;

        ClassLoader patchClassLoader = new ClassLoader(context.getClassLoader()) {
            @Override
            protected Class<?> findClass(String className)
                    throws ClassNotFoundException {
                Class<?> clazz = finalFile.loadClass(className, this);
                if (clazz == null) {
                    throw new ClassNotFoundException(className);
                }
                return clazz;
            }
        };

        Class<?> ZhangActivityClass = finalFile.loadClass("ZhangActivity", patchClassLoader);

        try {
            Class<?> targetClazz = Class.forName(ZhangActivityClass.getName(), true,
                    ZhangActivityClass.getClassLoader());
            Method dest = targetClazz.getDeclaredMethod("onCreate");
            replace(MainActivity.class.getDeclaredMethod("TestMethod"),
                    dest);

        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        }
        catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native void printLog();

    public native void printAPILevel(int level);

    public native void printMethodInfo(Method method);

    public static native void replace(Method src, Method dest);


    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }
}
