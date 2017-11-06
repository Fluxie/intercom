using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
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
		[Test]
		public void DoTest()
		{
			Assert.IsTrue( true );
		}
	}
}
