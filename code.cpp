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