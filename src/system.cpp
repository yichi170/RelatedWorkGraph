#include "system.hpp"
#include <random>

std::random_device rd;
std::default_random_engine gen = std::default_random_engine(rd());
std::default_random_engine gen2 = std::default_random_engine(rd());

NodeSystem::NodeSystem(
    const int & n_vertex, const int & width, 
    const int & height, const double & temp, 
    const int & niter, 
    const std::vector< std::vector<int> > && relation)
        : n_vertex(n_vertex), width(width), height(height), 
          temp(temp), niter(niter), relation(relation) {
        
    std::uniform_real_distribution<> disx(0, width);
    std::uniform_real_distribution<> disy(0, height);

    auto randfuncx = std::bind(disx, gen);
    auto randfuncy = std::bind(disy, gen2);

    force.resize(n_vertex, Coord{0.0, 0.0, 0});
    position.reserve(n_vertex);
    position_pr.reserve(n_vertex);

    for (int i = 0; i < n_vertex; i++) {
        if (i < (int)relation.size())
            position.emplace_back(randfuncx(), randfuncy(), 1, static_cast<int>(relation[i].size()));
        else
            position.emplace_back(randfuncx(), randfuncy(), 1);
    }

    double area = (double) width * height;
    this->k = sqrt(area / n_vertex);
};

void NodeSystem::run() {
    for (int t = 0; t < this->niter; t++) {
        this->step(t);
    }
}

void NodeSystem::step(int t) {
    this->init();
    this->compute_attraction();
    this->compute_repulsion();
    this->compute_gravity();
    this->update_position();
    this->temp *= (1 - (double)t / this->niter);
}

void NodeSystem::init() {
    for (int i = 0; i < n_vertex; i++)
        force[i] = Coord{0.0, 0.0, 0};
}

void NodeSystem::compute_attraction() {
    // std::vector< std::vector<int> >::iterator row;
    // std::vector<int>::iterator col;
    
    for (size_t row = 0; row < relation.size(); row++) {
        for (size_t col = row+1; col < relation[row].size(); col++) {
            int i = relation[row][0], j = relation[row][col];
            double distance = dist(position[i], position[j]);
            double fa = f_attract(distance);
            Coord fa_xy = (position[j] - position[i]) * (fa / distance);
            force[i] += fa_xy;
            force[j] -= fa_xy;
        }
    }
    
    // for (row = relation.begin(); row != relation.end(); row++) {
    //     for (col = row->begin() + 1; col != row->end(); col++) {
    //         int i = *(row->begin()), j = *col;
    //         double distance = dist(position[i], position[j]);
    //         double fa = f_attract(distance);
    //         Coord fa_xy = (position[j] - position[i]) * (fa / distance);
            
    //         force[i] += fa_xy;
    //         force[j] -= fa_xy;
    //     }
    // }
}

void NodeSystem::compute_repulsion() {
    for (size_t i = 0; i < force.size()-1; i++) {
        for (size_t j = i+1; j < force.size(); j++) {
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

/*
void update_position() {
    for (int i = 0; i < n_vertex; i++) {
        position[i] += min_with_scalar(force[i], I_max) * sigma;
    }
}
*/

void NodeSystem::update_position() {
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

const std::vector< std::pair<double, double> > & NodeSystem::getVector() const {
    for (int i = 0; i < n_vertex; i++) {
        this->position_pr.emplace_back(position[i].x, position[i].y);
    }
    return position_pr;
}
