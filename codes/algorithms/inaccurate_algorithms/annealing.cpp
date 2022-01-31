bool annealing_choice(int old_score, int new_score, double temperature)
{
    if (new_score < old_score)
    {
        return true;
    }
    int p = (int)(exp((old_score - new_score) / temperature) * 100000);
    return randint(0, 100000) <= p;
}

void annealing()
{
    double temperature = 1;
    int cur_score = get_score();
    while (temperature > EPS)
    {
        temperature *= 0.999;
        make_random_update();
        int new_score = get_score();
        if (annealing_choice(cur_score, new_score, temperature))
        {
            new_score = cur_score;
        }
        else
        {
            rollback_update();
        }
    }
}