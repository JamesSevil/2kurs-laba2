#include "include/set.h"
#include "include/array.h"
#include "vector"

bool checkorig(vector<Set<int>>& subsets, Set<int>& nums) {
    if (subsets.size() == 0) return true;
    for (int i = 0; i < subsets.size(); ++i) {
        Array<bool> checkrec;
        for (int j = 0; j < subsets[i].size(); ++j) {
            if ((nums.size() == subsets[i].size()) && (nums.get(j) == subsets[i].get(j))) checkrec.add(false);
            else checkrec.add(true);
        }
        
        int iter = 0;
        while (iter != checkrec.length()) {
            if (checkrec.get(iter)) return true;
            iter++;
        }
    }
    return false;
}

void findMaxPair(vector<Set<int>>& subsets, pair<Set<int>, Set<int>>& maxPair, int& maxInterections) {
    for (int i = 0; i < subsets.size(); ++i) {
        for (int j = i + 1; j < subsets.size(); ++j) {
            int commonCount = 0;

            // Считаем количество общих элементов
            for (int k = 0; k < subsets[i].size(); ++k) {
                int value = subsets[i].get(k);
                if (subsets[j].contains(value)) {
                    commonCount++;
                }
            }

            // Обновляем максимум, если найдено большее количество общих элементов
            if (commonCount > maxInterections) {
                maxInterections = commonCount;
                maxPair = {subsets[i], subsets[j]};
            }
        }
    }
}


int main() {

    while (true) {
        vector<Set<int>> subsets;
        int N;
        cout << "Введите кол-во подмножеств: ";
        cin >> N;
        cin.ignore();
        for (int i = 0; i < N; i++) {
            Set<int> subset;
            string nums;
            cout << "Введите элементы " << i+1 << "-го подмножества: ";
            getline(cin, nums);
            stringstream stream(nums);
            string token;
            while (getline(stream, token, ' ')) {
                subset.insert(stoi(token));
            }
            if (checkorig(subsets, subset)) {
                subsets.push_back(subset);
            }
        }

        int maxInterections = 0;
        pair<Set<int>, Set<int>> maxPair;
        findMaxPair(subsets, maxPair, maxInterections);

        cout << "Множества с максимальным количеством общих элементов: {{ ";
        for (int i = 0; i < maxPair.first.size(); ++i) {
            cout << maxPair.first.get(i) << " ";
        }
        cout << "},{ ";
        for (int i = 0; i < maxPair.second.size(); ++i) {
            cout << maxPair.second.get(i) << " ";
        }
        cout << "}}" << endl;
        cout << "Количество общих элементов: " << maxInterections << endl;
        cout << "--------------------------------------------------------" << endl;
    }

    return 0;
}

// вариант 4