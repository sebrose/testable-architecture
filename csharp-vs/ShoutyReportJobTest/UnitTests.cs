using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using ShoutyReport;

namespace ShoutyReport
{

    [TestClass]
    public class UnitTests
    {
        [TestMethod]
        public void milage_claim_can_be_created_from_strings()
        {
            var claim = new MileageClaim("David Allen", 37000, 99);
            Assert.AreEqual("David Allen", claim.Name);
            Assert.AreEqual(37000, claim.Miles);
            Assert.AreEqual(99, claim.CustomerID);
        }
    }
}
