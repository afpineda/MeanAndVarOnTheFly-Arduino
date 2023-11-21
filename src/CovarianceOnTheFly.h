/**
 * @author afpineda
 * @brief Arithmetic mean and variance without storing individual values
 * @date 2023-11-21
 */

#ifndef __COVARIANCEONTHEFLY_H__
#define __COVARIANCEONTHEFLY_H__

#include <type_traits>
#include "MeanAndVarOnTheFly.h"

/**
 * @brief Compute "on-the-fly" the covariance of two statistical variables
 *
 * @note Individual values are **not** stored in memory.
 *
 * @param Number An arithmetic type (int, float, etc.). Do not use unsigned types.
 */
template <typename Number = int, class = typename std::enable_if<std::is_signed<Number>::value>::type>
class Covariance
{
private:
    MeanAndVar<Number> X;
    MeanAndVar<Number> Y;
    MeanAndVar<Number> Sum;

public:
    /**
     * @brief Construct a new Covariance object
     *
     */
    Covariance()
    {
        reset();
    };

    /**
     * @brief Start a new calculation with an empty population
     *
     */
    void reset()
    {
        X.reset();
        Y.reset();
        Sum.reset();
    };

    /**
     * @brief Add another pair to the statistical population
     *
     * @note Pairs are not stored in memory
     *
     * @param X_Sample Value of the first variable to be added to the statistical population
     * @param Y_Sample Value of the second variable to be added to the statistical population
     */
    void add(const Number X_sample, const Number Y_sample)
    {
        X.add(X_sample);
        Y.add(Y_sample);
        Sum.add(X_sample + Y_sample);
    };

    /**
     * @brief Compute the covariance
     *
     * @return Current covariance
     */
    Number getCurrent()
    {
        return (Sum.getUnbiasedVariance() - X.getUnbiasedVariance() - Y.getUnbiasedVariance()) / 2;
    }

    /**
     * @brief Get the current size of the population
     *
     * @return Count of pairs in the statistical population
     */
    Number getCount()
    {
        return Sum.getCount();
    };
};

#endif