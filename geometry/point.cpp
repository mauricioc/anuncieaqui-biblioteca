typedef double T;
const T EPS = 1e-9;

inline int sgn(T a) { return a > EPS ? 1 : (a < -EPS ? -1 : 0); }
inline int cmp(T a, T b) { return sgn(b - a); }

struct pt {
    T x, y;
    pt(T x, T y = 0) : x(x), y(y) { }

    bool operator==(pt p) { return cmp(x, p.x) == 0 && cmp(y, p.y) == 0; }
    T operator||(pt p) { return x*p.x + y*p.y; }
    T operator%(pt p) { return x*p.y - y*p.x; }
    pt operator~() { return pt(x, -y); }
    pt operator+(pt p) { return pt(x + p.x, y + p.y); }
    pt operator-(pt p) { return pt(x - p.x, y - p.y); }
    pt operator*(pt p) { return pt(x*p.x - y*p.y, x*p.y + y*p.x); }
    pt operator/(T t) { return pt(x/t, y/t); }
    pt operator/(pt p) { return (*this * ~p)/(p||p); }
};
const pt I = pt(0,1);

struct circle { pt c; T r; };

T norm(pt a) { return a||a; }
T abs(pt a) { return sqrt(a||a); }
pt unit(pt a) { return a/abs(a); }
double arg(pt a) { return atan2(a.y, a.x); }
pt f_polar(T mod, double ang) { return pt(mod * cos(ang), mod * sin(ang)); }

ostream& operator<<(ostream& o, pt p) {
    return o << "(" << p.x << "," << p.y << ")";
}
