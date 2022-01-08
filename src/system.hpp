#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "node.hpp"
#include <cstddef>
#include <utility>
#include <vector>
#include <cmath>

class NodeSystem {
public:
    NodeSystem(const int & n_vertex, const int & width, 
               const int & height, const double & temp, 
               const std::vector< std::pair<int, int> > && relation);
    
    ~NodeSystem() = default;
    
    void run();
    void run_times(int n);
    void step(int);
    
    void init();
    void compute_force();
    void compute_gravity();
    void update_position();

    const std::vector< std::pair<double, double> > & getVector() const;

    double f_attract(double x) { return x * x / k; };
    double f_repulse(double x) { return k * k / x; };

    
private:
    int n_vertex;
    int width = 500, height = 500;
    double temp = 1e4;
    int niter = 100;

    double k;
    std::vector< std::pair<int, int> > relation;
    std::vector< std::vector<int> > adj;
    std::vector<Coord> force;
    std::vector<Coord> position;
    mutable std::vector< std::pair<double, double> > position_pr;

};

#endif
