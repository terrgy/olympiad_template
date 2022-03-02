struct Line
{
    double a;
    double b;
    double c;

    Line() : Line(0, 0, 0) {}
    Line(double a, double b, double c) : a(a), b(b), c(c) {}
    Line(const Point& point, Vector perp_vec) : a(perp_vec.x), b(perp_vec.y),
                                            c(-perp_vec.x * point.x - perp_vec.y * point.y) {}
    Line(const Point& point, const Line& parallel)
    {
        init_by_point_and_direction_vec(point, Vector(parallel.b, -parallel.a));
    }

    void init_by_point_and_direction_vec(const Point& point, const Vector& vec)
    {
        a = vec.y;
        b = -vec.x;
        c = -a * point.x - b * point.y;
    }

    bool is_belong(const Point& point)
    {
        return are_equal(a * point.x + b * point.y + c, 0);
    }
};

istream& operator>>(istream& in, Line& line)
{
    in >> line.a >> line.b >> line.c;
    return in;
}

Point intersection(const Line& line1, const Line& line2)
{
    if (are_equal(line1.a * line2.b, line1.b * line2.a))
    {
        throw -1;
    }
    double x = (line2.c * line1.b - line1.c * line2.b) / (line1.a * line2.b - line2.a * line1.b);
    double y = (line1.a * line2.c - line1.c * line2.a) / (line1.b * line2.a - line1.a * line2.b);
    return {x, y};
}

double distance(const Line& line, const Point& point)
{
    return fabs(line.a * point.x + line.b * point.y + line.c) / sqrt(line.a * line.a + line.b * line.b);
}

bool is_line_between(const Line& first, const Line& second, const Line& target)
{
    if (are_equal(target.b, 0))
    {
        return is_line_between(Line(first.b, first.a, first.c), Line(second.b, second.a, second.c), Line(target.b, target.a, target.c));
    }
    auto cmp = [](double c1, double b1, double c2, double b2)
    {
        bool less_sign = true;
        if (b1 < 0)
        {
            less_sign ^= 1;
        }
        if (b2 < 0)
        {
            less_sign ^= 1;
        }
        double res = c1 * b2 - c2 * b1;
        return less_sign ? res <= 0 : res >= 0;
    };

    auto is_between_half = [&](const Line& f, const Line& s, const Line& t)
    {
        return cmp(f.c, f.b, t.c, t.b) && cmp(t.c, t.b, s.c, s.b);
    };

    return is_between_half(first, second, target) || is_between_half(second, first, target);
}