#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

#define DUPLICATE -1
#define V1 1
#define V2 2

/*void printPair(std::vector<int> t) {
  if (t.size() == 2) {
    printf("[%d, %d]", t[0], t[1]);
  }
  else {
    printf("Estavamos à espera de um par, mas recebemos algo diferente\n");
  }
}*/

void stringProcessing(std::vector<int> &v, std::unordered_map<int, int> &map, int context) {
  int c, num, digit, isNegative, isNumber;

  num = 0;
  digit = 0;
  isNegative = 0;
  isNumber = 0;
  while (((c = getchar()) != EOF) && (c != '\n')) {
    if (c == '-') {
      isNegative = 1;
    }
    if (('0' <= c) && (c <= '9')) {
      isNumber = 1;
      digit = c - '0';
      num = num * 10 + digit;
    }
    if (c == ' ' && isNumber) {
      if (isNegative) {
        num *= -1;
        isNegative = 0;
      }
      if (context == V1 || ((context == V2) && (map[num] == -1))) {
        v.push_back(num);
        map[num] = -1;
      }
      num = 0;
      isNumber = 0;
    }
  }
  if (context == V1) {
    map[num] = -1;
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

  //printf("O par é "); printPair(pair); printf("\n");
  if (arr[arr.size() - 1][0] > cmp) { //If it is smaller than the smallest tuple on this level
    arr.push_back(pair);
  }
  for (long unsigned int i = 0; i < arr.size(); i++) {
    if (arr[i][0] == cmp) {
      long unsigned int j = i;
      if (((i + 1) < arr.size()) && (arr[i + 1][0] == cmp)) {
        j++;
      }
      //printf("Estamos no par nº %ld\n", i);
      //printf("aaaaaaaaaaa\nVamos meter no par "); printPair(arr[i]); printf(" o par "); printPair(pair);
      arr[j] = pair;
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
      //if (pares[j][0] < k) { //Conditional is a hack to prevent problems with insert at line 86
        counter += pares[j][1];
      //}
      j--;
    }
    if (j < 0) {j++;}
    if (pares[j][0] == k && counter == 0) {
      pares.insert(pares.begin() + j, pares[j]);
      return DUPLICATE;
    }
    return counter;
}

void processValue(std::vector<std::vector<std::vector<int>>> &arr, int k) {
  int size = arr.size();

  for (int i = size - 1; i >= 0; i--) {
    auto pares = arr[i];
    
    if (k < pares[pares.size() - 1][0]) {
      continue;
    }
    
    auto counter = count(arr[i], k);
    if (counter == DUPLICATE) {
      if (i > 0) { //If it isn't the lowest level
        counter = count(arr[i - 1], k);
        std::vector<int> pair = std::vector<int>();
        populatePair(k, counter, pair);
        insert(arr[i], pair);
      }
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
  for (auto value : v1) {
    int currentLength = 0;
    for (long unsigned int k = 0; k < v2.size(); k++) {
      if ((value == v2[k]) && ((currentLength + 1) > lcisTable[k])) {
        lcisTable[k] = currentLength + 1;
      }
      if ((value > v2[k]) && (lcisTable[k] > currentLength)) {
        currentLength = lcisTable[k];
      }
    }
  }
  return *std::max_element(lcisTable.begin(), lcisTable.end());
}

int main() {  
  std::vector<int> v1 = std::vector<int>();
  std::vector<int> v2 = std::vector<int>();
  std::unordered_map<int, int> map = std::unordered_map<int, int>();
  int problemType;

  int p = scanf("%d\n", &problemType);
  if (p != 1) { return(1); }

  if (problemType == 1) {
    stringProcessing(v1, map, V1);
    auto result = problem1(v1);
    printf("%d %d\n", result[0], result[1]);
  }
  else if (problemType == 2) {
    stringProcessing(v1, map, V1);
    stringProcessing(v2, map, V2);
    auto result = problem2(v1, v2);
    printf("%d\n", result);
  }
  else { return -1;}
  return 0;
}
