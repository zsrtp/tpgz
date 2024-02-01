#ifndef C_NODE_H
#define C_NODE_H

#include "../../dolphin/types.h"

typedef struct node_class {
    struct node_class* mpPrevNode;
    void* mpData;
    struct node_class* mpNextNode;
} node_class;

#endif /* C_NODE_H */
