#include "Money.h"

double Money::getAmount() const
{
    return m_amount;
}

std::string Money::getCurrency() const
{
    return m_currency;
}

bool Money::operator ==( const Money &other ) const
{
    return m_amount == other.m_amount  &&
           m_currency == other.m_currency;
}

bool Money::operator !=( const Money &other ) const
{
    return !(*this == other);
}

Money &Money::operator +=( const Money &other )
{
    if ( m_currency != other.m_currency )
        throw IncompatibleMoneyError();

    m_amount += other.m_amount;
    return *this;
}
