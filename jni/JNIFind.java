
public class JNIFind {
	public native long create_search_pool(float [] data, int dimen, int size);
	public native void destroy_search_pool(long pool);

	public native int find_0(float[] target, long pool);
	public native int find_1(float[] target, long pool);
	public native int find_2(float[] target, long pool);
	public native int find_3(float[] target, long pool);

	static {
		System.loadLibrary("JNIFind");
	}
}
