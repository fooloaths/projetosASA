std::tuple<int, int>(std::vector<vector<int>> arr):

  int size = arr.size()
  std::vector<vector<tuple(int, int)>>> aux = vector<vector<tuple(int, int)>>>();

  if (size > 0)
    aux[0].push_back(tuple(nums.at(0), 1))

  std::vector<tuple<int, int>> firstLevel = aux[0];

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


CheckThreeCases(std::vector<vector<tuple(int, int)>>> arr, int k):

  Let size = arr.size();
  for (int i = size; i > 0; i--) {

    std::vector<tuple<int, int>> pares = arr[i]
    sizeLIS = pares.size() //Ver se este é um bom nome de variável

    counter = count(pares, k);
    if (i < size) //Is within bounds
      insert(arr[i + 1], tuple(k, counter))
    else {
        std::vector<tuple<int, int>>>() tmp = vector<tuple<int, int>>>()
        tmp.push_back(tuple(k, counter));
        arr.push_back(tmp);
        insert(arr[i + 1], tuple(k, counter));
    }
