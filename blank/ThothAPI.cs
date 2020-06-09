using System;
using System.Runtime.InteropServices;
using System.Threading.Tasks;


class ThothAPI:IDisposable{

	public ThothAPI() {
		wrapped_init();
	}
	public void Dispose() {
		wrapped_free();
	}

	// Public facing API interface
	public void new_word(int l,Action<string> cb) {
		Task.Run(() => cb(wrapped_new_word(l)));
	}
	public void new_lang() {
		wrapped_new_lang();
	}

	// Wrapped binary C++ functions
	private const string DllName = "libthoth.so";
	[DllImport(DllName, EntryPoint = "thothAPI_new_word")]
	[return: MarshalAs(UnmanagedType.LPStr)]
	private static extern string wrapped_new_word(int l);
	[DllImport(DllName, EntryPoint = "thothAPI_new_language")]
	private static extern void wrapped_new_lang();
	[DllImport(DllName, EntryPoint = "thothAPI_start")]
	private static extern void wrapped_init();
	[DllImport(DllName, EntryPoint = "thothAPI_free")]
	private static extern void wrapped_free();
}

