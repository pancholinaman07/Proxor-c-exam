#include <iostream>
#include <vector>
#include <unordered_set>

void generate_subsequences(const std::vector<int>& A, int i, std::vector<int>& B, std::vector<std::vector<int>>& subsequences) {
    if (i == A.size()) {
        if (B.size() > 1 && std::all_of(B.begin(), B.end() - 1, [](int x, int y) { return x < y; })) {
            subsequences.push_back(B);
        } else {
            generate_subsequences(A, i + 1, B, subsequences);
            B.push_back(A[i]);
            generate_subsequences(A, i + 1, B, subsequences);
            B.pop_back();
        }
    }
}

int count_set_bits(int n) {
    int count = 0;
    while (n > 0) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

int count_xor_values(const std::vector<int>& A) {
    std::vector<std::vector<int>> subsequences;
    generate_subsequences(A, 0, std::vector<int>(), subsequences);

    std::unordered_set<int> xor_values;
    for (const auto& B : subsequences) {
        int xor_value = B[0];
        for (size_t i = 1; i < B.size(); i++) {
            xor_value ^= B[i];
            if (count_set_bits(xor_value) >= count_set_bits(B[i])) {
                xor_values.insert(xor_value);
            }
        }
    }

    return xor_values.size();
}

int main() {
    std::vector<int> A = {1, 2, 3};
    int result = count_xor_values(A);
    std::cout << "Result: " << result << std::endl;
    return 0;
}
