#include <stdio.h>
#include <stdlib.h>
// these two are to get maximums
#include <limits.h>
#include <float.h>
#include <thread>
#include <future>
#include <ctime>
#include <chrono>
#include <cmath>
#include <iostream>
#include <iomanip> // for std::setprecision()
#include <vector>

// for time stuff
using namespace std::chrono;

// max of long double: LDBL_MAX

long double denominatorParts[3] = {2.0, 3.0, 4.0};
long double pi = 3.0; // start with 3
unsigned long cycles = ULONG_MAX;

void calcinrange(unsigned long start, unsigned long end, std::promise<long double> && r, int TID) {
	unsigned long cycle = start;
	long double dParts[3] = {2.0+(long double)(start*2), 3.0+(long double)(start*2), 4.0+(long double)(start*2)};
	long double pi = 0.0; // the smaller ones will start with 0, then they will all be added to 3 at the end
	bool add = true;
	while (cycle <= end) {
		long double addend = 4.0/(dParts[0]*dParts[1]*dParts[2]);
		if (add) pi += addend;
		else pi -= addend;
		for (int i = 0; i<3; i++)
			dParts[i]+=2.0;
		cycle++;
		add = !add;
	}
	r.set_value(pi);
	printf("Thread %d done.\n", TID);
}

int main(int argc, char* argv[]) {
	int threads = 1;
	int precision = 11; // this will be 10 decimal places. 1 is added for the 3
	if (argc >= 4) {
		precision = std::abs(atoi(argv[3]));
		if (precision > 50) {
			printf("Warning: %d is equivalent to a precision of 50.\n", precision);
			precision = 51; // again, add one for 3
		}
		threads = atoi(argv[1]);
		cycles = strtoul(argv[2], NULL, 10);
	} else if (argc == 3) {
		threads = atoi(argv[1]);
		cycles = strtoul(argv[2], NULL, 10);
	} else if (argc == 2) {
		threads = atoi(argv[1]);
	}

	if (threads <= 0)
		threads = (int)std::thread::hardware_concurrency();

	if (threads <= 0) { // this means that it couldn't figure out how many threads the system can have
		printf("Warning: could not determine hardware concurrency. Please specify a specific number of threads. Will use one thread.\n");
		threads = 1;
	}

	printf("Calculating pi over %lu iterations.\nUsing %d threads.\nPrecision: %d decimal places.\n", cycles, threads, precision-1);

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	std::vector<std::thread> t(threads);
	std::vector<std::promise<long double> > p(threads);
	std::vector<std::future<long double> > futures(threads);
	for (int i = 0; i < threads; i++)
		futures[i] = p[i].get_future();

	for (int TID = 0; TID < threads; TID++) {
		// first iteration is 0, then the last is 'cycles'
		unsigned long start = 0+(TID*(cycles/threads));
		unsigned long end = start+(cycles/threads)-1;
		t[TID] = std::thread(calcinrange, start, end, std::move(p[TID]), TID);
		printf("Thread %d: %lu to %lu\n", TID, start, end);
	}
	printf("Started.\n");

	long double *returns = new long double[threads];
	for (int i = 0; i < threads; i++) {
		t[i].join();
		returns[i] = futures[i].get();
	}

	printf("All threads completed.\n");

	long double answer = 3.0;
	for (int i = 0; i < threads; i++)
		answer += returns[i];
	
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

	std::cout << "Answer: " << std::setprecision(precision) << answer;
	printf(" (took %.2f seconds)\n", time_span.count());
	
	return 0;
}
