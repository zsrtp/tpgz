
#ifndef F_PC_DELETE_TAG_H_
#define F_PC_DELETE_TAG_H_

#include "../SSystem/SComponent/c_tag.h"
#include "f_pc_layer.h"

typedef int (*delete_tag_func)(void*);

typedef struct delete_tag_class {
    create_tag_class mBase;
    layer_class* mpLayer;
    s16 mTimer;
} delete_tag_class;

#endif
