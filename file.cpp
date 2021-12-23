#include <iostream>
#include <vector>
#include <algorithm>

#define DUPLICATE -1

void stringProcessing(std::vector<int> &v) {
  int c, num, digit, isNegative;

  num = 0;
  digit = 0;
  isNegative = 0;
  while (((c = getchar()) != EOF) && (c != '\n')) {
    if (c == '-') {
      isNegative = 1;
    }
    if (('0' <= c) && (c <= '9')) {
      digit = c - '0';
      num = num * 10 + digit;
    }
    if (c == ' ') {
      if (isNegative) {
        num *= -1;
        isNegative = 0;
      }
      v.push_back(num);
      num = 0;
    }
  }
  if (isNegative) {
    num *= -1;
  }
  v.push_back(num);
  num = 0;
}

void populatePair(int value, int frequency, std::vector<int> &v) {
  v.push_back(value);
  v.push_back(frequency);
}

void insert(std::vector<std::vector<int>> &arr, std::vector<int> pair) {
  int cmp = pair[0];

  if (arr[arr.size() - 1][0] > cmp) { //If it is smaller than the smallest tuple on this level
    arr.push_back(pair);
  }
  for (long unsigned int i = 0; i < arr.size(); i++) {
    if (arr[i][0] == cmp) {
      arr[i] = pair;
      break;
    }
    else if (arr[i][0] < cmp) {
      arr.insert(arr.begin() + i, pair);
      break;
    } 
  }
}

int count(std::vector<std::vector<int>> &pares, int k) {
    int sizeLIS = pares.size();
    int counter = 0;
    int j = sizeLIS - 1;

    while ((j >= 0) && (pares[j][0]) < k) {
      counter += pares[j][1];
      j--;
    }
    if (j < 0) {j++;}
    if (pares[j][0] == k && counter == 0) {
      pares.insert(pares.begin() + j, pares[j]);
      return DUPLICATE;
    }

void processValue(std::vector<std::vector<std::tuple<int, int>>> &arr, int k) {
  int size = arr.size();

  for (int i = size - 1; i >= 0; i--) {
    auto pares = arr[i];

    if (k < pares[pares.size() - 1][0]) {
      continue;
    }
    
    auto counter = count(arr[i], k);
    if (counter == DUPLICATE) {
      break;
    }
    if (counter > 0) {
      if (i < (size - 1)) { //Is within bounds
        std::vector<int> pair = std::vector<int>();
        populatePair(k, counter, pair);
        insert(arr[i + 1], pair);
        break;
      }
      else {
        std::vector<std::vector<int>> tmp = std::vector<std::vector<int>>();
        std::vector<int> pair = std::vector<int>();
        populatePair(k, counter, pair);
        tmp.push_back(pair);
        arr.push_back(tmp);
        break;
      }
    }
  }
}

std::vector<int> problem1(std::vector<int> nums) {
  int size = nums.size();
  auto aux = std::vector<std::vector<std::vector<int>>>();

  if (size > 0) {
    std::vector<int> pair = std::vector<int>();
    populatePair(nums.at(0), 1, pair);
    auto tmp = std::vector<std::vector<int>>();
    tmp.push_back(pair);
    aux.push_back(tmp);
  }

  for (int i = 1; i < size; i++) {
    int k = nums[i];
    int sizeFirstLevel = aux[0].size();

    if (k < aux[0][sizeFirstLevel - 1][0])  {
      //Smaller than all LIS on this level (smallest pair is always at last index)
      std::vector<int> p = std::vector<int>();
      populatePair(k, 1, p);
      aux[0].push_back(p);
      continue;
    }

    processValue(aux, k);
  }

  int auxLastLevelIndex = aux.size() - 1;
  auto auxLastLevel = aux[auxLastLevelIndex];
  int sum = 0;
  for (long unsigned int i = 0; i <  auxLastLevel.size(); i++) {
    sum += auxLastLevel[i][1];
  }

  std::vector<int> result = std::vector<int>();
  populatePair(auxLastLevelIndex + 1, sum, result);
  return result;
}

int problem2(std::vector<int> v1, std::vector<int> v2) {
  std::vector<int> lcisTable = std::vector<int>(v2.size(), 0);
  for (long unsigned int i = 0; i < v1.size(); i++) {
    int curLen = 0;
    for (long unsigned int k = 0; k < v2.size(); k++) {
      if ((v1.at(i) == v2.at(k)) && (curLen + 1 > lcisTable.at(k))) {
        lcisTable.at(k) = curLen + 1;
      }
      if ((v1.at(i) > v2.at(k)) && (lcisTable.at(k) > curLen)) {
        curLen = lcisTable.at(k);
      }
    }
  } 
  return *std::max_element(lcisTable.begin(), lcisTable.end());
}

int main() {  
  std::vector<int> v1 = std::vector<int>();
  std::vector<int> v2 = std::vector<int>();
  int problemType;

  int p = scanf("%d\n", &problemType);
  if (p != 1) { return(1); }

  if (problemType == 1) {
    //v1 = stringProcessing();
    stringProcessing(v1);
    auto result = problem1(v1);
    printf("%d %d\n", result[0], result[1]);
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
