#include <iostream>
#include <vector>
#include <tuple>
#include <set>
#include <cstring>
#include <string.h>

#define DUPLICATE -1

/* Se o count num nível é 0, mas encontrámos um tuplo com K igual ao que queremos inserir, então temos de aumentar o nº
 de subsequências de forma proporcional. A forma mais fácil deve ser duplicar esse tuplo (crying inside) */

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


//**************************************TESTING FUNCTIONS*****************************************

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

//void insert(std::vector<std::tuple<int, int>> &arr, std::tuple<int, int> t) {
void insert(std::vector<std::tuple<int, int>> &arr, std::tuple<int, int> t) {
  //printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
  //printf("                    insert\n");
  //printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
  int cmp = std::get<0>(t);
  //printf("o tuplo a inserir é: (%d, %d)\n", std::get<0>(t), std::get<1>(t));
  //printf("O tamanho do vector onde vai ser inserido é %ld\n", arr.size());
  if (std::get<0>(arr[arr.size() - 1]) > cmp) { //If it is smaller than the smallest tuple on this level
    //printf("Como é mais pequeno que o menor tuplo neste nível, fazemos push back\n")
    arr.push_back(t);
  }
  for (long unsigned int i = 0; i < arr.size(); i++) {
    //printf("Estamos na iteração nº%ld, com o i = %ld\n", i + 1, i);
    //printf("O tuplo neste posição é (%d, %d) e queremos inserir o (%d, %d)\n", std::get<0>(arr[i]), std::get<1>(arr[i]), std::get<0>(t), std::get<1>(t));
    if (std::get<0>(arr[i]) == cmp) {
      //arr.swap(arr[i], t);
      //printf("Como são iguais, vamos dar swap aos tuplos.\n");
      arr[i].swap(t);
      break;
    }
    else if (std::get<0>(arr[i]) < cmp) {
      //printf("Este tuplo é menor do que o que queremos inserir. Portanto vamos meter o nosso tuplo no índice %ld\n", i);
      arr.insert(arr.begin() + i, t);
      break;
    } 
  }
  //printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
}

int count(std::vector<std::tuple<int, int>> &pares, int k) {
    //printf("\n?????????????????????????????????????????????\n");
    //printf("              count\n");
    //printf("??????????????????????????????????????????????\n");
    //printf("O valor que estamos a comparar é %d\n", k);
    int sizeLIS = pares.size();
    //printf("O número de tuplos neste nível é %d\n", sizeLIS);
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
    
    /*std::vector<std::tuple<int, int>>::reverse_iterator j = pares.rbegin();
    for (; j != pares.rend() && (std::get<0>(*j) < k); j++) {
      counter += std::get<1>(*j);
    }*/
    /*while ((j < sizeLIS) && (std::get<0>(pares[j]) < k)) {
      counter += std::get<1>(pares[j]);
      j++;
    }*/
    /*if (std::get<0>(*j) == k) {
      j = pares.erase(j);  //Vamos ter de usar ponteiros para isto funcionar. Se partir algo, remover isto
    }*/
    //printf("?????????????????????????????????????????????????\n");
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
  //printf("\n------------------------------------------------------\n");
  //printf("              processValue\n");
  //printf("------------------------------------------------------\n");
  //printf("O tamanho atual do vetor é %d\n", size);
  //printf("O valor a processar é %d\n", k);
  for (int i = size - 1; i >= 0; i--) {		//Voltar aqui para tentar trocar o >= por um >
    //printf("Estamos a começar o nível %d, ou seja, i é %d\n", i + 1, i);
    auto pares = arr[i];
    //printf("O tuplo mais pequeno neste nível é "); printTuple(pares[pares.size() - 1]); printf("\n");
    // int sizeLIS = pares.size(); //Ver se este é um bom nome de variável
        if (k < std::get<0>(pares[pares.size() - 1])) {
      // Se o K for menor que todos os tuplos neste nível, podemos ignorá-lo por agora
      continue;
    }

    //printf("Vamos chamar o count para ver quantos são menor\n");
    //auto counter = count(pares, k); //Ver se algum tuplo passou a estar inativo: Provavelmente ver se count > 0 durante a iteração
    auto counter = count(arr[i], k);
    //printf("A resposta é %d\n", counter);
    if (counter == DUPLICATE) {
      break;
    }
    if (counter > 0) {
      //printf("O i é %d, o nível é %d e o size é %d, por isso vamos ter de ", i, i + 1, size);
      if (i < (size - 1)) { //Is within bounds
	      //printf("simplesmente inserir o tuplo no nível a cima\n");

        //Falta verificar se existe um tuplo com k no nível i + 1, se sim, em vez de insert, temos de dar merge
        ///////int numSeqs = tupleInLevel(k, arr[i + 1]);
        //insert(arr[i + 1], std::make_tuple(k, counter));
        //insert(arr[i + 1], std::make_tuple(k, counter + numSeqs)); //Para usar esta versão, temos de apagar o (k, num) que está neste nível antes
        insert(arr[i + 1], std::make_tuple(k, counter));
        break;
      }
      else {
	      //printf("criar mais um nível para depois inserir o novo tuplo\n");
        std::vector<std::tuple<int, int>> tmp = std::vector<std::tuple<int, int>>();
        tmp.push_back(std::make_tuple(k, counter));
        arr.push_back(tmp);
	      //printf("O nível foi criado, por isso agora o size é %ld\n", arr.size());
        break;
      }
    }
  }
  //printf("------------------------------------------------------\n");
}

