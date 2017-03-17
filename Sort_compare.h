#ifndef CH_2_1_SORT_COMPARE_H
#define CH_2_1_SORT_COMPARE_H

#include <vector>
#include <random>
#include <iostream>
#include <iomanip>

#include "Timer.h"

template<template<class> class Sort_a,
        template<class> class Sort_b>
class Sort_compare {
private:
    Timer timer_{};
    std::uniform_real_distribution<double> dist_{0, 9};
    std::random_device rd_;

public:
    template<template<class> class Sort>
    unsigned long time_random_input(unsigned int num_elems, unsigned int num_trials) {
        unsigned long total{0};
        std::vector<double> elems;
        for (int t = 0; t < num_trials; t++) {
            for (int i = 0; i < num_elems; i++) {
                elems.push_back(dist_(rd_));
            }
            timer_.start_timer();
            Sort<double> s;
            s.sort(elems);
            total += timer_.get_elapsed_millis();
            timer_.reset();
            elems.clear();
        }
        return total;
    }

    void main(unsigned int num_elems, unsigned int num_trials) {
        unsigned long t1 = time_random_input<Sort_a>(num_elems, num_trials);
        unsigned long t2 = time_random_input<Sort_b>(num_elems, num_trials);
        if (t1 > t2) {
            std::cout << "For " << num_elems << " random doubles sort " << Sort_a<double>::tag << " is " << std::setprecision(9)
                      << static_cast<double>(t1) / static_cast<double>(t2) << " times faster than " << Sort_b<double>::tag << "\n";
        } else {
            std::cout << "For " << num_elems << " random doubles sort " << Sort_b<double>::tag << " is " << std::setprecision(9)
                      << static_cast<double>(t2) / static_cast<double>(t1) << " times faster than " << Sort_a<double>::tag << "\n";
        }
    }
};

#endif //CH_2_1_SORT_COMPARE_H
