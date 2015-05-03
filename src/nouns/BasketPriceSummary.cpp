//
// Created by krzysiek on 15.04.15.
//

#include "BasketPriceSummary.h"

BasketEntryPriceSummary::BasketEntryPriceSummary(double net, double gross, double tax, double discountGross, int points) {
    this->net = net;
    this->gross = gross;
    this->tax = tax;
    this->discountGross = discountGross;
    this->points = points;
}

BasketEntryPriceSummary::~BasketEntryPriceSummary() {
}

double BasketEntryPriceSummary::getNet() {
    return this->net;
}

double BasketEntryPriceSummary::getGross() {
    return this->gross;
}

double BasketEntryPriceSummary::getTax() {
    return this->tax;
}

double BasketEntryPriceSummary::getDiscountGross() {
    return this->discountGross;
}

int BasketEntryPriceSummary::getPoints() {
    return this->points;
}


// ------------------------------------------


BasketPriceSummary::BasketPriceSummary() {
}

BasketPriceSummary::BasketPriceSummary(double net, double gross, double tax, double discountGross, int points) {
    this->net = net;
    this->gross = gross;
    this->tax = tax;
    this->discountGross = discountGross;
    this->points = points;
}

void BasketPriceSummary::add(BasketEntryPriceSummary basketEntryPriceSummary) {
    net += basketEntryPriceSummary.getNet();
    gross += basketEntryPriceSummary.getGross();
    tax += basketEntryPriceSummary.getTax();
    discountGross += basketEntryPriceSummary.getDiscountGross();
    points += basketEntryPriceSummary.getPoints();
}

BasketPriceSummary::~BasketPriceSummary() {
}

double BasketPriceSummary::getNet() {
    return this->net;
}

double BasketPriceSummary::getGross() {
    return this->gross;
}

double BasketPriceSummary::getTax() {
    return this->tax;
}

double BasketPriceSummary::getDiscountGross() {
    return this->discountGross;
}

int BasketPriceSummary::getPoints() {
    return this->points;
}