std::tuple<int, int> problem1(std::vector<int> nums) {
  int size = nums.size();
  auto aux = std::vector<std::vector<std::tuple<int, int>>>();

  //printf("Testing the size of input array: %d\n", size);
  if (size > 0) {
    auto t = std::make_tuple(nums.at(0),1);
    auto tmp = std::vector<std::tuple<int,int>>();
    tmp.push_back(t);
    aux.push_back(tmp);
  }

  //auto firstLevel = aux[0];

  for (int i = 1; i < size; i++) {
    int k = nums[i];
    //int sizeFirstLevel = firstLevel.size();
    int sizeFirstLevel = aux[0].size();
    
    //printf("problem 1: o nosso k é %d\n", k);
    //printf("problem 1: vamos começar por comparar ao mais pequeno que é "); printTuple(aux[0][sizeFirstLevel - 1]); printf("\n");

    if (k < std::get<0>(aux[0][sizeFirstLevel - 1]))  {//Se isto não der para fazer com tuplos, troca os tuplos por arrays com 2 elementos
      //Smaller than all LIS on this level (smallest pair is always at last index)
      aux[0].push_back(std::make_tuple(k, 1));
      continue;
    }

    processValue(aux, k);
    /*printf("???????????????\n");
    printf("Reaching end of %dth iteration of problem1\n", i + 1);
    printf("???????????????\n");*/
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


std::set<std::vector<int>> findAllLCS(std::vector<std::vector<int>> matrix, int i, int j, std::vector<int> n, std::vector<int> m) {
  //printf("-----------------------------------------------------\n");
  //printf("           FindAllLCS\n");
  //printf("-----------------------------------------------------\n");
  //printf("o i é %d e o j é %d\n", i, j);
  if (j == 0 || i == 0) {
    //printf("aaaaaaaaa?\n");
    //printf("Chegámos ao caso base\n");
    std::set<std::vector<int>> emptySet;
    return emptySet;
  }
  else if (n[i - 1] != m[j - 1]) { //If matrix[i][j] was computed from cell directly above or to the left
    //printf("Vamos buscar a cima ou à esquerda\n");
    std::set<std::vector<int>> a;
    std::set<std::vector<int>> b;
    if (matrix[i - 2][j - 1] >= matrix[i - 1][j - 2]) {
      //If value came from cell to the left
      //printf("bbbbbbbbbb\n");
      a = findAllLCS(matrix, i - 1, j, n, m);
    }
    if (matrix[i - 1][j - 2] >= matrix[i - 2][j - 1]) {
      //If value came from cell directly above
      //printf("cccccccccc\n");
      b = findAllLCS(matrix, i, j - 1, n, m);
    }

    //Combine results and return
    //printf("Vamos dar merge aos dois ramos. Os tamanhos de cada um eram %ld e %ld\n", a.size(), b.size());
    a = mergeSets(a,b);
    //printf("Agora o tamanho do merged é %ld\n", a.size());
    //printCurrentLCSs(a);
    return a;
  }
  //else if (n[i] == m[j]) {
  else {
    //If matrix[i][j] was computed by incrementing the diagonal value
    //printf("Vamos para a diagonal\n");
    int value = n[i - 1]; //Value to be appended to the end of the subsequence

    std::set<std::vector<int>> a = findAllLCS(matrix, i - 1, j - 1, n, m);
    //printf("Vamos extender as sequências. O nº de sequências é %ld e vamos extendê-las com %d\n", a.size(), value);
    //Combine results
    std::set<std::vector<int>> result;
    if (a.size() != 0) {
      //printf("Vamos extender normalmente\n");
      //printf("O tamanho do set era %ld\n", a.size());
      result = extendSequences(a, value);
      //printf("Passou a ser %ld e o tamanho do result é %ld\n", a.size(), result.size());
    }
    else {
      std::vector<int> seq = std::vector<int>();
      seq.push_back(value);
      a.insert(seq);
      result = a;
    }
    //printf("bbbbbbbbbbbbbbbb\n");
    //printCurrentLCSs(result);
    //printf("aaaaaaaaaaaaaaa\n");
    return result;
  }
}

//int** computeLCSMatrix(std::vector<int> v1, std::vector<int> v2) {
std::vector<std::vector<int>>  computeLCSMatrix(std::vector<int> v1, std::vector<int> v2) {

  std::vector<std::vector<int>> matrix(v1.size() + 1, std::vector<int>(v2.size() + 1, 0));
  //int matrix[v1.size() + 1][v2.size() + 1];
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
//TODO change to be longest common strictly increasing subsequence
int problem2(std::vector<int> v1, std::vector<int> v2) {
  std::vector<std::vector<int>> matrix = computeLCSMatrix(v1, v2);

  /*printf("----Array 1-----\n");
  printf("O tamanho é %ld\n", v1.size());
  for (auto i : v1) {printf("%d, ", i);} printf("\n-----------\n");  
  printf("----Array 2-----\n");
    printf("O tamanho é %ld\n", v2.size());
  for (auto i : v2) {printf("%d, ", i);} printf("\n-----------\n");

  printMatrix(matrix, v1, v2);*/

  std::set<std::vector<int>> LCIS = findAllLCS(matrix, v1.size() + 1, v2.size() + 1, v1, v2);

  long unsigned int maxSize = 0;
  for (auto subseq : LCIS) {      //Temos de testar com vários inputs. Não sei se todas estas subSeqs são estritamente crescentes
    if (subseq.size() > maxSize) { //Tb não estou sure se têm todas o mesmo tamanho. Se a resposta a ambas for sim,
      maxSize = subseq.size();    //basta dar return de o size de 1 delas, em vez de percorrer todas
    }
  }
  return maxSize;
  //return matrix[v1.size()][v2.size()];
}


/*std::set<std::vector<int>> findAllLCS(int **matrix, int i, int j, std::vector<int> n, std::vector<int> m) {
  if (j == 0 || i == 0) {
    std::set<std::vector<int>> emptySet;
    return emptySet;
  }
  else if (n[i] != m[j]) { //If matrix[i][j] was computed from cell directly above or to the left

    std::set<std::vector<int>> a;
    std::set<std::vector<int>> b;
    if (matrix[i - 1][j] >= matrix[i][j - 1]) {
      //If value came from cell to the left
      a = findAllLCS(matrix, i - 1, j, n, m);
    }
    if (matrix[i][j - 1] >= matrix[i - 1][j]) {
      //If value came from cell directly above
      b = findAllLCS(matrix, i, j - 1, n, m);
    }

    //Combine results and return
    a = mergeSets(a,b);
    return a;
    //return mergeSets(a, b);
  }
  //else if (n[i] == m[j]) {
  else {
    //If matrix[i][j] was computed by incrementing the diagonal value

    int value = n[i]; //Value to be appended to the end of the subsequence

    std::set<std::vector<int>> a = findAllLCS(matrix, i - 1, j - 1, n, m);

    //Combine results
    std::set<std::vector<int>> result = extendSequences(a, value);
    return result;
  }
}*/

int main() {  
  std::vector<int> v1;
  std::vector<int> v2;
  int problemType;

  int p = scanf("%d\n", &problemType);
  if (p != 1) { return(1); }

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
    printf("problema 2\n");
    auto result = problem2(v1, v2);
    printf("%d\n", result);
  }
  else { return -1;}
  return 0;
}
