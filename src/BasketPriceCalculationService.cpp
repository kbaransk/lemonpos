#include "BasketPriceCalculationService.h"
#include "settings.h"

double BasketPriceCalculationService::calculateEntryDiscount(ProductInfo & prod, ClientInfo & client, bool forceGross) {
    bool pricesAreGross = !Settings::addTax(); //just a better name to understant what to do.

    double entryTotal = prod.qtyOnList * prod.price;
    double entryDiscount = 0.0;

    if (!prod.isNotDiscountable) {
        // Product discount. validDiscount==true -> use absolute; validDiscount==false -> use percentage
        if (prod.validDiscount) {
            entryDiscount += prod.qtyOnList * prod.disc;
        }
        else {
            entryDiscount += (prod.discpercentage * entryTotal) / 100;
        }

        // Client discount
        if (client.discount >= 0) {
            entryDiscount += (client.discount * entryTotal) / 100;
        }
    }

    if (!pricesAreGross && forceGross) {
        double taxFactor = (prod.tax + prod.extratax) / 100;
        if (taxFactor > 0) {
            entryDiscount *= (1.0 + taxFactor);
        }
    }

    return entryDiscount;
}

BasketEntryPriceSummary BasketPriceCalculationService::calculateBasketEntry(ProductInfo & prod, ClientInfo & client, bool applyDiscounts) {
    bool pricesAreGross = !Settings::addTax(); //just a better name to understant what to do.

    double entryTotal = prod.qtyOnList * prod.price;

    double entryDiscount = applyDiscounts ? this->calculateEntryDiscount(prod, client, pricesAreGross) : 0.0;
    double entryDiscountGross = applyDiscounts ? this->calculateEntryDiscount(prod, client, true) : 0.0;

    double entryBasePrice = entryTotal - entryDiscount;


    double taxFactor = (prod.tax + prod.extratax) / 100;
    double entryTax = 0.0;
    double entryNetPrice = 0.0;
    double entryGrossPrice = 0.0;

    if (pricesAreGross) {
        entryNetPrice = entryBasePrice / (1 + taxFactor);
        entryGrossPrice = entryBasePrice;
        entryTax = entryBasePrice - entryNetPrice;
    }
    else {
        entryNetPrice = entryBasePrice;
        entryTax = entryBasePrice * taxFactor;
        entryGrossPrice = entryNetPrice + entryTax;
    }


    BasketEntryPriceSummary result(entryNetPrice, entryGrossPrice, entryTax, entryDiscountGross, prod.points * prod.qtyOnList);
    return result;
}

BasketPriceSummary BasketPriceCalculationService::calculateBasketPrice(QHash<qulonglong, ProductInfo> & products, ClientInfo & client, double salesmanDiscount)
{
    BasketPriceSummary basketPriceSummary;

    bool useSalesmanDiscount = client.discount == 0 && salesmanDiscount > 0;

    foreach (ProductInfo prod, products) {
        BasketEntryPriceSummary basketEntryPriceSummary = this->calculateBasketEntry(prod, client, !useSalesmanDiscount);
        basketPriceSummary.add(basketEntryPriceSummary);
    }

    if (useSalesmanDiscount) {
        // apply absolut discount
        double factor = salesmanDiscount / basketPriceSummary.getGross();
        BasketPriceSummary salesmanDiscountedBasketPriceSummary(basketPriceSummary.getNet() * factor, basketPriceSummary.getGross() * factor, basketPriceSummary.getTax() * factor, salesmanDiscount, basketPriceSummary.getPoints());
        return salesmanDiscountedBasketPriceSummary;
    }

    return basketPriceSummary;
}
