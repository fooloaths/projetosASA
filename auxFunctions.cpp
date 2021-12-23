//*************************************TESTING FUNCTIONS******************************************
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

void printTuple(std::tuple<int, int> t) {
  printf("(%d, %d)", std::get<0>(t), std::get<1>(t));
}

void printMatrix(std::vector<std::vector<int>> matrix, std::vector<int> a, std::vector<int> b) {
  printf("###############################################################\n");
  printf("            LCS Matrix Representation\n");
  printf("###############################################################\n");
  printf("i\\j|0|"); for (auto i : b) {printf("%d|", i);} printf("\n");
  int i = -1;
  for (auto line : matrix) {
    printf("%d  |", a[i]); i++;
    for (auto cell : line) {
      printf("%d|", cell);

    }
    printf("\n");
  }
  printf("###############################################################\n");
}

void printCurrentLCSs(std::set<std::vector<int>> set) {
  printf("##########################################\n");
  printf("           printCurrentLCS\n");
  printf("##########################################\n");
  if (set.size() > 0) {
    for (auto subseq : set) {
      printf("{");
      for (auto value : subseq) {
        printf("%d, ",value);
      }
      printf("};");
    }
    printf("\n");
  }
  else {
    printf("O tamanho do set é 0\n");
  }
  printf("##########################################\n");
}

//**************************************TESTING FUNCTIONS*****************************************
