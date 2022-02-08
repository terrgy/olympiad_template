int phi(int value)
{
    int result = value;
    for (int i = 2; i * i <= value; ++i)
    {
        if (value % i == 0)
        {
            while (value % i == 0)
            {
                value /= i;
            }
            result -= result / i;
        }
    }
    if (value > 1)
    {
        result -= result / value;
    }
    return result;
}