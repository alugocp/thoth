using System;
using Microsoft.Win32.SafeHandles;

namespace Thoth
{

	internal class API : SafeHandleZeroOrMinusOneIsInvalid
	{
		internal API() : base(true){
		}

		protected override bool ReleaseHandle(){

		}
	}

}