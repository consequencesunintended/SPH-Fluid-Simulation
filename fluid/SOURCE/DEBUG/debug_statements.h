/*
Alex Nasser
http://www.alexnasser.co.uk
Winter 2011
*/
#include <assert.h>

#define DEBUG_check_this_expression( _condition_ )\
     assert( _condition_ )
#define DEBUG_fail_if_implemented()\
     assert( 1 == 0 )