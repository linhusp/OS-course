#include <iostream>

void print_arr()
{
    int n = 0;
    std::cout << "n = ";
    std::cin >> n;

    int arr[n];
    int count = 0;
    
    for (int i = 0; i < n; i++) 
    {
        std::cout << "arr[" << i << "] = ";
        std::cin >> arr[i];
        count += arr[i];
    }

    std::cout << "sum = " << count << std::endl;
}

int main()
{
    print_arr();
    return 0;
}
