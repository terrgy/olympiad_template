void get_convex_hull(vector<Point>& points, Polygon& polygon)
{
    if (points.empty())
    {
        return;
    }
    Point min_point = points[0];
    for (int i = 1; i < len(points); ++i)
    {
        min_point = min(min_point, points[i]);
    }

    auto cmp = [&](const Point& a, const Point& b)
    {
        if (a == min_point)
        {
            return false;
        }
        if (b == min_point)
        {
            return true;
        }
        Vector v1(min_point, a);
        Vector v2(min_point, b);
        ld product = vector_product(v1, v2);
        return (product > 0) || (are_equal(product, 0) && (v1.sqrLen() < v2.sqrLen()));
    };
    sort(points.begin(), points.end(), cmp);
    points.resize(distance(points.begin(), unique(points.begin(), points.end())));
    points.pop_back();

    vector<Point>& st = polygon.points;
    st.push_back(min_point);
    for (Point& point : points)
    {
        while ((len(st) > 1) && (vector_product(Vector(st.back(), point), Vector(st[len(st) - 2], st.back())) >= 0))
        {
            st.pop_back();
        }
        st.push_back(point);
    }
}