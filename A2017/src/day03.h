//
// Created by sebeko on 9.1.23.
//
#ifndef AOCPP_DAY03_H
#define AOCPP_DAY03_H
#pragma once
#include <istream>
#include <vector>

void main03(std::istream &input);

auto parse03(std::istream &input) -> int;

auto layer_count(int n) -> int;
auto solve1(int num) -> int;

auto solve2(int num) -> int;

struct Spiral {
    int max_val = 0;
    size_t layers;
    std::vector<std::vector<int>> grid;

    explicit Spiral(size_t layers)
            : layers(layers)
            , grid(2*layers+1, std::vector<int>(2*layers+1, 0))
    {}

    int get(ssize_t x, ssize_t y);

    int set(ssize_t x, ssize_t y, int val);

    /// @brief Iterator spiraling outward from origin.
    ///
    /// The layer out of border is all equal to end iterator.
    ///
    /// @note It is a modified version of https://stackoverflow.com/a/14010215/11105559
    /// with added standard operators.
    struct out_iterator {
        using value_type = std::pair<int, int>;
        unsigned layer;
        unsigned border_layer;
        unsigned leg;
        int x, y; //read these as output from next, do not modify.
        explicit out_iterator(size_t border): layer(0), border_layer(border), leg(0), x(0), y(0) {}

        value_type operator*() const { return {x,y}; }
        out_iterator operator++();
        bool operator==(const out_iterator& o) const;
        bool operator!=(const out_iterator& o) const;
    };

    [[nodiscard]] out_iterator begin() const {
        return out_iterator(layers);
    }

    [[nodiscard]] out_iterator end() const {
        auto e = out_iterator(layers);
        e.layer = layers+1;
        return e;
    }
};

std::ostream& operator<<(std::ostream &o, const Spiral& s);

#endif //AOCPP_DAY03_H
