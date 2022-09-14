#ifndef C_TAG_H
#define C_TAG_H

#include "c_list.h"
#include "c_node.h"
#include "c_tree.h"

typedef struct create_tag_class {
    node_class mpNode;
    void* mpTagData;
    int8_t mbIsUse;
} create_tag_class;

#endif /* C_TAG_H */
