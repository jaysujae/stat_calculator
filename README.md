# Stat Calculator

This codebase deals with how to efficiently calculate mean and variance from stream data.

## How to run
```
make all
```


## Problem & Solution

1. We want to get mean and variance of given values.
- Simple. Use the definition of mean and variance
```
Mean(Xn) = sum(X1,X2,...Xn) / n ;
Var(Xn) = sum( (X1-Xm)^2, (X2-Xm)^2, ...(Xn-Xm)^2) / n;
```
- let's call it 'Naive' method in the code.

2. We want to get mean and variance of stream data, with acceptable latency (can't recompute mean and variance everytime value comses)
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
- We can expect some problems with this method, like overflow and precision.
- Let's call it 'Formula' method.


