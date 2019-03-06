#include <cstdio>
#include <cstdlib>
#include <thread>
#include <future>
#include <cmath>
#include <iostream>
#include <iomanip> // for std::setprecision()
#include <vector>
#include <cinttypes> // for std::uint_fast64_t

// for time stuff
using namespace std::chrono;

std::uint_fast64_t cycles = UINT_FAST64_MAX;

void calcinrange(std::uint_fast64_t start, std::uint_fast64_t end, std::promise<long double> && r, int TID) {
    std::uint_fast64_t cycle = start;
    long double s = 2.0l + static_cast<long double>(start*2);
    long double den = s*(s+1.0l)*(s+2.0l);
    long double v_6s2 = 6.0l*s*s;
    long double v_24s = 24.0l*s;
    long double pi = 0.0l; // the individual threads will start with 0, then they will all be added to 3 at the end

    // determine what should be used at the end: 4.0 or -4.0
    // if the start value is odd, it should be a -4.0
    long double sign;
    if (start%2 == 0)
        sign = 1.0l;
    else sign = -1.0l;

    // den
    // den 2 = den + 6(x+2)^2
    // at the end if cycle == end, add (1/den)
    while (cycle < end) {
        long double den2 = den;
        v_6s2 += v_24s + 24;
        v_24s += 48;
        den += v_6s2;
        den2 *= den; // This mult could also be removed
        pi += v_6s2/den2; // Only one division (per two cycles)!
        v_6s2 += v_24s + 24;
        v_24s += 48;
        den += v_6s2;
        cycle += 2;
    }

    if (cycle == end)
        pi += (1/den);

    r.set_value(sign*4.0l*pi); // Multiply the 4 only at the end...
    std::printf("Thread %d done.\n", TID);
}

int main(int argc, char* argv[]) {
	const unsigned int maxdigits = sizeof(long double) == 128 ? 33 : 15;
    int threads = 1;
    int precision = 11; // this will be 10 decimal places. 1 is added for the 3
    if (argc >= 2)
        threads = std::atoi(argv[1]);
    if (argc >= 3)
        std::sscanf(argv[2], "%" SCNuFAST64 "", &cycles);
    if (argc >= 4) {
        precision = std::abs(std::atoi(argv[3]));
        if (precision > maxdigits) {
            std::printf("Warning: %d is equivalent to a precision of %d.\n", precision, maxdigits);
            precision = maxdigits; // again, add one for 3
        }
    }

    if (threads <= 0)
        threads = static_cast<int>(std::thread::hardware_concurrency());

    if (threads <= 0) { // this means that it couldn't figure out how many threads the system can have
        std::printf("Warning: could not determine hardware concurrency. Please specify a specific number of threads. Will use one thread.\n");
        threads = 1;
    }

    std::printf("Calculating pi over %" PRIuFAST64 " iterations.\nUsing %d threads.\nPrecision: %d decimal places.\n", cycles, threads, precision-1);

    steady_clock::time_point t1 = steady_clock::now();

    std::vector<std::thread> t(threads);
    std::vector<std::promise<long double> > p(threads);
    std::vector<std::future<long double> > futures(threads);
    for (int i = 0; i < threads; i++)
        futures[i] = p[i].get_future();

    for (int TID = 0; TID < threads; TID++) {
        // first iteration is 0, then the last is 'cycles'
        std::uint_fast64_t start = (TID*(cycles/threads));
        std::uint_fast64_t end = start+(cycles/threads)-1;
        if (TID == threads-1)
            end += cycles%threads; // account for leftovers
        t[TID] = std::thread(calcinrange, start, end, std::move(p[TID]), TID);
        std::printf("Thread %d: %" PRIuFAST64 " to %" PRIuFAST64 "\n", TID, start, end);
    }
    std::printf("Started.\n");

    long double answer = 3.0l;
    for (int i = 0; i < threads; i++) {
        t[i].join();
        answer += futures[i].get();
    }

    std::printf("All threads completed.\n");

    steady_clock::time_point t2 = steady_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

    std::cout << "Answer: " << std::setprecision(precision) << answer;
    std::printf(" (took %.2f seconds)\n", time_span.count());

    return 0;
}
