#include<iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

unsigned long long int fib_recursive(int n);
unsigned long long int fib_dynamic(int n);

int main() {

    int option, n, times;

    cout << "This program calculates the running time of finding Fibonacci numbers\n"
         << "using two different algorithms; a recursive algorithm and an iterative\n"
         << "dynamic programming algorithm. Which algorithm do you want to try?\n";

    while (1) { /// loop forever

        cout << "\nEnter 1 for recursive and 2 for dynamic programming: ";
        cin >> option;

        cout << "\nNow enter which Fibonacci number you want to calculate: ";
        cin >> n;

        cout << "\nNow enter the number of times to preform the calculation "
         << "(in order to find an average running time): ";
        cin >> times;


        high_resolution_clock::time_point t1 = high_resolution_clock::now(); /// Start time

        unsigned long long int result;

        if (option == 1) { /// recursive
            for (int i = 0; i < times; i++) {
                result = fib_recursive(n);
            }
        } else if (option == 2) { /// dynamic programming
            for (int i = 0; i < times; i++) {
                result = fib_dynamic(n);
            }
        }

        high_resolution_clock::time_point t2 = high_resolution_clock::now(); /// End time

        auto duration = duration_cast<microseconds>( t2 - t1 ).count(); /// To microseconds

        cout << "\nFibonacci number " << n << " is " << result;
        cout << "\nEach function took " << static_cast<double>(duration)/times << " microseconds.\n";
    }

    return 0;
}

unsigned long long int fib_recursive(int n) {
    /// if n == 0 or n == 1
    if(n <= 1)
        return 1;
    /// Else return sum of 2 previous values
    return fib_recursive(n-1) + fib_recursive(n-2);
}

unsigned long long int fib_dynamic(int n) {
    unsigned long long int f[n+1]; /// array for values
    f[0] = 1;
    f[1] = 1;
    /// Loop from 2 to n
    for(int i = 2; i <= n; i++) {
        f[i] = f[i-1] + f[i-2]; /// Equals sum of previous 2
    }
    return f[n];
}
