#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "node.hpp"
#include <vector>
#include <cmath>

std::random_device rd;
std::default_random_engine gen = std::default_random_engine(rd());
std::default_random_engine gen2 = std::default_random_engine(rd());

class NodeSystem {
public:
    NodeSystem(const std::vector< std::vector<int> > &relation, 
               int n_vertex, int width, int height, 
               double temp = 100.0, int niter=100)
               : n_vertex(n_vertex), 
                 width(width), height(height), 
                 temp(temp), niter(niter), relation(relation) {
        std::uniform_real_distribution<> disx(0, width);
        std::uniform_real_distribution<> disy(0, height);

        auto randfuncx = std::bind(disx, gen);
        auto randfuncy = std::bind(disy, gen2);

        force.resize(n_vertex, Coord{0.0, 0.0, 0});
        position.reserve(n_vertex);

        for (int i = 0; i < n_vertex; i++) {
            if (i < relation.size())
                position.emplace_back(randfuncx(), randfuncy(), 1, static_cast<int>(relation[i].size()));
            else
                position.emplace_back(randfuncx(), randfuncy(), 1);
        }

        double area = (double) width * height;
        this->k = sqrt(area / n_vertex);
    };

    void run() {
        for (int i = 0; i < position.size(); i++)
            std::cout << position[i];
        for (int t = 0; t < this->niter; t++) {
            this->step(t);
        }
        
        // return something for use.
    }

    const std::vector<Coord> & getVector() const {
        return position;
    }

    void step(int t) {
        this->init();
        this->compute_attraction();
        this->compute_repulsion();
        this->compute_gravity();
        this->update_position();
        this->temp *= (1 - (double)t / this->niter);
    }

    void init() {
        for (int i = 0; i < n_vertex; i++)
            force[i] = Coord{0.0, 0.0, 0};
    }

    void compute_attraction() {
        std::vector< std::vector<int> >::iterator row;
        std::vector<int>::iterator col;
        for (row = relation.begin(); row != relation.end(); row++) {
            for (col = row->begin() + 1; col != row->end(); col++) {
                int i = *(row->begin()), j = *col;
                double distance = dist(position[i], position[j]);
                double fa = f_attract(distance);
                Coord fa_xy = (position[j] - position[i]) * (fa / distance);
                
                force[i] += fa_xy;
                force[j] -= fa_xy;
            }
        }
    }

    void compute_repulsion() {
        for (int i = 0; i < force.size()-1; i++) {
            for (int j = i+1; j < force.size(); j++) {
                double distance = dist(position[i], position[j]);
                double fr = f_repulse(distance);
                Coord fr_xy = (position[j] - position[i]) * (fr / distance);
                
                force[i] -= fr_xy;
                force[j] += fr_xy;
            }
        }
    }

    /*
    void compute_gravity(int t) {
        gamma = 0.2 * floor((double)t / 200);
        Coord center = Coord{0.0, 0.0, 1};
        for (int i = 0; i < n_vertex; i++) {
            center += position[i];
        }
        center *= (1 / n_vertex);
        for (int i = 0; i < force.size(); i++) {
            force[i] += (center - position[i]) * gamma * position[i].mass;
        }
    }
    */

    void compute_gravity() {
        Coord center = Coord{(double)this->width / 2, (double)this->height / 2, 1};
        for (int i = 0; i < n_vertex; i++) {
            double distance = dist(position[i], center);
            if (distance > 1) {
                Coord f = (center - position[i]) * (3.0 / distance / distance);
                force[i] += f;
            }
        }
        
    }
    
    /*
    void update_position() {
        for (int i = 0; i < n_vertex; i++) {
            position[i] += min_with_scalar(force[i], I_max) * sigma;
        }
    }
    */

    void update_position() {
        for (int i = 0; i < n_vertex; i++) {
            double modulo = force[i].x * force[i].x + force[i].y * force[i].y;
            if (modulo > this->temp) {
                force[i].x = force[i].x * temp / modulo;
                force[i].y = force[i].y * temp / modulo;
            }
            Coord tmp_pos = position[i] + force[i];
            if (tmp_pos.x < 0.0)
                tmp_pos.x = 0.0;
            if (tmp_pos.x > (double)this->width)
                tmp_pos.x = (double)this->width;
            if (tmp_pos.y < 0.0)
                tmp_pos.y = 0.0;
            if (tmp_pos.y > (double)this->height)
                tmp_pos.y = (double)this->height;
            position[i] = tmp_pos;
        }
    }

    double f_attract(double x) { return x * x / k; };
    double f_repulse(double x) { return k * k / x; };
    
private:
    int n_vertex;
    int width, height;
    double temp;
    int niter;

    double k; //, gamma = 0.0;
    // double I_max = 10.0;
    // double sigma = 0.1;
    std::vector< std::vector<int> > relation;
    std::vector<Coord> force;
    std::vector<Coord> position;

};

#endif