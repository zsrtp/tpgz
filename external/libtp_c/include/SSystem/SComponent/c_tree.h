#ifndef C_TREE_H
#define C_TREE_H

#include "c_list.h"
#include "c_node.h"

typedef struct node_lists_tree_class {
    node_list_class* mpLists;
    int mNumLists;
} node_lists_tree_class;

#endif /* C_TREE_H */
