using System.Collections.Generic;

namespace ShoutyReport.Builders
{
    public class MileageClaimCollectionBuilder
    {
        private List<MileageClaim> defaultMileageClaimCollection =
            new List<MileageClaim>(){
                new MileageClaim("David Allen", 130000, 57),
                new MileageClaim("Lisa Crispin", 27000, 19),
                new MileageClaim("Ian Dees", 19238855, 22)
            };

        private List<MileageClaim> mileageClaimCollection = null;

        public List<MileageClaim> build() {
            if (mileageClaimCollection == null) {
                return defaultMileageClaimCollection;
            } else {
                return mileageClaimCollection;
            }
        }

        public MileageClaimCollectionBuilder withSalesPersonMilesForCustomer(
          string name,
          int miles,
          int id) {

            if (mileageClaimCollection == null){
                mileageClaimCollection = new List<MileageClaim>();
            }

            mileageClaimCollection.Add(new MileageClaim(name, miles, id));
            return this;
        }
    }
}
