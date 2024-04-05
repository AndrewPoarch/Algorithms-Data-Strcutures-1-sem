#include <iostream>
#include <cmath>
#include <cinttypes>
#include <string>
#include <vector>


struct Queue {
    std::vector<uint64_t > nums;

    void SiftUp(int index);

    void SiftDown(int i);

    void DecreaseKey(int key, int new_value);

    void ExtractMin();

    void Insert(int element);

    void Heapify();
};


void Queue::SiftDown( int i) {
    while (2 * i + 1 < nums.size()) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int j = left;
        if (right < nums.size() && nums[right] < nums[left]) {
            j = right;
        }
        if (nums[i] <= nums[j]) {
            break;
        }
        std::swap(nums[i], nums[j]);
        i = j;
    }
}

void Queue::SiftUp(int index) {
    if (index == 0)
        return;
    int parent = (index - 1) / 2;
    if (nums[parent] > nums[index]) {
        std::swap(nums[parent], nums[index]);
        SiftUp(parent);
    }
}
void Queue::DecreaseKey(int key, int new_value) {
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] == key) {
            nums[i] = new_value;
            SiftDown(i);
            SiftUp(i);
            break;
        }
    }
}
void Queue::ExtractMin() {
    std::cout << nums[0] << ' ';
    std::swap(nums[0], nums[nums.size() - 1]);
    nums.resize(nums.size() - 1);
    SiftDown( 0);
}

void Queue::Insert(int element) {
    nums.push_back(element);
    SiftUp(nums.size() - 1);
}

void Queue::Heapify() {
    for (int i = nums.size() / 2; i >= 0; i--){
        SiftDown(i);
    }
}




struct Heap {
    std::vector< std::pair<uint64_t, uint64_t>> nums;

    void SiftUp(int index);

    void SiftDown(int i);

    void DecreaseKey(int key, int new_value);

    std::pair<uint64_t, uint64_t> ExtractMin();

    void Insert(uint64_t element, uint64_t pow);

    void Heapify();
};


void Heap::SiftDown( int i) {
    while (2 * i + 1 < nums.size()) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int j = left;
        if (right < nums.size() && pow(nums[right].first, nums[right].second) < pow(nums[left].first, nums[left].second)) {
            j = right;
        }
        if (pow(nums[i].first, nums[i].second) <= pow(nums[j].first, nums[j].second)) {
            break;
        }
        std::swap(nums[i], nums[j]);
        i = j;
    }
}

void Heap::SiftUp(int index) {
    if (index == 0)
        return;
    int parent = (index - 1) / 2;
    if (pow(nums[parent].first, nums[parent].second) > pow(nums[index].first, nums[index].second)) {
        std::swap(nums[parent], nums[index]);
        SiftUp(parent);
    }
}
void Heap::DecreaseKey(int key, int new_value) {
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i].first == key) {
            nums[i].first = new_value;
            SiftDown(i);
            SiftUp(i);
            break;
        }
    }
}
std::pair<uint64_t, uint64_t> Heap::ExtractMin() {
    std::pair<uint64_t, uint64_t> ans = nums[0];
    std::swap(nums[0], nums[nums.size() - 1]);
    nums.resize(nums.size() - 1);
    SiftDown( 0);
    return ans;
}

void Heap::Insert(uint64_t element, uint64_t pow) {
    nums.emplace_back(element, pow);
    SiftUp(nums.size() - 1);
}
void Heap::Heapify() {
    for (int i = nums.size() / 2; i >= 0; i--){
        SiftDown(i);
    }
}

int main() {
    int n = 5'000'000;
    Heap my_heap;
    int* mas = new int[n + 1];
    for (int i = 0; i < n + 1; ++i)
        mas[i] = i;
    for (int i = 2; i < n + 1; ++i) {
        if (mas[i] != 0) {
            my_heap.Insert(mas[i], 1);
            for (uint64_t j = i * i; j < n + 1; j += i)
                mas[j] = 0;
        }
    }

    std::vector<uint64_t > answer;
    int count;
    std::cin >> count;
    for (int i = 0; i < count; ++i) {
        std::pair<uint64_t, uint64_t> temp = my_heap.ExtractMin();
        for (int j = 0; j < temp.second; ++j) {
            answer.push_back(temp.first) ;
        }

        my_heap.Insert(temp.first, temp.second * 2);
    }

    std::cout << answer.size() << '\n';



    Queue kkk;
    kkk.nums = answer;
    kkk.Heapify();

    int temp = kkk.nums.size();

    for (int i = 0; i < temp; ++i) {
        kkk.ExtractMin();
    }


    return 0;
}