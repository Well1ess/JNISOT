package netease.com.jnisot;

import java.lang.reflect.Method;

/**
 * Created by shs1330 on 2018/3/16.
 */

public class VMReplace {
    public static native void showArtMethodSize(Method src, Method dest);
}
