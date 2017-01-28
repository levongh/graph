#include "kernigan_lin.h"

unsigned kernigan_lin::internal_cost() const
{
}

unsigned kernigan_lin::external_cost() const
{
}

unsigned kernigan_lin::moveing_cost() const
{
    return external_cost() - internal_cost();
}
