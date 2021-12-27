#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

std::vector<std::string> stringAnagrams(const std::string& sentence, const std::map<std::string, int>& dict)
{
    std::string word;
    std::vector<std::string> sentenceWords;
    for (char i : sentence)
    {
        if (std::isspace(i)) {
            sentenceWords.push_back(word);
            word.clear();
        }
        else {
            word.push_back(i);
        }
    }
    if (!word.empty()) {
        sentenceWords.push_back(word);
    }

    std::vector<std::multimap<int, std::string, std::greater<int>>> wordsAnagrams;
    for (const auto& it : sentenceWords)
    {
        std::multimap<int, std::string, std::greater<int>> temp;
        for (auto& dw : dict)
        {
            if (it.size() == dw.first.size() && std::is_permutation(it.begin(), it.end(), dw.first.begin(), dw.first.end())) {
                temp.insert(std::make_pair(dw.second, dw.first));
            }
        }
        wordsAnagrams.push_back(temp);
    }

    std::multimap<int, std::vector<std::string>, std::greater<int>> buf;
    std::vector<std::multimap<int, std::string, std::greater<int>>::iterator> itVec;
    for (auto& it : wordsAnagrams) {
        itVec.push_back(it.begin());
    }

    bool end = false;
    do {
        std::vector<std::string> strVec;
        int strWeight = 0;
        for (auto it : itVec) {
            strVec.push_back(it->second);
            strWeight += it->first;
        }

        buf.insert(std::make_pair(strWeight, strVec));

        for (int i = wordsAnagrams.size() - 1; i >= 0; --i)
        {
            if (std::distance(wordsAnagrams[i].begin(), itVec[i]) != wordsAnagrams[i].size() - 1) {
                ++itVec[i];
                break;
            }
            else {
                if (i == 0) {
                    end = true;
                    break;
                }
                for (int j = wordsAnagrams.size() - 1; j >= i; --j) {
                    itVec[j] = wordsAnagrams[j].begin();
                }
            }
        }
    } while (!end);

    std::vector<std::string> sentenceAnagrams;
    for (auto& it : buf)
    {
        std::sort(it.second.begin(), it.second.end());
        do {
            std::string anagram{};
            for (auto& w : it.second) {
                anagram.append(w + ' ');
            }
            anagram.pop_back();
            sentenceAnagrams.push_back(anagram);
        } while (std::next_permutation(it.second.begin(), it.second.end()));
    }

    return sentenceAnagrams;
}

int main()
{
    std::map<std::string, int> dict{};
    std::ifstream fin;
    fin.open("dictionary.txt");
    if (!fin.is_open()) {
        std::cerr << "ERROR: file was not opened!\n";
    }

    std::string word;
    int weight;
    while (fin >> word) {
        if (!word.empty()) { 
            word.pop_back();
            fin >> weight;
            dict.insert(std::make_pair(word, weight));
        } 
    }
    fin.close();

    fin.open("input.txt");
    if (!fin) {
        std::cerr << "ERROR: file was not opened!\n";
    }

    std::string sentence;
    while (std::getline(fin, sentence)) {
        if (!sentence.empty()) {
            std::vector<std::string> anagrams = stringAnagrams(sentence, dict);
            for (auto& i : anagrams) {
                std::cout << i << '\n';
            }
        }        
    }
    fin.close();

    return 0;
}

