# Compute mean and variance (biased and/or unbiased) "on the fly"

This small library allows a computation of mean and variance **without keeping track in memory** of each individual sample.
The library is intended for Arduino applications, however it may be used in any C++ program.

Based on [Welford's online algorithm](https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#Welford's_online_algorithm).

## How to use

There is just one class template, `MeanAndVar`, that should be instantiated to a **signed** numerical data type. Typical uses are (for example):

```c++
#include<MeanAndVarOnTheFly.h>

MeanAndVar<int> integerPopulation;
MeanAndVar<float> realNumberPopulation;
```

Check the [examples folder](./examples) for some usage cases, mostly **filters** for [ADC](https://en.wikipedia.org/wiki/Analog-to-digital_converter) readings.

You can reuse an existing object to compute a new mean and variance by calling `reset()`. Add samples to your population using `add()`, then retrive the mean and variance with `getMean()`, `getUnbiasedVariance()` and `getVariance()`. Call `getCount()` to know the size of the statistical population.

Check code commentaries for further information.
