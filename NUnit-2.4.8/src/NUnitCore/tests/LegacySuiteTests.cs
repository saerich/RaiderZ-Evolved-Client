// ****************************************************************
// Copyright 2007, Charlie Poole
// This is free software licensed under the NUnit license. You may
// obtain a copy of the license at http://nunit.org/?p=license&r=2.4
// ****************************************************************

using System;
using System.Collections;
using NUnit.Framework;
using NUnit.Core;
using NUnit.TestData;

namespace NUnit.Core.Tests
{
	/// <summary>
	/// Summary description for LegacySuiteTests.
	/// </summary>
	[TestFixture]
	public class LegacySuiteTests
	{
        static int setupCount = 0;
        static int teardownCount = 0;

        [Test]
        public void SuiteReturningTestSuite()
        {
            TestSuite suite = new LegacySuite(typeof(NUnit.Core.Tests.AllTests));
            Assert.AreEqual(RunState.Runnable, suite.RunState);
            Assert.AreEqual(3, suite.Tests.Count);
            Assert.AreEqual(11, suite.TestCount);
        }

        [Test]
        public void SuiteReturningFixtures()
        {
            TestSuite suite = new LegacySuite(typeof(LegacySuiteReturningFixtures));
            Assert.AreEqual(RunState.Runnable, suite.RunState);
            Assert.AreEqual(3, suite.Tests.Count);
            Assert.AreEqual(11, suite.TestCount);
        }

        private class LegacySuiteReturningFixtures
        {
            [Suite]
            public static IEnumerable Suite
            {
                get
                {
                    ArrayList suite = new ArrayList();
                    suite.Add(new OneTestCase());
                    suite.Add(new AssemblyTests());
                    suite.Add(new NoNamespaceTestFixture());
                    return suite;
                }
            }
        }

        [Test]
        public void SuiteReturningTypes()
        {
            TestSuite suite = new LegacySuite(typeof(LegacySuiteReturningTypes));
            Assert.AreEqual(RunState.Runnable, suite.RunState);
            Assert.AreEqual(3, suite.Tests.Count);
            Assert.AreEqual(11, suite.TestCount);
        }

        private class LegacySuiteReturningTypes
        {
            [Suite]
            public static IEnumerable Suite
            {
                get
                {
                    ArrayList suite = new ArrayList();
                    suite.Add(typeof(OneTestCase));
                    suite.Add(typeof(AssemblyTests));
                    suite.Add(typeof(NoNamespaceTestFixture));
                    return suite;
                }
            }
        }

        [Test]
		public void SetUpAndTearDownAreCalled()
		{
            setupCount = teardownCount = 0;
			TestSuite suite = new LegacySuite( typeof( LegacySuiteWithSetUpAndTearDown ) );
            Assert.AreEqual(RunState.Runnable, suite.RunState);
			suite.Run( NullListener.NULL );
			Assert.AreEqual( 1, setupCount );
			Assert.AreEqual( 1, teardownCount );
		}

		private class LegacySuiteWithSetUpAndTearDown
		{
 			[Suite]
			public static TestSuite TheSuite
			{
				get { return new TestSuite( "EmptySuite" ); }
			}

			[TestFixtureSetUp]
			public void SetUpMethod()
			{
				setupCount++;
			}

			[TestFixtureTearDown]
			public void TearDownMethod()
			{
				teardownCount++;
			}
		}

        [Test]
        public void SuitePropertyWithInvalidType()
        {
            TestSuite suite = new LegacySuite(typeof(LegacySuiteWithInvalidPropertyType));
            Assert.AreEqual(RunState.NotRunnable, suite.RunState);
        }

        private class LegacySuiteWithInvalidPropertyType
        {
            [Suite]
            public static object TheSuite
            {
                get { return null; }
            }
        }
	}
}
