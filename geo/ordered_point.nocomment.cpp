namespace OrderedPoint {
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
