Circle minDiskWith2Points(vector<Point>& points, int border, Point a, Point b)
{
    Circle min_disk = circle_by_diameter(a, b);
    for (int i = 0; i <= border; ++i)
    {
        if (min_disk.is_belong(points[i]))
        {
            continue;
        }
        min_disk = circle_by_3_points(points[i], a, b);
    }
    return min_disk;
}

Circle minDiskWithPoint(vector<Point>& points, int border, Point a)
{
    shuffle(points.begin(), points.begin() + border, rnd);
    Circle min_disk = circle_by_diameter(points[0], a);
    for (int i = 1; i <= border; ++i)
    {
        if (min_disk.is_belong(points[i]))
        {
            continue;
        }
        min_disk = minDiskWith2Points(points, i - 1, a, points[i]);
    }
    return min_disk;
}

Circle minDisk(vector<Point>& points)
{
    shuffle(points.begin(), points.end(), rnd);
    Circle min_disk = circle_by_diameter(points[0], points[1]);
    for (int i = 2; i < len(points); ++i)
    {
        if (min_disk.is_belong(points[i]))
        {
            continue;
        }
        min_disk = minDiskWithPoint(points, i - 1, points[i]);
    }
    return min_disk;
}