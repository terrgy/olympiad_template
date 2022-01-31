// Task: find the ratio of the area of the rectangle to the area of the union of circles inside it

struct Circle
{
    double x;
    double y;
    double z;
    double rad;

    Circle() : Circle(0, 0, 0, 0) {}
    Circle(int x, int y, int z, int rad) : x(x), y(y), z(z), rad(rad) {}

    void read()
    {
        cin >> x >> y >> z >> rad;
    }

    bool is_point_belong(double x_, double y_, double z_) const
    {
        return sqr(x - x_) + sqr(y - y_) + sqr(z - z_) <= sqr(rad);
    }
};

vector<Circle> circles;

ld monte_carlo_method()
{
    int tries_count, success_count;
    tries_count = success_count = 0;
    for (; tl_safe(); )
    {
        double x, y, z;
        x = (double)randint(0, 10000000) / 100000;
        y = (double)randint(0, 10000000) / 100000;
        z = (double)randint(0, 10000000) / 100000;

        ++tries_count;
        for (Circle& circle : circles)
        {
            if (circle.is_point_belong(x, y, z))
            {
                ++success_count;
                break;
            }
        }
    }

    return (ld)success_count / tries_count;
}