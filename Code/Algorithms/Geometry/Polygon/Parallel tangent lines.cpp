struct Polygon
{
    vector<Point> points;

    int get_next(int i)
    {
        return i == len(points) - 1 ? 0 : i + 1;
    }

    vector< pair<Vector, int> > left_half, right_half;

    void prepare()
    {
        left_half.emplace_back(Vector(points[0], points[get_next(0)]), 0);

        int i;
        for (i = 1; i < len(points); ++i)
        {
            Vector vec(points[i], points[get_next(i)]);
            if (vector_product(left_half.front().first, vec) < 0)
            {
                left_half.emplace_back(vec, i);
            }
            else
            {
                right_half.emplace_back(vec, i);
                ++i;
                break;
            }
        }

        for (; i < len(points); ++i)
        {
            right_half.emplace_back(Vector(points[i], points[get_next(i)]), i);
        }
    }

    int find_half(const Vector& vec, vector< pair<Vector, int> >& half)
    {
        int left, right;
        left = -1;
        right = len(half);
        while (right - left > 1)
        {
            int mid = (left + right) / 2;
            if (vector_product(vec, half[mid].first) > 0)
            {
                left = mid;
            }
            else
            {
                right = mid;
            }
        }
        if (right == len(half))
        {
            return get_next(half.back().second);
        }
        else
        {
            return half[right].second;
        }
    }

    pair<Line, Line> find_tangent_lines(const Line& parallel)
    {
        vector<Vector> sides = {Vector(parallel.b, -parallel.a), Vector(-parallel.b, parallel.a)};
        vector<int> tangent_points;
        for (Vector& vec : sides)
        {
            if (are_collinear(vec, left_half.front().first))
            {
                tangent_points.push_back(0);
                continue;
            }
            if (vector_product(left_half.front().first, vec) < 0)
            {
                tangent_points.push_back(find_half(vec, left_half));
            }
            else
            {
                tangent_points.push_back(find_half(vec, right_half));
            }
        }

        return {Line(points[tangent_points[0]], parallel),
                Line(points[tangent_points[1]], parallel)};
    }
};