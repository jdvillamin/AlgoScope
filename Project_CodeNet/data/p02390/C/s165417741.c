#include <iostream>

int main() {

	int time;
	int h = 0;
	int m = 0;
	int s = 0;

	cin >> time;

	h = time / 3600;
	m = (time - (h * 3600)) / 60;
	s = time - (h * 3600) - (m * 60);

	std::cout<<h<<":"<<m<<":"<<s;
	
	return 0;
}
