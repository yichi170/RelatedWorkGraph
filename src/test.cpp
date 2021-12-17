#include <iostream>
#include <cassert>
#include "node.hpp"
#include "system.hpp"

using namespace std;

int main() {
	vector< vector<int> > a(3);
	
	a[0].push_back(1);
	a[0].push_back(2);

	a[1].push_back(0);
	a[1].push_back(2);
	
	a[2].push_back(0);
	a[2].push_back(1);

	NodeSystem ns(3, 100, 100, 100.0, 100, std::move(a));
	ns.run();

	const std::vector<Coord>& position = ns.getVector();
	assert(position.size() != 0);

	assert(position[2].x < 101.0);
	assert(position[2].y < 101.0);

	assert(position[1].x < 101.0);
	assert(position[1].y < 101.0);
	
	assert(position[0].x < 101.0);
	assert(position[0].y < 101.0);

	cout << "test hello world\n";
	return 0;
}

/*
3
0 1
0 2
1 2
*/