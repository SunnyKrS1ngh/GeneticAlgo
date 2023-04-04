#include <bits/stdc++.h>
using namespace std;

const int n = 3;
const int maxw = 6;
const int profit[n] = {3, 3, 3};
const int weight[n] = {2, 2, 3};
const int pop_size = 100;
const float mutationRate = 0.1;
const float crossRate = 0.01;
const int generations = 100;
struct candidate
{
    vector<bool> gene;
    int fitness;
};

vector<candidate> create_population()
{
    vector<candidate> population;
    for (int i = 0; i < pop_size; i++)
    {
        candidate c;
        c.gene.resize(n);
        for (int j = 0; j < n; j++)
        {
            c.gene[j] = rand() % 2;
        }
        population.push_back(c);
    }
    return population;
}

int val_fit(candidate c)
{
    int wt = 0;
    int val = 0;
    for (int i = 0; i < n; i++)
    {
        if (c.gene[i])
        {
            wt += weight[i];
            val += profit[i];
        }
    }
    if (wt > maxw)
    {
        val = 0;
    }
    return val;
}
int val_wt(candidate c)
{
    int wt = 0;
    for (int i = 0; i < n; i++)
    {
        if (c.gene[i])
        {
            wt += weight[i];
        }
    }
    return wt;
}

void print_cand(candidate c)
{
    for (int i = 0; i < n; i++)
    {
        cout << c.gene[i] << " ";
    }
}

candidate wheel_select(vector<candidate> &population)
{
    int tot_fit = 0;
    for (int i = 0; i < pop_size; i++)
    {
        tot_fit += population[i].fitness;
    }
    float r = (rand() / static_cast<float>(RAND_MAX)) * tot_fit;
    float sum = 0;
    for (int i = 0; i < population.size(); i++)
    {
        sum += population[i].fitness;
        if (sum > r)
        {
            return population[i];
        }
    }
    return population[0];
}

void one_point_cross(candidate &c1, candidate &c2)
{
    int cross_point = rand() % n;
    for (int i = cross_point; i < n; i++)
    {
        bool temp = c1.gene[i];
        c1.gene[i] = c2.gene[i];
        c2.gene[i] = temp;
    }
}

void mutate(candidate &c)
{
    for (int i = 0; i < n; i++)
    {
        if (rand() / static_cast<float>(RAND_MAX) < mutationRate)
        {
            c.gene[i] = !c.gene[i];
        }
    }
}

int main()
{
    int mxfit = INT_MIN;
    int mnwt = INT_MAX;
    vector<candidate> population = create_population();
    for (int i = 1; i <= generations; i++)
    {
        for (int j = 0; j < population.size(); j++)
        {
            population[j].fitness = val_fit(population[j]);
        }
        sort(population.begin(), population.end(), [](const candidate &c1, const candidate &c2)
             { return c1.fitness > c2.fitness; });

        // print the best solution
        mxfit = max(mxfit, population[0].fitness);
        mnwt = min(mnwt, val_wt(population[0]));
        cout << "Generation : " << i << endl;
        cout << "fitness : " << population[0].fitness << endl;
        cout << "Weight : " << val_wt(population[0]) << endl;
        print_cand(population[0]);
        cout << endl;
        cout << endl;

        vector<candidate> new_pop;
        for (int j = 0; j < pop_size; j++)
        {
            candidate parent1 = wheel_select(population);
            candidate parent2 = wheel_select(population);
            candidate child = parent1;
            if (rand() / static_cast<float>(RAND_MAX) < crossRate)
            {
                one_point_cross(child, parent2);
            }
            mutate(child);
            new_pop.push_back(child);
        }
        population = new_pop;
    }
    cout << "Max profit = " << mxfit << endl;
    cout << "optimal weight = " << mnwt << endl;
    return 0;
}