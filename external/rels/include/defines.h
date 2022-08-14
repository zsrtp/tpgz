#ifndef TGPZ_DEFINES_H
#define TPGZ_DEFINES_H

// Required for keeping certain unused functions/variables from being removed
#define KEEP_FUNC __attribute__( ( used, visibility( "default" ) ) )
#define KEEP_VAR __attribute__( ( visibility( "default" ) ) )

#endif