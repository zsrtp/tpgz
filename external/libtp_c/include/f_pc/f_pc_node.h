#ifndef F_PC_NODE_H_
#define F_PC_NODE_H_

#include "../f_pc/f_pc_base.h"

typedef struct process_node_class {
    /* 0x00 */ base_process_class mBase;
    /* 0xB8 */ nodedraw_method_class* mpNodeMtd;
    /* 0xBC */ layer_class mLayer;
    /* 0xE8 */ node_list_class mLayerNodeLists[16];
    /* 0x1A8 */ s8 mUnk0;
} process_node_class;

typedef struct node_process_profile_definition {
    /* 0x00 */ process_profile_definition mBase;
    /* 0x1C */ process_method_class* sub_method; // Subclass methods
} node_process_profile_definition;

#endif