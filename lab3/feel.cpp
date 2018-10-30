#include <iostream>

int sum(int n);

int main()
{
    int n = 0;
    std::cout << "n = ";
    std::cin >> n;
    std::cout << "sum = " << sum(n) << std::endl;
    
    return 0;
}

int sum(int n)
{
    int count = 0;
    for (int i = 1; i <= n; i++) 
    {
        count += i;
    }
    return count;
}
