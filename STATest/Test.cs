using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using NUnit.Framework;

namespace STATest
{
	[SetUpFixture]
	class SetUp
	{
	}

	[TestFixture]
	class Test
	{
		[Test, Apartment(ApartmentState.STA)]
		public void DoTest()
		{
			Assert.AreEqual( ApartmentState.STA, Thread.CurrentThread.GetApartmentState() );
		}
	}
}
