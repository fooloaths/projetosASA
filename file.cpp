#include <iostream>
#include <vector>
#include <tuple>
#include <stdio.h>

//auxiliary function, will delete
//given a vector, print it's contents
void printVector(std::vector<int> v){
    for(int i = 0; i < (int) v.size(); i++){
        printf("%d ", v[i]);
    }
    printf("\n");
}

//O(n^2) needs to be O(nlog(n))
//solves problem 1, finding the size and the number of longest increasing subsequences
//this is not the best algorithm, but it works for testing purposes
std::tuple<int, int> findLengthAndNumberOfLIS(std::vector<int> nums)
{
  //Base Case
  if (nums.size() == 0)
    return std::make_tuple(0, 0);
 
  int n = nums.size();
 
  //Initialize dp_l array with
  // 1s
  std::vector<int> dp_l(n, 1);
 
  //Initialize dp_c array with
  // 1s
  std::vector<int> dp_c(n, 1);
 
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < i; j++)
    {
      //If current element is
      // smaller
      if (nums[i] <= nums[j])
        continue;
 
      if  (dp_l[j] + 1 > dp_l[i])
      {
        dp_l[i] = dp_l[j] + 1;
        dp_c[i] = dp_c[j];
      }
      else if (dp_l[j] + 1 == dp_l[i])
        dp_c[i] += dp_c[j];
    }
  }
 
  //Store the maximum element
  // from dp_l
  int max_length = 0;
 
  for (int i : dp_l)
    max_length = std::max(i,max_length);
 
  //Stores the count of LIS
  int count = 0;
 
  //Traverse dp_l and dp_c
  // simultaneously
  for(int i = 0; i < n; i++)
  {
    //Update the count
    if (dp_l[i] == max_length)
      count += dp_c[i];
  }
   
  //Return the count of LIS
  return std::make_tuple(max_length, count);
}

//solves problem 2
//i think this can be solved by mixing the longest common subsequence and longest increasing subsequence problems into one
//given two vectors, finds the size and number of longest common increasing subsequences
std::tuple<int, int> findLengthAndNumberOfLICS(std::vector<int> v1, std::vector<int> v2) {
}

int main() {
    //vectors for testing
    std::vector<int> v = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
    std::vector<int> v1 = {1, 2, 6, 3, 7};
    std::vector<int> v2 = {1, 2, 4, 7, 3};
    
    //FIXME: input doesn't work
    /*
    int problemType;
    char c = '-';
    

    std::cin >> problemType;

    c = getchar(); //Discard the '\n' at the end of first input
    while ((c = getchar()) != '\n') {
        if (c >= '0' && c <= '9') {
            v.push_back(c - '0');
        }
    }
    */


    //FIXME: implement switch statement for selecting problems

    auto result = findLengthAndNumberOfLIS(v);
    //problema 1
    printf("problema 1\n");
    printf("%d %d\n", std::get<0>(result), std::get<1>(result));
    //problema 2
    
    /*
    printf("problema 2\n");
    auto result = findLengthAndNumberOfLICS(v1, v2);
    printf("%d %d\n", std::get<0>(result), std::get<1>(result));
    */
    
    return 0;
}