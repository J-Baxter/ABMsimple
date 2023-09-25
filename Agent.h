//header file: this is where we will declare the variables, methods within the class, library's and any other required
// file from the project
#include <random>
#include <vector>
#include <string>
#include <chrono>

class Agent
{
public:
    enum infection_status
    {
        susceptible = 0, infected, removed, dead
    };
    int infection_length = 0;

private:
    int m_x = 0;
    int m_y = 0;

    infection_status m_stage = susceptible;
    bool m_infectious = false;

    double m_infection_chance = 0;
    double m_recovery_chance = 0;
    double m_dying_chance = 0;

private:
    std::vector<unsigned int>
Discrete_distribution(std::vector<double>& weights, unsigned int
runs);

public:
    void update_location(int x_loc, int y_loc);
    void update_infec_status(infection_status stage);

    bool check_infectious();
    bool check_recovered();
    bool check_dead();

    void set_infection_chance(double chance);
    void set_recovery_chance(double chance);
    void set_dying_chance(double chance);
};