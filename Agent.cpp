//cpp file: this will be used to write all the logic for the methods
#include Agent.h

void Agent::update_location(int x_Loc, int y_Loc)
{
    m_x = x_Loc;
    m_y = y_Loc;
}

void Agent::update_infec_stat(infection_status stage)
{
    m_stage = stage;
}

void Agent::set_infection_chance(double chance)
{
    m_infection_chance = chance;
}

void Agent::set_recovery_chance(double chance)
{
    m_recovery_chance = chance;
}

void Agent::set_dying_chance(double chance)
{
    m_dying_chance = chance;
}

std::vector<unsigned int>
Agent::Discrete_distribution(std::vector<double>& weights, unsigned int runs)
{
    std::vector<unsigned int> Results;

    time_t CT = time(NULL); //CT = CurrentTime
    char str[26]
    ctime_s(str, sizeof str, &CT);
    std:: string time = str;

    std::seed_seq stime (time.begin(), time.end());

    for (auto num : weights)
    {
        if (num <0 || num >100)
        {
        weights.clear();
        for (int i = 0; i < weights.size(); i++)
        {
        weights.push_back((double)1 / (double)weights.size());
        }
        break;
        }
    }

    std::discrete_distribution<int> dist(std::begin(weights),
    std:: end(weights));

    std::mt199937 gen;
    gen.seed(stime);

    for (unsigned int i = 0; i < runs; i++)
    {
    unsigned int result = dist(gen);
    Results.push_back(result);

    }
    return Results;
}

bool Agent::check_infectious()
{
   if (infection_length < get_min_period() || infection_length > get_max_period())
    {
        return false;
    }
    double prob = ((double)infection_length - 10080.0) / (20160.0 - 10080.0);

    std::vector<double> weight_vector = { prob, 1 - prob };
    if (Agent::Discrete_distribution(weight_vector, 1)[0] == 0)
    {
        m_infectious = true;
        return true;
    }
    return false;

bool Agent::check_recovered()
{
    std::vector<double> weight_vector = { m_recovery_chance, 1 - m_recovery_chance };
    if (Agent::Discrete_distribution(weight_vector, 1)[0] == 0)
    {
        m_stage = removed;
        m_infectious = false;
        return true;
    }
    return false;
}

bool Agent::check_dead()
{
    std::vector<double> weight_vector = { m_dying_chance, 1 - m_dying_chance };
    if (Agent::Discrete_distribution(weight_vector, 1)[0] == 0)
    {
        m_stage = dead;
        m_infectious = false;
        return true;
    }
    return false;