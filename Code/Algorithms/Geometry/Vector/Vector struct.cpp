struct Vector
{
    double x;
    double y;

    Vector() : Vector(0, 0) {}
    Vector(double x, double y) : x(x), y(y) {}
    Vector(Point start, Point end) : Vector(end.x - start.x, end.y - start.y) {}

    ld sqr_len() const
    {
        return sqr(x) + sqr(y);
    }
};

Vector point_to_vector(Point point)
{
    return {point.x, point.y};
}

ld scalar_product(Vector a, Vector b)
{
    return a.x * b.x + a.y * b.y;
}

ld vector_product(Vector a, Vector b)
{
    return a.x * b.y - a.y * b.x;
}

bool is_vector_between_vectors(Vector target, Vector lower, Vector upper)
{
    ld lower_vector_product = vector_product(lower, target);
    return ((lower_vector_product > 0) && (vector_product(upper, target) < 0)) ||
           (are_equal(lower_vector_product, 0) && (scalar_product(lower, target) > 0));
}

bool are_collinear(const Vector& a, const Vector& b)
{
    return (vector_product(a, b) == 0) && (scalar_product(a, b) > 0);
}