
#ifndef F_PC_LAYER_H_
#define F_PC_LAYER_H_

#include "../SSystem/SComponent/c_node.h"
#include "../SSystem/SComponent/c_tag.h"
#include "../SSystem/SComponent/c_tree.h"

struct process_method_tag_class;
typedef struct process_node_class process_node_class;

typedef struct layer_class {
    node_class mNode;
    uint32_t mLayerID;
    node_lists_tree_class mNodeListTree;
    process_node_class* mpPcNode;
    node_list_class mCancelList;
    struct {
        int16_t mCreatingCount;
        int16_t mDeletingCount;
    } counts;
} layer_class;

#endif
