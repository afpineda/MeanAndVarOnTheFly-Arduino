# Compute mean and variance (biased and/or unbiased) "on the fly"

This small library allows a computation of mean, variance and covariance **without keeping track in memory** of each individual sample.
The library is intended for Arduino applications, however it may be used in any C++ program.

Based on [Welford's online algorithm](https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#Welford's_online_algorithm).

## How to use

Check code commentaries for further information.

### Single statistical variable

There is a class template, `MeanAndVar`, that should be instantiated to a **signed** numerical data type. Typical uses are (for example):

```c++
#include<MeanAndVarOnTheFly.h>

MeanAndVar<int> integerPopulation;
MeanAndVar<float> realNumberPopulation;
```

Check the [examples folder](./examples) for some usage cases, mostly **filters** for [ADC](https://en.wikipedia.org/wiki/Analog-to-digital_converter) readings.

You can reuse an existing object to compute a new mean and variance by calling `reset()`. Add samples to your population using `add()`, then retrieve the mean and variance with `getMean()`, `getUnbiasedVariance()` and `getVariance()`. Call `getCount()` to know the size of the statistical population.

### Covariance matrix

There is a class template, `CovarianceMatrix`, that should be instantiated to **int32_t**, **int64_t** or **double** (no other types are allowed).
Include the proper header in your sketch:

```c++
#include<CovarianceOnTheFly.h>
```

You must provide the count of statistical variables in the covariance matrix at the class constructor:

```c++
CovarianceMatrix<double> example(4); // Creates a 4x4 (symmetrical) covariance matrix for 4 statistical variables
```

Add samples to your population using `add()`, one argument for each statistical variable, in ascending order of index. For example:

```c++
CovarianceMatrix<double> example(4); // four statistical variables
example.add( 1.0, 30.3, 1.2, 30.9); // four arguments are mandatory (first,second,third,fourth).
```

Then you may retrieve the covariance for any pair of statistical variables with `getCovariance()`.
Arguments to this function are 0-based indices of the involved statistical variables. For example:

```c++
CovarianceMatrix<double> example(4); // four statistical variables

auto cov1_2 = example.getCovariance(1,2) // covariance of second and third variables.
auto cov0_3 = example.getCovariance(0,3) // covariance of first and fourth variables.

```

You can reuse an existing object to compute a new covariance matrix by calling `reset()`.
Call `getCount()` to know the size of the statistical population. 
Call `getMean()` to retrieve the mean of a single statistical variable.
