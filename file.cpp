#include <iostream>
#include <vector>
#include <tuple>
#include <set>
#include <cstring>

#define DUPLICATE -1

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


void insert(std::vector<std::tuple<int, int>> &arr, std::tuple<int, int> t) {
  int cmp = std::get<0>(t);

  if (std::get<0>(arr[arr.size() - 1]) > cmp) { //If it is smaller than the smallest tuple on this level
    arr.push_back(t);
  }
  for (long unsigned int i = 0; i < arr.size(); i++) {
    if (std::get<0>(arr[i]) == cmp) {
      arr[i].swap(t);
      break;
    }
    else if (std::get<0>(arr[i]) < cmp) {
      arr.insert(arr.begin() + i, t);
      break;
    } 
  }
}

int count(std::vector<std::tuple<int, int>> &pares, int k) {
    int sizeLIS = pares.size();
    int counter = 0;
    int j = sizeLIS - 1;    
    while ((j >= 0) && (std::get<0>(pares[j]) < k)) {
      counter += std::get<1>(pares[j]);
      j--;
    }
    if (std::get<0>(pares[j]) == k && counter == 0) {
      pares.insert(pares.begin() + j, pares[j]);
      return DUPLICATE;
    }
    return counter;
}

int tupleInLevel(int k, std::vector<std::tuple<int, int>> &arr) {

  int size = arr.size() - 1;  
  for (int i = 0; i < size; i++) {
    if (std::get<0>(arr[i]) == k) {
      return std::get<1>(arr[i]);
    }
  }
  return 0;
}

void processValue(std::vector<std::vector<std::tuple<int, int>>> &arr, int k) {
  int size = arr.size();
  for (int i = size - 1; i >= 0; i--) {
    auto pares = arr[i];
    if (k < std::get<0>(pares[pares.size() - 1])) {
      continue;
    }
    
    auto counter = count(arr[i], k);
    if (counter == DUPLICATE) {
      break;
    }
    if (counter > 0) {
      if (i < (size - 1)) { //Is within bounds
        insert(arr[i + 1], std::make_tuple(k, counter));
        break;
      }
      else {
        std::vector<std::tuple<int, int>> tmp = std::vector<std::tuple<int, int>>();
        tmp.push_back(std::make_tuple(k, counter));
        arr.push_back(tmp);
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

  for (int i = 1; i < size; i++) {
    int k = nums[i];
    int sizeFirstLevel = aux[0].size();

    if (k < std::get<0>(aux[0][sizeFirstLevel - 1]))  {
      //Smaller than all LIS on this level (smallest pair is always at last index)
      aux[0].push_back(std::make_tuple(k, 1));
      continue;
    }

    processValue(aux, k);
  }
  
  int auxLastLevelIndex = aux.size() - 1;
  auto auxLastLevel = aux[auxLastLevelIndex];
  int sum = 0;
  for (long unsigned int i = 0; i <  auxLastLevel.size(); i++) {
    sum += std::get<1>(auxLastLevel[i]);
  }

  return std::make_tuple(auxLastLevelIndex + 1, sum);
}

std::set<std::vector<int>> mergeSets(std::set<std::vector<int>> &a, std::set<std::vector<int>> &b) {
  for (auto subseq : b) {
    a.insert(subseq);
  }
  return a;
}

std::set<std::vector<int>> extendSequences(std::set<std::vector<int>> &a, int value) {
  std::set<std::vector<int>> result;
  for (auto subseq : a) {
    if (subseq[subseq.size() - 1] >= value) {
      continue; //Value can't extend this subsequence
    }
    else {
      subseq.push_back(value);
      result.insert(subseq);
    }
  }
  if (result.size() == 0) {
    result = a;
  }
  return result;
}

std::set<std::vector<int>> findAllLCS(std::vector<std::vector<int>> matrix, int i, int j, std::vector<int> n, std::vector<int> m) {

  if (j == 1 || i == 1 || (((long unsigned int) i <= n.size() && (long unsigned int) j <= m.size()) && matrix[i][j] == 0)) {
    std::set<std::vector<int>> emptySet;
    return emptySet;
  }
  else if (n[i - 2] != m[j - 2]) { //If matrix[i][j] was computed from cell directly above or to the left

    std::set<std::vector<int>> a;
    std::set<std::vector<int>> b;
    a = findAllLCS(matrix, i - 1, j, n, m);
    b = findAllLCS(matrix, i, j - 1, n, m);
    a = mergeSets(a,b);

    return a;
  }
  else {
    int value = n[i - 2]; //Value to be appended to the end of the subsequence

    std::set<std::vector<int>> a = findAllLCS(matrix, i - 1, j - 1, n, m);
    //Combine results
    std::set<std::vector<int>> result;
    if (a.size() != 0) {
      result = extendSequences(a, value);
    }
    else {
      std::vector<int> seq = std::vector<int>();
      seq.push_back(value);
      a.insert(seq);
      result = a;
    }
    return result;
  }
}

std::vector<std::vector<int>>  computeLCSMatrix(std::vector<int> v1, std::vector<int> v2) {

  std::vector<std::vector<int>> matrix(v1.size() + 1, std::vector<int>(v2.size() + 1, 0));
  for (long unsigned int i = 0; i <= v1.size(); i++) {
    for (long unsigned int j = 0; j <= v2.size(); j++) {
      if (i == 0 || j == 0) {
        matrix[i][j] = 0; 
      }
      else if (v1[i - 1] == v2[j - 1]) {
        matrix[i][j] = matrix[i - 1][j - 1] + 1;
      }
      else {
        matrix[i][j] = std::max(matrix[i - 1][j], matrix[i][j - 1]);
      }
    }
  }
  return matrix;
}

//given two vectors, find the longest common subsequence
int problem2(std::vector<int> v1, std::vector<int> v2) {
  
  std::vector<std::vector<int>> matrix = computeLCSMatrix(v1, v2);

  if (matrix[v1.size()][v2.size()] == 0) { //If there is no common subsequence
    return 0;
  }
  if (v1.size() == v2.size() && (long unsigned int) matrix[v1.size()][v2.size()] == v1.size()) {
    //If v1 is the same sequence as v2
    return matrix[v1.size()][v2.size()];
  }

  std::set<std::vector<int>> LCIS = findAllLCS(matrix, v1.size() + 1, v2.size() + 1, v1, v2);
  long unsigned int maxSize = 0;
  for (auto subseq : LCIS) {      //Temos de testar com vários inputs. Não sei se todas estas subSeqs são estritamente crescentes
    if (subseq.size() > maxSize) { //Tb não estou sure se têm todas o mesmo tamanho. Se a resposta a ambas for sim,
      maxSize = subseq.size();    //basta dar return de o size de 1 delas, em vez de percorrer todas
    }
  }
  return maxSize;
}


int main() {  
  std::vector<int> v1;
  std::vector<int> v2;
  int problemType;

  int p = scanf("%d\n", &problemType);
  if (p != 1) { return(1); }

  if (problemType == 1) {
    stringProcessing(v1);
    auto result = problem1(v1);
    printf("%d %d\n", std::get<0>(result), std::get<1>(result));
  }
  else if (problemType == 2) {
    stringProcessing(v1);
    stringProcessing(v2);
    auto result = problem2(v1, v2);
    printf("%d\n", result);
  }
  else { return -1;}
  return 0;
}
