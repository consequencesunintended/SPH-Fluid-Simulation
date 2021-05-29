#ifndef __FUNDAMENTAL_DATA_TYPES__
#define __FUNDAMENTAL_DATA_TYPES__


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