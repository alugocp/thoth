using System;
using System.Runtime.InteropServices;

class ThothAPI:IDisposable{

	public ThothAPI() {
		wrapped_init();
	}
	public void Dispose() {
		wrapped_free();
	}

	// Public facing API interface
	public string[] new_words(int n,int l) {
		IntPtr ptrs=wrapped_new_words(n,l);
        IntPtr[] data = new IntPtr[n];
        Marshal.Copy(ptrs,data,0,n);
        string[] words = new string[n];
        for (int a = 0; a < n; a++) {
            words[a] =Marshal.PtrToStringAnsi(data[a]);
        }
        return words;
    }
	public void new_lang() {
		wrapped_new_lang();
	}

	// Wrapped binary C++ functions
	private const string DllName = "libthoth.so";
	[DllImport(DllName, EntryPoint = "thothAPI_new_words")]
    [return: MarshalAs(UnmanagedType.LPArray,ArraySubType = UnmanagedType.LPStr,SizeConst = 80)]
    private static extern IntPtr wrapped_new_words(int n,int l);
	[DllImport(DllName, EntryPoint = "thothAPI_new_language")]
	private static extern void wrapped_new_lang();
	[DllImport(DllName, EntryPoint = "thothAPI_start")]
	private static extern void wrapped_init();
	[DllImport(DllName, EntryPoint = "thothAPI_free")]
	private static extern void wrapped_free();
}

