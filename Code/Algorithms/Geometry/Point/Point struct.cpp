struct Point
{
    double x;
    double y;

    Point() : Point(0, 0) {}
    Point(double x, double y) : x(x), y(y) {}

    bool operator<(const Point& other) const
    {
        return (x < other.x) || (are_equal(x, other.x) && (y < other.y));
    }

    bool operator==(const Point& other) const
    {
        return are_equal(x, other.x) && are_equal(y, other.y);
    }
};

istream& operator>>(istream& in, Point& point)
{
    in >> point.x >> point.y;
    return in;
}

ostream& operator<<(ostream& out, Point& point)
{
    out << point.x << ' ' << point.y;
    return out;
}

ld sqrDist(Point a, Point b)
{
    return sqr(a.x - b.x) + sqr(a.y - b.y);
}

ld dist(Point a, Point b)
{
    return sqrt(sqrDist(a, b));
}

bool are_on_line(Point a, Point b, Point c)
{
    return are_equal((double)vector_product(Vector(a, b), Vector(a, c)), 0.);
}

pair<Point, Point> get_diameter_points(Point a, Point b, Point c)
{
    if (scalar_product(Vector(a, b), Vector(a, c)) < 0)
    {
        return {b, c};
    }
    else if (scalar_product(Vector(b, c), Vector(b, a)) < 0)
    {
        return {a, c};
    }
    return {a, b};
}