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