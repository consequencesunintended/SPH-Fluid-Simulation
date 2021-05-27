/*
Alex Nasser
http://www.alexnasser.co.uk
Winter 2011
*/
#ifndef __FUNDAMENTAL_DATA_TYPES__
	#define __FUNDAMENTAL_DATA_TYPES__

typedef unsigned int	INDEX;
typedef int				INT32;
typedef short			INT16;
typedef unsigned int    UINT32;
typedef unsigned char	UINT8;
typedef float			REAL32;
typedef int				COUNTER;
typedef char			CHAR;
typedef unsigned char	UCHAR;
#undef					VOID
typedef void			VOID;
#undef					BOOL
#define BOOL			char
#define BOOLEAN_true	true
#define BOOLEAN_false	false


#define FUNDAMENTAL_DATA_TYPES_loop_through_table( _index_, _table_ ) \
    \
    for( \
        ; \
        _index_<_table_.size(); \
        _index_++ \
		)

#define FUNDAMENTAL_DATA_TYPES_loop_through_index( _index_, _start_index_value_, _end_index_value ) \
    \
    for( \
        _index_ = _start_index_value_; \
        _index_<=_end_index_value; \
        _index_++ \
		)

#endif