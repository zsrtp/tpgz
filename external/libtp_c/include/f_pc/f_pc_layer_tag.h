
#ifndef F_PC_LAYER_TAG_H_
#define F_PC_LAYER_TAG_H_

#include "../SSystem/SComponent/c_tag.h"
#include "f_pc_layer.h"

typedef struct layer_management_tag_class {
    create_tag_class mCreateTag;
    layer_class* mpLayer;
    u16 mNodeListID;
    u16 mNodeListIdx;
} layer_management_tag_class;

#endif
