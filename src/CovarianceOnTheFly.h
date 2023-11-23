/**
 * @author afpineda
 * @brief Arithmetic mean and variance without storing individual values
 * @date 2023-11-21
 */

#ifndef __COVARIANCEONTHEFLY_H__
#define __COVARIANCEONTHEFLY_H__

#include <type_traits>
#include <cstdarg>
#include <stdexcept>

/**
 * @brief Estimate "on-the-fly" the covariance of a number of statistical variables
 *
 * @note Individual values are **not** stored in memory. Based on
 *       [online algorithm](https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#Covariance)
 *
 * @param Number int32_t, int64_t or double.
 */

template <typename Number>
class CovarianceMatrix
{
    static_assert(std::is_same<Number, int32_t>::value || std::is_same<Number, double>::value || std::is_same<Number, int64_t>::value);

protected:
    unsigned int varCount;
    Number *covArray;
    Number *meanArray;
    Number *lastSampleArray;
    Number samplesCount;

    int covArrayIndex(int row, int col)
    {
        if (row <= col)
        {
            unsigned int unusedMatrixCellCount = (row * (row + 1)) / 2;
            unsigned int matrixIndex = row * varCount;
            return matrixIndex - unusedMatrixCellCount + col;
        }
        else
            return covArrayIndex(col, row);
    };

public:
    /**
     * @brief Construct a new Covariance Matrix object
     *
     * @param countOfStatisticalVars Count of statistical variables in the matrix (row/column count)
     * @throws std::invalid_argument If the given parameter is zero
     */
    CovarianceMatrix(unsigned int countOfStatisticalVars = 2)
    {
        varCount = countOfStatisticalVars;
        if (varCount > 0)
        {
            meanArray = (Number *)calloc(varCount, sizeof(Number));
            lastSampleArray = (Number *)calloc(varCount, sizeof(Number));
            covArray = (Number *)calloc((((varCount * varCount) - varCount) / 2) + varCount, sizeof(Number));
            reset();
        }
        else
            throw std::invalid_argument("at least one statistical variable is required");
    };

    ~CovarianceMatrix()
    {
        free(meanArray);
        free(lastSampleArray);
        free(covArray);
    };

    /**
     * @brief Start a new calculation with an empty population
     *
     */
    void reset()
    {
        samplesCount = {};
        unsigned int i;
        for (i = 0; i < varCount; i++)
            meanArray[i] = {};
        unsigned int covArraySize = (((varCount * varCount) - varCount) / 2) + varCount;
        for (i = 0; i < covArraySize; i++)
            covArray[i] = {};
    };

    /**
     * @brief Add another sample to the statistical population of each variable
     *
     * @param firstVarValue A sample value for the first statistical variable
     * @param ... Sample values for other statistical variables, in ascending order
     * @note The number of arguments to this function must match the count of statistical variables
     *       given in the constructor
     */
    void add(Number firstVarValue, ...)
    {
        if (varCount == 0)
            return;

        va_list argList;
        unsigned int i, j;

        // Retrieve var samples from arguments list
        lastSampleArray[0] = firstVarValue;
        va_start(argList, firstVarValue);
        for (i = 1; i < varCount; i++)
        {
            lastSampleArray[i] = va_arg(argList, Number); // Note: may be promoted
        }
        va_end(argList);

        // Compute new means
        samplesCount++;
        for (i = 0; i < varCount; i++)
            meanArray[i] += ((lastSampleArray[i] - meanArray[i]) / samplesCount);

        // Compute covariance matrix
        if (samplesCount > 1)
            for (i = 0; i < varCount; i++)
                for (j = i; j < varCount; j++)
                {
                    unsigned int cIndex = covArrayIndex(i, j);
                    Number prevSamplesCount = samplesCount - 1;
                    Number squares = (lastSampleArray[i] - meanArray[i]) * (lastSampleArray[j] - meanArray[j]);
                    Number term1 = covArray[cIndex] * prevSamplesCount;
                    Number term2 = (squares * samplesCount) / prevSamplesCount;
                    covArray[cIndex] = (term1 + term2) / samplesCount;
                }
    };

    /**
     * @brief Get the mean of a single statistical variable
     *
     * @param varIndex 0-based index of the statistical variable
     * @return The mean or zero if there are no samples
     */
    Number getMean(unsigned int varIndex)
    {
        if (varIndex < varCount)
            return meanArray[varIndex];
        else
            throw std::invalid_argument("index out of bounds");
    };

    /**
     * @brief Get the count of samples in the statistical population
     *
     * @return Count of samples
     */
    Number getCount()
    {
        return samplesCount;
    };

    /**
     * @brief Get the biased covariance between two statistical variables
     *
     * @param firstVarIndex 0-based index of the first statistical variable
     * @param secondVarIndex 0-based index of the second statistical variable
     * @return Covariance or zero if there are less than 2 samples
     * @throws std::invalid_argument If any index is out of bounds
     */
    Number getCovariance(int firstVarIndex, int secondVarIndex)
    {
        if ((firstVarIndex < varCount) && (secondVarIndex < varCount))
        {
            unsigned int arrayIndex = covArrayIndex(firstVarIndex, secondVarIndex);
            return covArray[arrayIndex];
        }
        else
            throw std::invalid_argument("index out of bounds");
    }

    /**
     * @brief Get the biased variance of a single statistical variable
     *
     * @param varIndex 0-based index of the statistical variable
     * @return The biased variance or zero if there are less than 2 samples
     */
    Number getVariance(int varIndex)
    {
        return getCovariance(varIndex, varIndex);
    }
};

#endif