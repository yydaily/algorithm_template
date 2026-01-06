#include<vector>
#include<algorithm>
#include<numeric>
namespace Rerange {
    template <typename T>
    std::vector<int> argsort(const std::vector<T> &A) {
        std::vector<int> ids(A.size());
        std::iota(ids.begin(), ids.end(), 0);
        sort(ids.begin(), ids.end(), [&](int i, int j) { return (A[i] == A[j] ? i < j : A[i] < A[j]); });
        return ids;
    }

    template <typename T>
    std::vector<T> rearrange(const std::vector<T> &before, const std::vector<int> &index) {
        std::vector<T> after(before.size());
        for(int i = 0; i < before.size(); i++) {
            after[i] = before[index[i]];
        }
        return after;
    }
}
