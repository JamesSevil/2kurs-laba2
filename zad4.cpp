#include "include/array.h"

struct Pair {
    int w; // ширина
    int h; // высота
};

int maxFind(Array<Pair>& blocks) {
    Pair para;
    para.w, para.h = 0;
    int maxWeightPosition;
    for (int i = 0; i < blocks.length(); ++i) {
        if ((blocks.get(i).w == para.w && blocks.get(i).h > para.h) || (blocks.get(i).w > para.w)) {
            para.w = blocks.get(i).w;
            para.h = blocks.get(i).h;
            maxWeightPosition = i;
        }
    }

    return maxWeightPosition;
}

int maxHeight(Array<Pair>& blocks) {
    int maxHeight = 0;
    int pred = 0;
    while (blocks.length() != 0) {
        int position = maxFind(blocks);
        if (blocks.get(position).w < pred || maxHeight == 0) {
            maxHeight += blocks.get(position).h;
            pred = blocks.get(position).w;
            blocks.remove(position);
        } else {
            blocks.remove(position);
        }
    }
    
    return maxHeight;
}

int main() {
    
    while (true) {
        int N;
        cout << "Введите кол-во блоков: ";
        cin >> N;
        while (N < 1 || N > pow(10, 4)) {
            cout << "Кол-во блоков должно быть >= 1 и <= 10^4: ";
            cin >> N;
        }
        Pair block;
        Array<Pair> blocks;
        for (int i = 0; i < N; ++i) {
            cout << "Введите ширину и высоту " << i+1 << "-го блока: ";
            cin >> block.w >> block.h;
            while (block.w < 1 || block.h > pow(10, 9)) {
                cout << "Ширина должна быть >= 1, а высота < 10^9: ";
                cin >> block.w >> block.h;
            }
            blocks.add(block);
        }
        cout << "Максимальная высота: " << maxHeight(blocks) << endl;
        cout << "----------------------------------------" << endl;
    }

    return 0;
}

// вариант 4