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
               const int & niter, 
               const std::vector< std::vector<int> > && relation);
    
    ~NodeSystem() = default;
    
    void run();
    void step(int);
    
    void init();
    void compute_attraction();
    void compute_repulsion();
    void compute_gravity();
    void update_position();

    const std::vector< std::pair<double, double> > & getVector() const;

    double f_attract(double x) { return x * x / k; };
    double f_repulse(double x) { return k * k / x; };

    
private:
    int n_vertex;
    int width = 500, height = 500;
    double temp = 100.0;
    int niter = 100;

    double k; //, gamma = 0.0;
    // double I_max = 10.0;
    // double sigma = 0.1;
    std::vector< std::vector<int> > relation;
    std::vector<Coord> force;
    std::vector<Coord> position;
    mutable std::vector< std::pair<double, double> > position_pr;

};

#endif
