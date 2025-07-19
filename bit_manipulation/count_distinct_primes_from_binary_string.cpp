/**
 * @file count_distinct_primes_from_binary_string.cpp
 * @brief Count distinct prime numbers from a binary string using allowed operations.
 * 
 * @author Rudraksh Tank
 * @date July 2025
 *
 * @details
 * From a given binary string, generate all unique prime numbers = 2^n - 1
 * under the following operations any number of times:
 * - Swap any 2 digits
 * - Turning any '1' into '0' (but not vice versa)
 *
 * Efficient approach using bitmasking and Sieve of Eratosthenes.
 * 
 * Tags: Bit Manipulation, Prime Numbers, Combinatorics, Greedy
 */
#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

const int MAX = 1e6;
std::vector<bool> is_prime;

/**
 * @brief Precompute all primes up to MAX using Sieve of Eratosthenes.
 */
void precomputePrimes() {
    is_prime.assign(MAX + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= MAX; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= MAX; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

/**
 * @brief Count distinct primes that can be formed from the binary string.
 * @param s Binary string input
 * @return Total count of distinct primes that can be formed
 */
int countPrimeBinaryStrings(const std::string &s) {
    int n = s.length();
    int k = std::count(s.begin(), s.end(), '1'); // number of set bits in initial string
    int limit = ((1 << k) - 1) << (n - k); // max number possible after moving all k one's to the left

    std::unordered_set<int> seen;
    int cnt = 0;

    for (int i = 2; i < limit; ++i) {
        if (__builtin_popcount(i) <= k && is_prime[i]) {
            if (!seen.count(i)) {
                seen.insert(i);
                ++cnt;
            }
        }
    }

    return cnt;
}

/**
 * @brief Main driver function
 */
int main() {
    precomputePrimes();

    // Example test case-1
    std::string s1 = "10101";
    std::cout << "Input: " << s1 << "\n";
    std::cout << "Distinct primes: " << countPrimeBinaryStrings(s1) << "\n\n";

    // Input from user
    std::string s;
    std::cout << "Enter binary string: ";
    std::cin >> s;
    std::cout << countPrimeBinaryStrings(s) << std::endl;

    return 0;
}

