#include <iostream>
#include <cassert>
#include <utility>
#include "node.hpp"
#include "system.hpp"

#define x first
#define y second

using namespace std;

int main() {
	vector< pair<int, int> > a(3);
	
	a[0] = std::make_pair(1, 2);

	a[1] = std::make_pair(0, 2);
	
	a[2] = std::make_pair(0, 1);

	NodeSystem ns(3, 100, 100, 100.0, std::move(a));
	ns.run();

	const std::vector<std::pair <double, double> >& position = ns.getVector();
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
