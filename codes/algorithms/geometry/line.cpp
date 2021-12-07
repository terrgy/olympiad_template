struct Line
{
    double A;
    double B;
    double C;

    Line() : Line(0, 0, 0) {}
    Line(double A, double B, double C) : A(A), B(B), C(C) {}
    Line(Point point, Vector perp_vector) : A(perp_vector.x), B(perp_vector.y),
                                            C(-perp_vector.x * point.x - perp_vector.y * point.y) {}
};

Point intersection(Line a, Line b)
{
    if (are_equal(a.A * b.B, a.B * b.A))
    {
        throw -1;
    }
    double x = (b.C * a.B - a.C * b.B) / (a.A * b.B - b.A * a.B);
    double y = (a.A * b.C - a.C * b.A) / (a.B * b.A - a.A * b.B);
    return {x, y};
}