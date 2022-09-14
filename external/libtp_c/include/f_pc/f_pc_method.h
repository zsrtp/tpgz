
#ifndef F_PC_METHOD_H_
#define F_PC_METHOD_H_

typedef int (*process_method_func)(void*);

typedef struct process_method_class {
    process_method_func mpCreateFunc;
    process_method_func mpDeleteFunc;
    process_method_func mpExecuteFunc;
    process_method_func mpIsDeleteFunc;
} process_method_class;

#endif
