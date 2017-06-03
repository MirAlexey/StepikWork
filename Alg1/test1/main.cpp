#include <cassert>
#include <iostream>

class Fibonacci {
 public:
  static int get_remainder(long long n, int m) {
    assert(n >= 1);
    assert(m >= 2);
    // put your code here
      int a2=1 ,a3;
      long long a1=0;
      int ost=1, p, num=n;
      long long i = 2, j=1;
      if (n>2){
          while(a2>0){
              a3 = a2;
              a2 = (a1+a2)% m ;
              a1 = a3;

              i++;
          }
          while(a1%m !=1){
              a1=(a1*a3);
              j++;
          }

          p = (i-1)*j;
          std::cout << "P=" << p<< " ost=";
          num = n%p;

      }
      a1=0, a2=1;
      if(num < 2){
          n= num==0?0:1;
      }else{
        for(int k = 2; k< num+1 ; k++){
            a3 = a2;
            a2 = (a1+a2)% m ;
            a1 = a3;
        }
        n=a2;
      }
    return n % m;

  }
};

int main(void) {
  long long n;
  int m;
  //std::cin >> n >> m;
  //std::cout << Fibonacci::get_remainder(n, m) << std::endl;
  std::cout << Fibonacci::get_remainder(1, 2) << std::endl;
  std::cout << Fibonacci::get_remainder(2, 2) << std::endl;
  std::cout << Fibonacci::get_remainder(3, 2) << std::endl;
  std::cout << Fibonacci::get_remainder(4, 2) << std::endl;
  std::cout << Fibonacci::get_remainder(5, 2) << std::endl;
  std::cout << Fibonacci::get_remainder(6, 2) << std::endl;
  std::cout << Fibonacci::get_remainder(7, 2) << std::endl;
  std::cout << Fibonacci::get_remainder(8, 2) << std::endl;
  std::cout << Fibonacci::get_remainder(9, 2) << std::endl;
  std::cout << Fibonacci::get_remainder(10, 2) << std::endl;
  std::cout  << "--------------" << std::endl;

  std::cout << Fibonacci::get_remainder(9, 2) << std::endl;
  std::cout << Fibonacci::get_remainder(9, 3) << std::endl;
  std::cout << Fibonacci::get_remainder(9, 4) << std::endl;
  std::cout << Fibonacci::get_remainder(9, 5) << std::endl;
  std::cout << Fibonacci::get_remainder(9, 6) << std::endl;
  std::cout << Fibonacci::get_remainder(9, 7) << std::endl;
  std::cout << Fibonacci::get_remainder(9, 8) << std::endl;
  std::cout << Fibonacci::get_remainder(9, 9) << std::endl;
  std::cout << Fibonacci::get_remainder(9, 10) << std::endl;
  std::cout  <<"--------------" << std::endl;
  std::cout << Fibonacci::get_remainder(900, 35) << std::endl;
  std::cout << Fibonacci::get_remainder(9000, 187) << std::endl;
  std::cout << Fibonacci::get_remainder(9000000, 6871) << std::endl;
  std::cout  <<"--------------" << std::endl;
  std::cout << Fibonacci::get_remainder(50, 99999) << std::endl;
  return 0;
}
