#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

typedef std::pair <int, int> Segment;

bool operator < (Segment const & a, Segment const & b)
{
    return a.second < b.second ? true: false;
}
bool operator > (Segment const & a, Segment const & b)
{
    return a.second > b.second ? true: false;
}
bool operator <= (Segment const & a, Segment const & b)
{
    return a.second <= b.second ? true: false;
}
bool operator >= (Segment const & a, Segment const & b)
{
    return a.second >= b.second ? true: false;
}
bool operator == (Segment const & a, Segment const & b)
{
    return a.second == b.second && a.first == b.first ? true: false;
}
bool operator == (Segment const & a, int const & b)
{
    return a.first <= b && a.second >= b ? true: false;
}
bool operator != (Segment const & a, int const & b)
{
    return a.first > b || a.second < b ? true: false;
}
bool myfunction (Segment const & a, Segment const & b) { return (a<b); }



std::vector <int> get_covering_set(std::vector <Segment> segments) {
  std::vector <int> result;

  // fix this function
  std::vector <Segment> segments2;

  std::sort(segments.begin(), segments.end(), myfunction );
  while (segments.size()>0) {
      result.push_back(segments[0].second);
      for (std::vector <Segment>::iterator it = segments.begin(); it != segments.end(); ++it) {
          if (*it!=result.back()){
             segments2.push_back(*it); ;
          }
      }
      segments = segments2;
      segments2.clear();
  }
  return result;
}

int main(void) {
  int segments_count;
  std::cin >> segments_count;
  std::vector <Segment> segments(segments_count);
  for (int i = 0; i < segments_count; i++) {
    std::cin >> segments[i].first >> segments[i].second;
  }

  std::vector <int> points = get_covering_set(segments);
  std::cout << points.size() << std::endl;
  for (std::size_t i = 0; i < points.size(); i++) {
    std::cout << points[i] << " ";
  }
  std::cout << std::endl;
}
