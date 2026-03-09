# DSA — Maximum Stock Profit (Multiple Transactions)

A focused C++ implementation of one of the most well-known greedy problems in DSA — **maximizing profit from stock prices** when unlimited buy-sell transactions are allowed. This is the canonical **"Best Time to Buy and Sell Stock II"** problem, a staple of FAANG interviews and competitive programming, and one of the cleanest demonstrations of why a greedy strategy can be provably optimal.

---

## Problem Statement

Given an array of stock prices where `prices[i]` is the price on day `i`, find the **maximum total profit** you can achieve.

**Rules:**
- You may complete **as many transactions as you like**
- You must **sell before you buy again** (no overlapping holds)
- You may buy and sell on the **same day**

**Example Input:**
```
Enter number of days: 6
Enter stock prices for 6 days: 7 1 5 3 6 4
```

**Example Output:**
```
Maximum total profit: 7
```

*(Buy at 1, sell at 5 → profit 4. Buy at 3, sell at 6 → profit 3. Total = 7)*

---

## The Code

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;
    cout << "Enter number of days: ";
    cin >> n;

    vector<int> prices(n);
    cout << "Enter stock prices for " << n << " days: ";
    for (int i = 0; i < n; i++)
    {
        cin >> prices[i];
    }

    int maxProfit = 0;
    for (int i = 1; i < n; i++)
    {
        if (prices[i] > prices[i - 1])
        {
            maxProfit += prices[i] - prices[i - 1];
        }
    }

    cout << "Maximum total profit: " << maxProfit;
    return 0;
}
```

---

## The Core Insight — Valley-Peak = Sum of Positive Differences

At first glance, this problem seems to require finding every valley (buy point) and every peak (sell point). But there's a far more elegant observation:

**The profit from buying at a valley and selling at a peak equals the sum of all positive day-to-day differences in between.**

Formally, for any interval `[l, r]`:

```
prices[r] - prices[l] = (prices[l+1] - prices[l])
                      + (prices[l+2] - prices[l+1])
                      + ...
                      + (prices[r]   - prices[r-1])
```

This means instead of finding optimal buy-sell windows, we can simply **accumulate every positive daily increment**. The code does exactly this — if today's price is higher than yesterday's, add the difference. If it's lower or equal, skip it.

**This is a greedy strategy — and it is provably optimal.**

---

## Visual Walkthrough

**Prices:** `7 → 1 → 5 → 3 → 6 → 4`

```
Price
  7 |  *
  6 |                 *
  5 |        *
  4 |                       *
  3 |              *
  2 |
  1 |     *
     D1   D2   D3   D4   D5   D6
