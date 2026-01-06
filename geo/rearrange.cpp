#include<vector>
#include<algorithm> // sort函数需要
#include<numeric> // iota函数调用，你可以可以去掉这个，然后手动赋值（但是不够优雅）
namespace Rerange {
    /*
     * 任意类型vector排序
     * 需要重载 <, ==, =
     * 下标从0开始
     * 按照升序排列
     */
    template <typename T>
    std::vector<int> argsort(const std::vector<T> &A) { // 返回重排下标, 表示当前这个位置应该用A[ret[i]]填充后就是有序的了
        std::vector<int> ids(A.size());
        std::iota(ids.begin(), ids.end(), 0);
        sort(ids.begin(), ids.end(), [&](int i, int j) { return (A[i] == A[j] ? i < j : A[i] < A[j]); });
        return ids;
    }

    template <typename T>
    std::vector<T> rearrange(const std::vector<T> &before, const std::vector<int> &index) { // 利用重排下标进行排序，返回排序后的数组
        std::vector<T> after(before.size());
        for(int i = 0; i < before.size(); i++) {
            after[i] = before[index[i]];
        }
        return after;
    }
}
