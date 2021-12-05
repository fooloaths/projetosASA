#include <iostream>
#include <vector>
#include <tuple>
#include <cstring>
#include <string.h>

//TESTING FUNCTIONS********************TESTING FUNCTIONS******************************************//
void printVector(std::vector<int> v){
    for(int i = 0; i < (int) v.size(); i++){
        printf("%d ", v[i]);
    }
    printf("\n");
}

std::vector<int> generateVector(int n){
    std::vector<int> v(n);
    for(int i = 0; i < n; i++){
        v.push_back(rand());
    }
    return v;
}
//**************************************TESTING FUNCTIONS*****************************************//

//abstraction of string processing
void stringProcessing(std::vector<int> &v){
  std::string str;  
  getline(std::cin, str);
  char *cstr = &str[0];
  char *ptr;
  ptr = strtok(cstr, " ");
  while (ptr != NULL && *ptr != '\n')
  { 
    v.push_back(atoi(ptr));
    ptr = strtok(NULL, " ");  
  }
}

//O(n^2) needs to be O(nlog(n))
//solves problem 1, finding the size and the number of longest increasing subsequences
//this is not the best algorithm, but it works for testing purposes
std::tuple<int, int> findLengthAndNumberOfLIS(std::vector<int> nums)
{
  //Base Case
  int n = nums.size();
  
  if (n == 0)
    return std::make_tuple(0, 0);
 
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

/* std::tuple<int, int> findLengthAndNumberOfLICS(std::vector<int> v1, std::vector<int> v2) {
} */

int main() {  
  std::vector<int> v1;
  std::vector<int> v2;
  int problemType;

  //scanf return value is how many arguments it read
  int p = scanf("%d\n", &problemType);
  //not sure what to handle here
  if (p != 1) {
    exit(1);
  }

  if (problemType == 1) {
    stringProcessing(v1);
    //SOLUTION
    auto result = findLengthAndNumberOfLIS(v1);
    printf("problema 1\n");
    printf("%d %d\n", std::get<0>(result), std::get<1>(result));
  }
  else if (problemType == 2) {
    stringProcessing(v1);
    stringProcessing(v2);
    //SOLUTION
    /*
    printf("problema 2\n");
    auto result = findLengthAndNumberOfLICS(v1, v2);
    printf("%d %d\n", std::get<0>(result), std::get<1>(result));
    */
  }
  return 0;
}