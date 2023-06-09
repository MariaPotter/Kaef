#include "Tool.hpp"

using namespace std;

Tool operator+ (const Tool& a, const Tool& b)
{
    if (a.deg() == -1) return b;
    if (b.deg() == -1) return a;

    int d = max (a.deg(), b.deg());

    vector<double> result (static_cast<unsigned int> (d + 1));

    for (unsigned int i = 0; i < static_cast<unsigned int> (d + 1); ++i)
    {
        if (static_cast<int> (i) <= a.deg() && static_cast<int> (i) <= b.deg())
            result[i] = a.coeff_[i] + b.coeff_[i];
        else if (static_cast<int> (i) > a.deg()) result[i] = b.coeff_[i];
        else result[i] = a.coeff_[i];
    }

    return Tool (result);
}

Tool operator- (const Tool& p)
{
    vector<double> result (p.coeff_.size());

    for (unsigned int i = 0; i < static_cast<unsigned int> (result.size()); ++i)
        result[i] = -p.coeff_[i];

    return Tool (result);
}

Tool operator- (const Tool& a, const Tool& b) { return a + (-b); }

Tool operator* (const Tool& a, const Tool& b)
{
    if (a.deg() == -1 || b.deg() == -1) return Tool ({0});

    vector<double> result (static_cast<unsigned int> (a.deg() + b.deg() + 1),
                           0);

    for (unsigned int i = 0; i < static_cast<unsigned int> (result.size()); ++i)
    {
        for (unsigned int j = 0; j <= i; ++j)
        {
            if (static_cast<int> (j) > a.deg() ||
                static_cast<int> (i - j) > b.deg())
                continue;

            result[i] += a.coeff_[j] * b.coeff_[i - j];
        }
    }

    return Tool (result);
}

ToolWithSupp operator+ (const ToolWithSupp& a, const ToolWithSupp& b)
{
    if (a.N_ != b.N_) error (-1, "a.N_ != b.N_ in operator+");

    return ToolWithSupp (a.tool_ + b.tool_, max (a.start_, b.start_),
                         min (a.end_, b.end_), a.N_);
}

ToolWithSupp operator- (const ToolWithSupp& p)
{
    return ToolWithSupp (-p.tool_, p.start_, p.end_, p.N_);
}

ToolWithSupp operator- (const ToolWithSupp& a, const ToolWithSupp& b)
{
    return a + (-b);
}

ToolWithSupp operator* (const ToolWithSupp& a, const ToolWithSupp& b)
{
    if (a.N_ != b.N_) error (-1, "a.N_ != b.N_ in operator*");

    return ToolWithSupp (a.tool_ * b.tool_, max (a.start_, b.start_),
                         min (a.end_, b.end_), a.N_);
}