```

| Day Pair | Difference | Profitable? | Added to Profit |
|----------|------------|-------------|-----------------|
| D1 → D2  | 1 - 7 = -6 | ❌          | 0               |
| D2 → D3  | 5 - 1 = +4 | ✅          | 4               |
| D3 → D4  | 3 - 5 = -2 | ❌          | 0               |
| D4 → D5  | 6 - 3 = +3 | ✅          | 3               |
| D5 → D6  | 4 - 6 = -2 | ❌          | 0               |

**Total Profit: 4 + 3 = 7** ✅

---

## Complexity Analysis

| Metric | Complexity |
|--------|------------|
| Time   | **O(n)** — single pass through the prices array |
| Space  | **O(n)** — `std::vector<int>` stores all `n` prices |

> **Space note:** The vector is necessary here since all prices are read before processing. If prices could be read and processed in a streaming fashion (one at a time), space could be reduced to **O(1)** by tracking only the previous price.

---

## Dry Run

**Input:** `prices = {1, 2, 3, 4, 5}` (strictly increasing)

| `i` | `prices[i]` | `prices[i-1]` | Diff | `maxProfit` |
|-----|-------------|---------------|------|-------------|
| 1   | 2           | 1             | +1   | 1           |
| 2   | 3           | 2             | +1   | 2           |
| 3   | 4           | 3             | +1   | 3           |
| 4   | 5           | 4             | +1   | 4           |

**Output:** `Maximum total profit: 4`

*(Equivalent to buying on Day 1 at price 1 and selling on Day 5 at price 5)*

---

## Edge Cases

| Scenario | Behavior |
|----------|----------|
| Strictly decreasing prices `{5, 4, 3, 2, 1}` | No positive difference exists — `maxProfit = 0`. Correct: best action is to not trade |
| All prices equal `{3, 3, 3, 3}` | All differences are `0` — `maxProfit = 0`. Correct |
| Single day `n = 1` | Loop doesn't execute — `maxProfit = 0`. Correct: can't sell without a future day |
| Two days, increasing `{2, 5}` | One transaction: profit = 3 |
| Two days, decreasing `{5, 2}` | No trade: profit = 0 |

---

## Why Not Just Buy Low, Sell High Manually?

An intuitive approach might be:
- Find every local minimum (buy)
- Find the next local maximum (sell)
- Repeat

This works but requires valley-peak detection logic. The greedy approach here achieves **the exact same result** in a single pass with a two-line condition — because the telescoping sum property guarantees it.

Both approaches yield identical profit. The greedy one is just cleaner, shorter, and faster to reason about.

---

## Comparison with Related Stock Problems

This problem is part of a well-known family. Knowing where it sits helps:

| Problem | Constraint | Strategy | Difficulty |
|---------|------------|----------|------------|
| Stock I (LeetCode #121) | One transaction only | Track running min, compute max spread | Easy |
| **Stock II (this repo)** | **Unlimited transactions** | **Greedy — sum all positive diffs** | **Easy** |
| Stock III (LeetCode #123) | At most 2 transactions | DP with state machine | Medium |
| Stock IV (LeetCode #188) | At most k transactions | DP generalized | Hard |
| Stock with Cooldown (#309) | 1-day cooldown after sell | DP with cooldown state | Medium |
| Stock with Fee (#714) | Transaction fee per trade | Greedy modified | Medium |

Understanding Stock II deeply is the foundation for solving all the harder variants.

---

## Repository Structure

```
DSA-Stock-Max-Profit/
│
├── stock_profit.cpp      # Main C++ implementation
└── README.md             # Project documentation
```

---

## How to Compile and Run

**Prerequisites:** GCC / G++ (C++11 or later for `std::vector`)

```bash
# Clone the repository
git clone https://github.com/rishita-ops/DSA-Stock-Max-Profit.git
cd DSA-Stock-Max-Profit

# Compile
g++ -std=c++11 stock_profit.cpp -o stock_profit

# Run
./stock_profit
```

**On Windows:**
```bash
g++ -std=c++11 stock_profit.cpp -o stock_profit.exe
stock_profit.exe
```

---

## Key Concepts Covered

- **Greedy algorithm** — locally optimal choices (capture every upward move) lead to a globally optimal solution
- **Telescoping sums** — the mathematical property that allows valley-peak profit to be decomposed into daily differences
- **`std::vector`** — dynamic array from the C++ STL, correctly used here over VLA for portability
- **Single-pass linear scan** — O(n) traversal with no backtracking or lookahead
- **Profit maximization under constraints** — a foundational pattern in financial, scheduling, and resource allocation problems

---

## Contributing

Contributions are welcome. Consider adding:
- A **valley-peak approach** version for explicit comparison
- A version that also **prints each buy/sell transaction** with dates and prices
- Implementations in Python, Java, or JavaScript
- Unit tests covering all edge cases

```bash
git checkout -b feature/your-feature
git commit -m "Add: your feature description"
git push origin feature/your-feature
# Then open a Pull Request
```

---

## License

This project is open-source and available under the [MIT License](LICENSE).

---

*Part of a structured DSA practice series — fundamentals, done right.*
