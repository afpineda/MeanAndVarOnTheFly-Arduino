/**
 * @author afpineda
 * @brief Arithmetic mean and variance without storing individual values
 * @date 2023-03-04
 */

#ifndef __MEANANDVARONTHEFLY_H__
#define __MEANANDVARONTHEFLY_H__

#include <type_traits>

/**
 * @brief Compute "on-the-fly" the arithmetic mean and variance of a statistical population
 *
 * @note Individual values are **not** stored in memory.
 *
 * @param Number An arithmetic type (int, float, etc.). Do not use unsigned types.
 */
template <typename Number = int, class = typename std::enable_if<std::is_signed<Number>::value>::type>
class MeanAndVar
{
private:
    Number mean;
    Number M2;
    Number count;

public:
    /**
     * @brief Construct a new MeanAndVar object
     *
     */
    MeanAndVar()
    {
        reset();
    };

    /**
     * @brief Start a new calculation with an empty population
     *
     */
    void reset()
    {
        mean = {};
        M2 = {};
        count = {};
    };

    /**
     * @brief Add another value (or sample) to the statistical population
     *
     * @note Samples are not stored in memory
     *
     * @param sample Value to be added to the statistical population
     */
    void add(const Number sample)
    {
        Number oldDelta, newDelta;
        count++;
        oldDelta = sample - mean;
        mean += (oldDelta / count);
        newDelta = sample - mean;
        M2 += (newDelta * oldDelta);
    };

    /**
     * @brief Get the arithmetic mean of the population.
     *
     * @return Current arithmetic mean or zero if there is no population.
     */
    Number getMean()
    {
        return mean;
    };

    /**
     * @brief Get the unbiased variance of the population.
     *        The unbiased variance is an estimator of the variance to be used
     *        if the whole population is unknown.
     *
     * @note Uses [Welford's online algorithm](https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#Welford's_online_algorithm).
     * @return Current unbiased variance or zero if population' size is less than two samples
     */
    Number getUnbiasedVariance()
    {
        if (count > 1)
            return (M2 / (count - 1));
        else
            return {};
    };

    /**
     * @brief Get the (biased) variance of the population
     *
     * @note Uses [Welford's online algorithm](https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#Welford's_online_algorithm).
     * @return Current variance or zero if population' size is less than two samples
     */
    Number getVariance()
    {
        if (count > 0)
            return (M2 / count);
        else
            return (Number){};
    };

    /**
     * @brief Get the current size of the population
     *
     * @return Count of samples in the statistical population
     */
    Number getCount()
    {
        return count;
    };
};

#endif