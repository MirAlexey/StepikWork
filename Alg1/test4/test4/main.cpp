#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int number;
    std::vector<int> numbers;
    int num = 0;

    std::cin >> number;

    while(number>0){
        num++;
        if(number - num > num){
            number-=num;
            numbers.push_back(num);
        }else{
            numbers.push_back(number);
            number = 0;
        }
    }

    std::cout << numbers.size() << std::endl;
    for (int i = 0; i < numbers.size(); i++) {
      std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}

