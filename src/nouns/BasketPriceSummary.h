//
// Created by krzysiek on 15.04.15.
//

#ifndef LEMON_BASKETPRICESUMMARY_H
#define LEMON_BASKETPRICESUMMARY_H


class BasketEntryPriceSummary {
private:
    double net;
    double gross;
    double tax;
    double discountGross;
    int points;

public:
    BasketEntryPriceSummary(double net, double gross, double tax, double discountGross, int points);
    virtual ~BasketEntryPriceSummary();

public: //getters
    double getNet();
    double getGross();
    double getTax();
    double getDiscountGross();
    int getPoints();
};

class BasketPriceSummary {
private:
    double net;
    double gross;
    double tax;
    double discountGross;
    int points;

public:
    BasketPriceSummary();
    BasketPriceSummary(double net, double gross, double tax, double discountGross, int points);
    virtual ~BasketPriceSummary();
    void add(BasketEntryPriceSummary basketEntryPriceSummary);
public: //getters
    double getNet();
    double getGross();
    double getTax();
    double getDiscountGross();
    int getPoints();
};


#endif //LEMON_BASKETPRICESUMMARY_H
