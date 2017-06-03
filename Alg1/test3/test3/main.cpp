#include <iostream>
#include <iomanip>
#include <utility>
#include <vector>
#include <algorithm>

typedef std::pair <int, int> thing;

bool operator < (thing const & a, thing const & b)
{
    double p1 = (double)a.first/a.second;
    double p2 = (double)b.first/b.second;
    if(p1 == p2) return a.second < b.second ? true: false;
    return p1 < p2 ? true: false;
}

bool myfunction (thing const & a, thing const & b) { return !(a<b); }



double get_max_amount(std::vector <thing> things, int amount) {

  double result=0;
  int i=0;

  std::sort(things.begin(), things.end(), myfunction );

  while (amount>0 && i<things.size()) {
      if(amount < things[i].second){
          result+= (double)things[i].first * amount / things[i].second;
          amount = 0;
      }else{
         result+= (double)things[i].first;
         amount-=things[i].second;
      }
      i++;
  }
  return result;
}

int main(void) {
  int count, amount;

  std::cin >> count >> amount;

  std::vector<thing> things(count);

  for (int i = 0; i < count; i++) {
    std::cin >> things[i].first >> things[i].second;
  }

  double result = get_max_amount(things, amount);

  std::cout << std::fixed <<  std::setprecision(3) << result << std::endl;
}
