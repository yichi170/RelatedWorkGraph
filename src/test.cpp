#include <iostream>
#include "node.hpp"
#include "system.hpp"

using namespace std;

int main() {
	vector< vector<int> > a(3);
	
	a[0].push_back(1);
	a[0].push_back(2);

	a[1].push_back(1);
	a[1].push_back(3);
	
	a[2].push_back(2);
	a[2].push_back(3);

	NodeSystem ns(a, 3, 100, 100);
	ns.run();

	const std::vector<Coord>& position = ns.getVector();

	cout << "test\n";
	cout << position.size() << '\n';
	for (int i = 0; i < 3; i++) {
		cout << position[i].x << " " << position[i].y << '\n';
	}

	return 0;
}

/*
3
1 2
1 3
2 3
*/