/***************************************************************************
 *  examples/containers/map1.cpp
 *
 *  Part of the STXXL. See http://stxxl.sourceforge.net
 *
 *  Copyright (C) 2013 Daniel Feist <daniel.feist@student.kit.edu>
 *
 *  Distributed under the Boost Software License, Version 1.0.
 *  (See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt)
 **************************************************************************/

//! [example]
#include <stxxl/map>
#include <iostream>

#include <random>

#define DATA_NODE_BLOCK_SIZE (4096)
#define DATA_LEAF_BLOCK_SIZE (4096)

//! [comparator]
struct CompareGreater
{
    bool operator () (const uint64_t& a, const uint64_t& b) const
    { return a > b; }

    static int max_value()
    { return std::numeric_limits<uint64_t>::min(); }
};
//! [comparator]

int main()
{
    // template parameter <KeyType, DataType, CompareType, RawNodeSize, RawLeafSize, PDAllocStrategy (optional)>
    typedef stxxl::map<uint64_t, char, CompareGreater, DATA_NODE_BLOCK_SIZE, DATA_LEAF_BLOCK_SIZE> map_type;

    // Constructor map(node_cache_size_in_bytes, leaf_cache_size_in_bytes)
    map_type my_map((map_type::node_block_type::raw_size)*3, (map_type::leaf_block_type::raw_size)*3);

    std::random_device rd;
    std::mt19937_64 gen(rd());

    std::uniform_int_distribution<uint64_t> dis;

    for(int i=0; i<10000; i++) {
	auto key = dis(gen);
	auto value = isprint(i & 0x7f) ? (i & 0x7f) : '.';
        auto r = my_map.insert(std::pair<uint64_t, char>(key, value));
	if(!r.second) {
	    std::cout << key << std::endl;
	}
    }

    map_type::iterator iter;

    std::cout << "my_map contains:\n";
    for (iter = my_map.begin(); iter != my_map.end(); ++iter)
    {
        std::cout << iter->first << " => " << iter->second << std::endl;
    }

    map_type::iterator iter_low, iter_up;

    iter_low = my_map.lower_bound(1); // iter_low points to (1,a) in this case
    iter_up = my_map.upper_bound(3);  // iter_up points to (2,b) in this case

    std::cout << "lower bound " << iter_low->second << ", upper bound " << iter_up->second << std::endl;

    return 0;
}
//! [example]
