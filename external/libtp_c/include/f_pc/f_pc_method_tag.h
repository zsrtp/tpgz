
#ifndef F_PC_METHOD_TAG_H_
#define F_PC_METHOD_TAG_H_

#include "../SSystem/SComponent/c_tag.h"

typedef int (*process_method_tag_func)(void*);

typedef struct process_method_tag_class {
    create_tag_class mCreateTag;
    process_method_tag_func mpFunc;
    void* mpMthdData;
} process_method_tag_class;

#endif
