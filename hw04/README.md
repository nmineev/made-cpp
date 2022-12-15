# Homework #4: First try on multiprocessing
[![codecov](https://codecov.io/gh/nmineev/made-cpp/branch/homework04/graph/badge.svg?token=6EHJ86ZD38)](https://codecov.io/gh/nmineev/made-cpp)
### Synchronous and Parallelized alghorithm comparison
**Runnings on 50mb data:**

| Algorithm type | Mean [ms] | Min [ms] | Max [ms] | Relative |
|:---:|---:|---:|---:|---:|
| `Parallelized` | 200.4 ± 26.4 | 150.1 | 226.7 | 1.00 |
| `Synchronous` | 851.6 ± 177.1 | 615.9 | 1019.6 | 4.25 ± 1.05 |

**Runnings on 100mb data:**

| Algorithm type | Mean [ms] | Min [ms] | Max [ms] | Relative |
|:---|---:|---:|---:|---:|
| `Parallelized` | 323.0 ± 39.9 | 294.0 | 402.3 | 1.00 |
| `Synchronous` | 1395.6 ± 267.0 | 1197.8 | 1991.0 | 4.32 ± 0.98 |

**Runnings on 200mb data:**

| Algorithm type | Mean [ms] | Min [ms] | Max [ms] | Relative |
|:---|---:|---:|---:|---:|
| `Parallelized` | 627.3 ± 58.2 | 570.6 | 739.2 | 1.00 |
| `Synchronous` | 2495.9 ± 69.0 | 2395.6 | 2586.5 | 3.98 ± 0.39 |

*It's not surprise, paralellized algorithm in 2-3 times faster.*  
Here, parallelized algorithm was divided into 12 processes;