#pragma once
#include "dfs_traversal.h"

struct compare_traversals{
    bool operator()(const dfs_traversal& t1, const dfs_traversal& t2) const {
        return t1.dfs_path() < t2.dfs_path();
    }
};
