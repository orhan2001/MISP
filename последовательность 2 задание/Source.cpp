#include<cstdlib>
#include<iostream>
#include<vector>
#include<numeric>
#include<cmath>
#include<fstream>
#include <algorithm>
void Error() {
	std::cout << "File error!";
}

int main(int argc, char** argv) {

	int n = 0;
	int buff = 0;
	std::vector<int> general;
	std::vector<int> firstPlayer;
	std::vector<int> secondPlayer;
	int sumOne = 0;
	int sumTwo = 0;


	if (argc != 3) {
		Error();
	}

	std::ifstream fin(argv[1]);
	if (fin.is_open()) {
		fin >> n;
		for (int i = 0;i < n;i++) {
			fin >> buff;
			general.push_back(buff);
		}

		fin.close();
	}
	sort(general.begin(), general.end());
	
	for (int i = 0;i < (n / 2);i++) {
		firstPlayer.push_back(general[i]);
	}

	for (int i = n/2;i < n;i++) {
		secondPlayer.push_back(general[i]);
	}
	sumOne = std::accumulate(firstPlayer.begin(), firstPlayer.end(), 0);
	sumTwo = std::accumulate(secondPlayer.begin(), secondPlayer.end(), 0);

	std::ofstream fout(argv[2]);
	if (fout.is_open()) {
		fout << abs(sumOne - sumTwo);
		fout.close();
	}


}