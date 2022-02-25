struct Circle
{
    Point center;
    double rad;

    Circle() : Circle(Point(), 0) {}
    Circle(Point center, double rad) : center(center), rad(rad) {}

    bool is_belong(Point point) const
    {
        ld kek = sqr(center.x - point.x) + sqr(center.y - point.y) - sqr(rad);
        return (kek < 0) || are_equal(kek, 0);
    }
};

Circle circumscribedCircle(Point a, Point b, Point c)
{
    Point middle_ab((a.x + b.x) / 2, (a.y + b.y) / 2);
    Point middle_ac((a.x + c.x) / 2, (a.y + c.y) / 2);
    Line line_ab(middle_ab, Vector(a, b));
    Line line_ac(middle_ac, Vector(a, c));
    Point center = intersection(line_ab, line_ac);
    auto rad = (double)sqrt(sqr(a.x - center.x) + sqr(a.y - center.y));
    return {center, rad};
}

Circle circle_by_diameter(Point a, Point b)
{
    return {Point((a.x + b.x) / 2, (a.y + b.y) / 2), (double)(dist(a, b) / 2)};
}

Circle circle_by_3_points(Point a, Point b, Point c)
{
    if (a.are_equal(b))
    {
        return circle_by_diameter(a, c);
    }
    else if (a.are_equal(c) || b.are_equal(c))
    {
        return circle_by_diameter(a, b);
    }
    if (are_on_line(a, b, c))
    {
        auto [d1, d2] = get_diameter_points(a, b, c);
        return circle_by_diameter(d1, d2);
    }
    return circumscribedCircle(a, b, c);
}