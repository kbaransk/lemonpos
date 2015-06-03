#include "Currency.h"
#include <QTextStream>

Currency::Currency()
{
    this->amount = 0;
}

Currency::Currency(double amount)
{
    this->amount = amount * 100.0;
}

Currency::~Currency()
{
}

void Currency::substract(Currency currency)
{
    this->amount -= currency.amount;
}

void Currency::add(Currency currency)
{
    this->amount += currency.amount;
}

void Currency::multiply(double multiplier)
{
    this->amount *= multiplier;
}

void Currency::divide(double divider)
{
    this->amount /= divider;
}

double Currency::toDouble() const {
    double result = this->amount / 100.0;
    return result;
}

QString Currency::toString() const {
    QString result;
    QTextStream out(&result);
    out.setRealNumberPrecision(2);
    out.setRealNumberNotation(QTextStream::FixedNotation);
    out << this->toDouble();
    return result;
}


QTextStream& operator<<(QTextStream& os, const Currency& obj) {
    os << obj.toString();
    return os;
}

QDebug& operator<<(QDebug& os, const Currency& obj) {
    os << obj.toString();
    return os;
}
