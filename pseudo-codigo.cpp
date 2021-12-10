#include <tuple>
#include <vector>

std::tuple<int, int> problem1(std::vector<std::vector<int>> arr) {

  auto size = arr.size();
  auto aux = new std::vector<std::vector<std::tuple<int, int>>>();

  if (size > 0)
    aux[0].push_back(std::make_tuple(arr.at(0), 1))

  auto firstLevel = aux[0];

  for (int i = 0; i < size; i++) {
    int k = array[i];
    int sizeFirstLevel = firstLevel.size();

    if (k < firstLevel[sizeFirstLevel - 1]].get(0))  {//Se isto não der para fazer com tuplos, troca os tuplos por arrays com 2 elementos
      //Smaller than all LIS on this level (smallest pair is always at last index)
      firstLevel.push_back(tuple(k, 1));
      continue;

    CheckThreeCases(aux, k);
  }

int count(std::vector<tuple<int, int>> pares, int k) {
    int counter = 0;
    int j = sizeLIS - 1;
      while ((j > 0) && (pares[j].get(0) < k)) {
        counter += pares[j].get(1);
        j--
      }

    return counter;
}


processValue(std::vector<vector<tuple(int, int)>>> arr, int k):

  Let size = arr.size();
  for (int i = size; i > 0; i--) {

    std::vector<tuple<int, int>> pares = arr[i]
    sizeLIS = pares.size() //Ver se este é um bom nome de variável

    counter = count(pares, k);
    if (counter > 0) {
      if (i < size) //Is within bounds
        insert(arr[i + 1], tuple(k, counter))
        break;
      else {
          std::vector<tuple<int, int>>>() tmp = vector<tuple<int, int>>>()
          tmp.push_back(tuple(k, counter));
          arr.push_back(tmp);
          insert(arr[i + 1], tuple(k, counter));
          break;
       }
     }
    }
