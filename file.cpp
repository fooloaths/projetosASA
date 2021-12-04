#include <iostream>
#include <vector>
#include <tuple>
#include <stdio.h>

int longestIncreasingSubsequenceSize(std::vector<int> v);

//Gonçalo vê isto, prolly há melhor, foi o copilot que fez, prolly é O(n^2)
//agora complicado devolver quantas destas há

//given a vector, return the size of the longest increasing subsequence
int longestIncreasingSubsequenceSize(std::vector<int> v) {
    int n = v.size();
    std::vector<int> dp(n, 1);
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (v[i] > v[j]) {
                dp[i] = std::max(dp[i], dp[j] + 1);
            }
        }
    }
    int max = 0;
    for (int i = 0; i < n; i++) {
        max = std::max(max, dp[i]);
    }
    return max;
}

int main() {

    int problemType;
    char c = '-';
    std::vector<int> v;

    std::cin >> problemType;

    c = getchar(); //Discard the '\n' at the end of first input
    while ((c = getchar()) != '\n') {
        if (c >= '0' && c <= '9') {
            v.push_back(c - '0');
            std::cout << c;
            std::cout << " next ";
        }
    }

    for (int i = 0; i < v.size(); i++) {
        std::cout << "indice " << i << " tem " << v.at(i) << "\n";
    }

    /*v.push_back(1);
    v.push_back(2);
    v.push_back(6);
    v.push_back(3);
    v.push_back(7);
    v.push_back(4);
    v.push_back(1234);

    std::cout << longestIncreasingSubsequenceSize(v) << std::endl;*/

    return 0;
}