#ifndef MONEY_H
#define MONEY_H

#include <string>
#include <stdexcept>


class IncompatibleMoneyError : public std::runtime_error
{
public:
    IncompatibleMoneyError() : runtime_error( "Incompatible moneys" )
    {
    }
};


class Money
{
public:
    Money( double amount, std::string currency )
        : m_amount( amount )
        , m_currency( currency )
    {
    }

    double getAmount() const;
    std::string getCurrency() const;
    bool operator ==( const Money &other ) const;
    bool operator !=( const Money &other ) const;
    Money &operator +=( const Money &other );

private:
    double m_amount;
    std::string m_currency;
};

#endif
