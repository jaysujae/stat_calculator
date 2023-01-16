# Stat Calculator

This codebase deals with how to efficiently calculate mean and variance from stream data.

## How to run
```
make all
```

## Reference
- https://nestedsoftware.com/2018/03/20/calculating-a-moving-average-on-streaming-data-5a7k.22879.html
- https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance

## Things to consider
1. 'catastrophic cancellation'
- `the phenomenon that subtracting good approximations to two nearby numbers may yield a very bad approximation to the difference of the original numbers` - Wikipedia
- rough rule is that if x and y match up to m significant figures, then up to m significant figures can be lost.

## Problem & Solution

### Q1. How to get running variance for integer data?
- For integer data, we can assign many significant numbers, meaning we don't need to worry about catastrophic cancellation compared to float data. (Unless the numbers are super big and vairance is small.)
- Therefore we can save sum of X**2 and sum of X, and use the formula 'var(x) = E(X^2) - E(X)^2'


### Q2. How to get running variance for float data?
- using above method for float data has a danger of catastrophic cancellation. Double can represent 15~16 digits (https://blog.demofox.org/2017/11/21/floating-point-precision/), so when we're calculating E(X^2)- E(X)^2, we can lost up to m significant figures, making double not reliable and even negative value.
- we can use welford algorithm.
- Since Var(Xn) = E(Xn^2) - E(Xn)^2
-> n * Var(Xn) = Sum(Xn^2) - n * E(Xn)^2
= n * Var(Xn) = Sum(Xn-1 ^2) + Xn^2 - (n-1)*E(Xn-1)^2 + (n-1)*E(Xn-1)^2 - n * E(Xn)^2
= (n-1)*Var(Xn-1) + Xn^2 + (n-1)*E(Xn-1)^2 - n * E(Xn)^2
since E(Xn) = E(Xn-1) + (Xn - E(Xn-1)) / n
= (n-1)*Var(Xn-1) + (Xn - E(Xn)) ( Xn - E(Xn-1)).
here, let's say n*Var(Xn) as M(Xn).
- so, M(Xn) = M(Xn-1) + (Xn - E(Xn) * (Xn - E(xn-1))


### Q3. Can we consider a special case when small subset of values are much larger than normal values?
- Since small subset of values are much larger, they have a danger of poluting (cancelling precision) data.
I suggest calculating them differently and adding variance with the assumption that they're independent. ( Since Var(A + B) = Var(A) + Var(B) when they're independent.)

### Q4. Can we support a sliding window ability as well ? 
For integer case,
1. We can save all the values and timestamp, and find the starting time using binary search (can use map in cpp,) and then start calculating
2. If that calculation is burdening to do in online time, we can save them in prefix-sum and use E(X^2) - E(X)^2 formula.
For floating point case,
3. The danger of cancellation is in that we're calculating large numbers with limited precision to get small number. We can consider shifting the values using the sample mean to get Var(x-m), so that E(X^2) and E(X^2) don't become big. 