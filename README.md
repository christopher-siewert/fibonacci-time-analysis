# Fibonacci Algorithmic Running Time Analysis

This is a demonstration of the large experimental difference between algorithms of different time complexities.

#### Fibonacci Sequence
The Fibonacci sequence is 1, 1, 2, 3, 5, 8, 13, 21... where each new number equals the sum of the previous two numbers.

The C++ program starts a loop that allows you to calculate the nth Fibonacci number in the sequence and to measure the time it takes to do so.

#### Running the program

It's a simple C++ file.

On Unix, use `g++ -o fib fib.cpp` to compile it and then `./fib` to run it.

On Windows it's easiest to get a C++ IDE like [Code::Blocks](http://www.codeblocks.org/).

#### Pseudo Code

The Fibonacci numbers can be calculated in two ways. One uses a recursive algorithm and one uses a dynamic programming algorithm. The pseudo code for each is listed below.

**Recursive Algorithm**

```
Algorithm fib_recursive(n)
  Input: integer n
  Output: nth Fibonacci number
  if n = 0 or 1 return 1
  return fib_recursive(n-2) + fib_recursive(n-1)
```

**Dynamic Programming Algorithm**

```
Algorithm fib_dynamic(n)
  Input: integer n
  Output: nth Fibonacci number
  if n = 0 or 1 return 1
  new array A
  A[0] <- 1
  A[1] <- 1
  for i from 2 to n
    A[i] <- A[i-2] + A[i-1]
  return A[n]
```

#### Experimental Time Analysis Results

I tried different values of n for each algorithm. The running time of each function call in microseconds is listed below.

n | Recursive | Dynamic
--- | --- | ---
1 | 0.0031184 | 0.0132312
10 | 0.453027 | 0.0468655
20 | 55.6782 | 0.0816157
30 | 6991.02 | 0.1130364
40 | 841255.5 | 0.1516468
50 | 100728807 | 0.1859212
60 | > 1 hour | 0.2209892

#### Dynamic

The dynamic programming algorithm has a time complexity of O(n). The program consists of constant time operations outside of the for loop, constant time operations inside the for loop, and a loop being executed n times.

You can see this well when the times are graphed:

![Dynamic n vs Time](https://christopher-siewert.github.io/fibonacci-time-analysis/img/dynamic.PNG)

The trendline has a very high R<sup>2</sup>, which indicates good fit and suggests my program scales linearly with n.

#### Recursive

The recurrence equation is T(n) = O(1) when n = 0 or 1. This is the base case. But for n > 1, T(n) = T(n-1) + T(n-2) + O(1). This is because each function call spawns 2 additional function calls, one to n-1 and one to n-2. Thus, the time to run the function for n is the sum of the time it takes to run n-1 and to run n-2. There is also a constant term for the addition.

I analyzed this equation using a recursive tree. Each node in the recursive tree corresponds to one function call.  You end up getting a binary tree like:
```
               f(n)
            /       \
     f(n-1)           f(n-2)
   /       \         /       \
f(n-2)   f(n-3)   f(n-3)   f(n-4)
```
The overhead at each node in this case is O(1). It does a simple addition between the results of the function calls. The running time for the whole algorithm is the sum of the overhead at each node. As the overhead is O(1) for each node, the running time for the entire tree will just be the number of nodes in the tree. Thus, if I can calculate a worst-case number of nodes in this tree, that will provide bounds on the worst-case running time.

This recursive tree will have height of O(n). This is easy to see. The max number of n on each level will be one less than the level above it. Thus, the max value of n on each level will range from n to 1.

The tree will also be binary. Each function call has at most 2 children.

A binary tree of height n has at most 2<sup>n+1</sup> - 1 nodes. Thus the number of nodes is O(2<sup>n</sup>), and the running time of this algorithm is O(2<sup>n</sup>).

This can be tested using induction.

Assume T(n) is O(2<sup>n</sup>)

Base case: T(1) is O(1) which is O(2<sup>1</sup>)

T(n) = T(n-1) + T(n-2) + O(1)

T(n+1) = O(2<sup>n</sup>)+ O(2<sup>n-1</sup>) + O(1) which is O(2<sup>n</sup>)

You can see the exponential running time in the following graphs:

![Recursive n vs Time](https://christopher-siewert.github.io/fibonacci-time-analysis/img/recursive.PNG)

![Recursive n (log scale) vs Time](https://christopher-siewert.github.io/fibonacci-time-analysis/img/recursive_log.PNG)

The R<sup>2</sup> is also extremely high, suggesting the exponential function is a good fit and my program was highly accurate.

Side note: After further research I discovered O(2<sup>n</sup>) was not a tight bound. The tight bound is O(1.6180<sup>n</sup>) according to [GeeksforGeeks](https://www.geeksforgeeks.org/time-complexity-recursive-fibonacci-program/). Interestingly, my line of best fit simplifies to (0.0026)(1.6323<sup>n</sup>) which is just slightly above the tight bound.

### Conclusion

The huge time save of the dynamic algorithm is stunning. If I extrapolate the exponential line of best fit, the predicted recursive running time for n=60 would be 15248640157.8 microseconds or 4.2 hours. It took the dynamic algorithm less than a microsecond. This speaks to the importance of algorithm design and choice. It demonstrates the large practical difference between polynomial time algorithms and exponential ones.

My results also showed the interesting trade offs in time complexity. My dynamic program was about 4 times slower for n=1. Therefore, a recursive solution works if the input is limited. Especially since they are often easier to code. But very quickly (n=10), the recursive solution becomes more time intensive than the linear algorithm.
