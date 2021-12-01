#include<cstdlib>
#include<iostream>
#include<vector>
#include<numeric>
#include<cmath>
#include<fstream>

void Error() {
	std::cout << "File error!";
}

int main(int argc, char** argv) {

	int n = 0;
	int buff = 0;
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
		for (int i = 0;i < (n / 2);i++) {
			fin >> buff;
			firstPlayer.push_back(buff);
		}
		for (int j = (n / 2);j < n;j++) {
			fin >> buff;
			secondPlayer.push_back(buff);
		}
		fin.close();
	}

	sumOne = std::accumulate(firstPlayer.begin(), firstPlayer.end(), 0);
	sumTwo = std::accumulate(secondPlayer.begin(), secondPlayer.end(), 0);

	std::ofstream fout(argv[2]);
	if (fout.is_open()) {
		fout << abs(sumOne - sumTwo);
		fout.close();
	}


}