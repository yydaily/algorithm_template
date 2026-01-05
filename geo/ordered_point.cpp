namespace OrderedPoint {
    /*
     * 可以对点进行排序，逆时针排序
     * 注意：可以支持任意点集的排序，包括x = 0, y = 0的case
     */
    class Point {
    public:
        long long x, y;
        int sign() const {
            if(y<0) return -1;
            if(y==0&&x>=0) return 0;
            return 1;
        }
        bool operator<(const Point& other) const {
            if(sign()!=other.sign()) return sign()<other.sign();
            return x*other.y-y*other.x>0;
        }
    };
};
