/**
 * @author afpineda
 * @brief Arithmetic mean and variance without storing individual values
 * @date 2023-03-04
 */

#ifndef __MEANANDVARONTHEFLY_H__
#define __MEANANDVARONTHEFLY_H__

/**
 * @brief Compute "on-the-fly" the arithmetic mean and variance of an statistical population
 * 
 * @note Individual values are **not** stored in memory.
 * 
 * @tparam Number An arithmetic type (int, float, etc.). Do not use unsigned types.
 */
template <typename Number = int> class MeanAndVar
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
    MeanAndVar() {
        reset();
    }

    /**
     * @brief Start a new calculation with an empty population
     * 
     */
    void reset();

    /**
     * @brief Add another sample to the statistical population
     * 
     * @note Samples are not stored in memory
     * 
     * @param sample Value to be added to the statistical population
     */
    void add(const Number sample);

    /**
     * @brief Get the arithmetic mean of the population.
     *  
     * @return Number Current arithmetic mean or zero if there is no population.
     */
    Number getMean();

    /**
     * @brief Get the unbiased variance of the population
     * 
     * @note Uses [Welford's online algorithm](https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#Welford's_online_algorithm).
     * @return Number Current unbiased variance or zero if population' size is less than two samples
     */
    Number getUnbiasedVariance();

     /**
     * @brief Get the biased variance of the population
     * 
     * @note Uses [Welford's online algorithm](https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#Welford's_online_algorithm).
     * @return Number Current biased variance or zero if population' size is less than two samples
     */
    Number getVariance();

    /**
     * @brief Get size of the population
     * 
     * @return unsigned long int Count of samples in the statistical population
     */
    Number getCount();
};

template <typename Number>
void MeanAndVar<Number>::reset()
{
    mean = {};
    M2 = {};
    count = {};
}

template <typename Number>
void MeanAndVar<Number>::add(const Number sample)
{
    Number oldDelta, newDelta;
    count++;
    oldDelta = sample - mean;
    mean += (oldDelta / count);
    newDelta = sample - mean;
    M2 += (newDelta * oldDelta);
}

template <typename Number>
Number MeanAndVar<Number>::getMean()
{
    return mean;
}

template <typename Number>
Number MeanAndVar<Number>::getUnbiasedVariance()
{
    if (count>1)
        return (M2/(count-1));
    else
        return (Number){};
}

template <typename Number>
Number MeanAndVar<Number>::getVariance()
{
    if (count>0)
        return (M2/count);
    else
        return (Number){};
}

template <class Number>
Number MeanAndVar<Number>::getCount()
{
    return count;
}

#endif