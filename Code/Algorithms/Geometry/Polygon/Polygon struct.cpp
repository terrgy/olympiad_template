struct Polygon
{
    vector<Point> points;

    ld getArea() const
    {
        ld sum = 0;
        for (int i = 0; i < len(points) - 1; ++i)
        {
            sum += vector_product(pointToVector(points[i]), pointToVector(points[i + 1]));
        }
        sum += vector_product(pointToVector(points.back()), pointToVector(points.front()));
        return fabs(sum) / 2;
    }

    ld getPerimeter() const
    {
        ld sum = 0;
        for (int i = 0; i < len(points) - 1; ++i)
        {
            sum += dist(points[i], points[i + 1]);
        }
        sum += dist(points.front(), points.back());
        return sum;
    }

    bool is_belong(Point point) const
    {
        if (point == points.front())
        {
            return true;
        }
        Vector target(points.front(), point);
        Vector lower(points.front(), points[1]);
        Vector upper(points.front(), points.back());
        if (!isVectorBetweenVectors(target, lower, upper))
        {
            if (are_equal(vector_product(upper, target), 0) && (scalar_product(upper, target) > 0))
            {
                return sqrDist(points.front(), point) <= sqrDist(points.front(), points.back());
            }
            return false;
        }

        int left, right;
        right = len(points) - 3;
        left = -1;
        while (right - left > 1)
        {
            int mid = (left + right) / 2;
            if (isVectorBetweenVectors(target, lower, Vector(points.front(), points[mid + 2])))
            {
                right = mid;
            }
            else
            {
                left = mid;
            }
        }
        return vector_product(Vector(points[right + 1], points[right + 2]), Vector(points[right + 1], point)) >= 0;
    }
};

istream& operator>>(istream& in, Polygon& polygon)
{
    int n;
    in >> n;
    polygon.points.resize(n);
    for (int i = 0; i < n; ++i)
    {
        in >> polygon.points[i];
    }
    return in;
}