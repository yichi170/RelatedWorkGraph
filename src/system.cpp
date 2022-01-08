#include "system.hpp"
#include <random>

#define fs first
#define sc second

std::random_device rd;
std::default_random_engine gen = std::default_random_engine(rd());
std::default_random_engine gen2 = std::default_random_engine(rd());

NodeSystem::NodeSystem(
    const int & n_vertex, const int & width, 
    const int & height, const double & temp, 
    const std::vector< std::pair<int, int> > && relation)
        : n_vertex(n_vertex), width(width), height(height), 
          temp(temp), relation(relation) {
        
    std::uniform_real_distribution<> disx(0, width);
    std::uniform_real_distribution<> disy(0, height);

    auto randfuncx = std::bind(disx, gen);
    auto randfuncy = std::bind(disy, gen2);

    force.resize(n_vertex, Coord{0.0, 0.0, 0});
    position.reserve(n_vertex);
    position_pr.reserve(n_vertex);

    adj.resize(n_vertex);

    for (int i = 0; i < n_vertex; i++) {
        position.emplace_back(randfuncx(), randfuncy(), 1, static_cast<int>(adj[i].size()));
    }

    for (auto &i: relation) {
        adj[i.fs].push_back(i.sc);
    }

    double area = (double) width * height;
    this->k = sqrt(area / n_vertex);
};

void NodeSystem::run() {
    for (int t = 0; t < this->niter; t++) {
        this->step(t);
    }
}

void NodeSystem::run_times(int n) {
    for (int t = 0; t < n; t++) {
        this->step(t);
    }
}

void NodeSystem::step(int t) {
    this->init();
    this->compute_force();
    this->compute_gravity();
    this->update_position();
    this->temp *= std::max(1.0 , (1.0 - (double)t / this->niter));
}

void NodeSystem::init() {
    for (int i = 0; i < n_vertex; i++)
        force[i] = Coord{0.0, 0.0, 0};
}

void NodeSystem::compute_force() {
    for (int i = 0; i < n_vertex; i++) {
        
        // compute_attraction
        for (auto &j: adj[i]) {
            if (i >= j) continue;
            
            double distance = dist(position[i], position[j]);
            double fa = f_attract(distance);
            Coord fa_xy = (position[j] - position[i]) * (fa / distance);
            
            force[i] += fa_xy;
            force[j] -= fa_xy;
        }
        
        // compute_repulsion
        for (int j = i+1; j < n_vertex; j++) {
            double distance = dist(position[i], position[j]);
            double fr = f_repulse(distance);
            Coord fr_xy = (position[j] - position[i]) * (fr / distance);
            
            force[i] -= fr_xy;
            force[j] += fr_xy;
        }
    }
}

void NodeSystem::compute_gravity() {
    Coord center = Coord{(double)this->width / 2, (double)this->height / 2, 1};
    for (int i = 0; i < n_vertex; i++) {
        double distance = dist(position[i], center);
        if (distance > 1) {
            Coord f = (center - position[i]) * (3.0 / distance / distance);
            force[i] += f;
        }
    }
}

void NodeSystem::update_position() {
    for (int i = 0; i < n_vertex; i++) {
        double modulo = force[i].x * force[i].x + force[i].y * force[i].y;
        if (modulo > this->temp) {
            force[i] = force[i] * (temp / modulo);
        }
        position[i] += force[i];
        position[i].x = std::min((double)width, std::max(-width / 2.0, position[i].x));
        position[i].y = std::min((double)height, std::max(-height / 2.0, position[i].y));
    }
}

const std::vector< std::pair<double, double> > & NodeSystem::getVector() const {
    for (int i = 0; i < n_vertex; i++) {
        this->position_pr.emplace_back(position[i].x, position[i].y);
    }
    return position_pr;
}
