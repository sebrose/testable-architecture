public class EcoStat
{
    public string SalesPersonName { get; private set; }
    public float RevenuePerMile { get; private set; }

    public EcoStat(string salesPersonName, float revenuePerMile)
    {
        this.SalesPersonName = salesPersonName;
        this.RevenuePerMile = revenuePerMile;
    }
}
