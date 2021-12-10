#include <iostream>
#include <vector>
#include <tuple>
#include <cstring>
#include <string.h>

//TESTING FUNCTIONS********************TESTING FUNCTIONS******************************************//
void printVector(std::vector<std::tuple<int, int>> v){
    for (long unsigned int i = 0; i <  v.size(); i++) {
        printf("%d %d\n", std::get<0>(v[i]), std::get<1>(v[i]));
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

void printVector2(std::vector<std::vector<std::tuple<int, int>>> arr) {
  printf("###############################################################\n");
  printf("            Curent Vector Representation\n");
  printf("###############################################################\n");
  int nlevels = arr.size();
  for (int i = 0; i < nlevels; i++) {
    printf("%d | ", i + 1);
    std::vector<std::tuple<int, int>> ithlevel = arr[i];
    int sizeLevel = ithlevel.size();
    for (int j = 0; j < sizeLevel; j++) {
        printf("(%d, %d), ", std::get<0>(ithlevel[j]), std::get<1>(ithlevel[j]));
    }
    printf("\n");
  }
  printf("###############################################################\n");
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

void insert(std::vector<std::tuple<int, int>> &arr, std::tuple<int, int> t) {
  int cmp = std::get<0>(t);
  for (long unsigned int i = 0; i <  arr.size(); i++) {
    if (std::get<0>(arr[i]) < cmp) {
      arr.insert(arr.begin() + i, t);
      break;
    } 
  }
}

int count(std::vector<std::tuple<int, int>> pares, int k) {
    int sizeLIS = pares.size();
    int counter = 0;
    int j = sizeLIS - 1;
    while ((j > 0) && (std::get<0>(pares[j]) < k)) {
      counter += std::get<1>(pares[j]);
      j--;
    }
    return counter;
} 

void processValue(std::vector<std::vector<std::tuple<int, int>>> &arr, int k) {
  int size = arr.size();
  for (int i = size - 1; i > 0; i--) {

    auto pares = arr[i];
    // int sizeLIS = pares.size(); //Ver se este é um bom nome de variável

    auto counter = count(pares, k);
    if (counter > 0) {
      if (i < size) { //Is within bounds
        insert(arr[i + 1], std::make_tuple(k, counter));
        break;
      }
      else {
        std::vector<std::tuple<int, int>> tmp = std::vector<std::tuple<int, int>>();
        tmp.push_back(std::make_tuple(k, counter));
        arr.push_back(tmp);
        insert(arr[i + 1], std::make_tuple(k, counter));
        break;
      }
    }
  }
}

std::tuple<int, int> problem1(std::vector<int> nums) {
  int size = nums.size();
  auto aux = std::vector<std::vector<std::tuple<int, int>>>();

  if (size > 0) {
    auto t = std::make_tuple(nums.at(0),1);
    auto tmp = std::vector<std::tuple<int,int>>();
    tmp.push_back(t);
    aux.push_back(tmp);
  }

  auto firstLevel = aux[0];

  for (int i = 0; i < size; i++) {
    int k = nums[i];
    int sizeFirstLevel = firstLevel.size();
    
    if (k < std::get<1>(firstLevel[sizeFirstLevel - 1]))  {//Se isto não der para fazer com tuplos, troca os tuplos por arrays com 2 elementos
      //Smaller than all LIS on this level (smallest pair is always at last index)
      firstLevel.push_back(std::make_tuple(k, 1));
      continue;
    }

    processValue(aux, k); 
  }
  
  // aí talvez seja melhor fazermos um for loop extra, em que percorres só o último nível 
  // do aux e vais somando numa variável todas as segundas entradas dos tuplos nesse nível

  //TODO abstract as a function
  printVector2(aux);
  int auxLastLevelIndex = aux.size() - 1;
  auto auxLastLevel = aux[auxLastLevelIndex];
  int sum = 0;
  for (long unsigned int i = 0; i <  auxLastLevel.size(); i++) {
    sum += std::get<1>(auxLastLevel[i]);
  }

  return std::make_tuple(auxLastLevelIndex, sum);
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
    auto result = problem1(v1);
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