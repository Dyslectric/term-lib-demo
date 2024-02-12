#include <iostream>
#include <chrono>

#include "qrosturm.h"

#define DELTA 30

long long now() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

bool is_time(long long delta, long long& last_refresh) {
	long long t = now();
	if (t - last_refresh > delta) {
		last_refresh = t;
		return true;
	} else return false;
}

int stdout_main() {
	int pos = 0;
	long long last_refresh = 0;

	while (true) {
		if (!is_time(DELTA, last_refresh)) {
			continue;
		}
		if (pos > 12) {
			pos = 0;
		}

		system("cls");

		for (int row = 0; row < 10; row++) {
			for (int i = 0; i < pos; i++) {
				std::cout << ' ';
			}
			for (int i = 0; i < row; i++) {
				std::cout << ' ';
			}

			std::cout << "Hello World! This is David's terminal library tester app.\n";
		}

		pos++;
	}
}

int qrosturm_main() {
	int pos = 0;
	long long last_refresh = 0;

	qrosturm::init();

	while (true) {
		if (!is_time(DELTA, last_refresh)) {
			qrosturm::poll_events();
			continue;
		}
		if (pos > 12) {
			pos = 0;
		}

		qrosturm::clear(' ');

		for (int row = 0; row < 10; row++) {
			qrosturm::set_print_coord(row, pos + row);
			qrosturm::print("Hello World! This is David's terminal library tester app.");
		}

		qrosturm::refresh();

		pos++;
	}
}

int main() {
	//stdout_main();
	qrosturm_main();
}

