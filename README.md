# Stat Calculator

This codebase deals with how to efficiently calculate mean and variance from stream data.

## How to run
```
make all
```

## Things to consider
1. 'catastrophic cancellation'
- `the phenomenon that subtracting good approximations to two nearby numbers may yield a very bad approximation to the difference of the original numbers` - Wikipedia

- rough rule is that if x and y match up to m significant figures, then up to m significant figures can be lost.

## Problem & Solution

0. We want to get mean and variance of given values.
- Simple. Use the definition of mean and variance
```
Mean(Xn) = sum(X1,X2,...Xn) / n ;
Var(Xn) = sum( (X1-Xm)^2, (X2-Xm)^2, ...(Xn-Xm)^2) / n;
```
- let's call it 'Naive' method in the code.

1. We want to get mean and variance of stream data, with acceptable latency (can't recompute mean and variance everytime value comses)
- Now we need to think about how we can reuse the calculation we did before.
- For mean, it is not hard to come up with the idea
```
Mean(Xn+1)
= sum(X1,X2, ... Xn+Xn+1) / (n+1) 
= (sum(X1,X2,...Xn) / n)*(n / (n+1)) + Xn+1 / (n+1)
= Mean(Xn) * (n / (n+1)) + Xn+1 / (n+1)
= Mean(Xn) + (Xn+1 - Mean(Xn) ) / (n+1)
```
- For variance, it might be helpful to come up with this formula
```
Var(Xn) 
= sum( (X1-Xm)^2, (X2-Xm)^2, ...(Xn-Xm)^2) / n;
= sum(X1^2, X2^2, ... Xn^2) - 2*n*Xm*sum(X1,...Xn) + sum(X1,..Xn)^2 ( since n * Xm = sum(X1,...Xn)) / n
= mean(Xn^2) - mean(Xn)^2
```
- Therefore if we save mean value and mean of square value, we can use a new mean value formula and get a new variance as well.
- We can expect some problems with this method, like overflow and precisions especially for float case.
- Let's call it 'Formula' method.

2. As I said above, 'Formula' method is not numerically stable because of 'catastrophic cancellation' effect. This leads to a natural line of thinking of using variance of previous calculation directly.
- This is called "Welford algorithm"
- Since Var(Xn) = E(Xn^2) - E(Xn)^2
-> n * Var(Xn) = Sum(Xn^2) - n * E(Xn)^2
= n * Var(Xn) = Sum(Xn-1 ^2) + Xn^2 - (n-1)*E(Xn-1)^2 + (n-1)*E(Xn-1)^2 - n * E(Xn)^2
= (n-1)*Var(Xn-1) + Xn^2 + (n-1)*E(Xn-1)^2 - n * E(Xn)^2
since E(Xn) = E(Xn-1) + (Xn - E(Xn-1)) / n
= (n-1)*Var(Xn-1) + (Xn - E(Xn)) ( Xn - E(Xn-1)).
here, let's say n*Var(Xn) as M(Xn).

As there is no too big number in this equation, this doesn't suffer from catastrophic cancellation problem.

3. Can we consider a special case, where small group is having much higher number than other numbers?
For this case, I think we can use this property.
```
E(aX+b) = aE(x) + b, and
Var(aX+b) = a^2E(X)
```
Since small group is way larger than other group,
we can consider calculating in two different groups and then add two group's statistics later.
More specifically, we can change the values into 1/10000 X - u ( where u is mean of small numbers group)
Then we can practically say small number's variance and mean is 0. 
Then while calculating, when small number comes then we just add count of small number.
For adding two group's statistics, I'll use this formula from wikipedia.
![formula absolute URL](https://wikimedia.org/api/rest_v1/media/math/render/svg/dd88631832bace8b86e5b41ffcfa78f50f1b6602)
