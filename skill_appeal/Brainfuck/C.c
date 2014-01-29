#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#define memory(type) \
typedef struct memory_ ## type ## _tag \
{ \
	size_t size_ ; \
	type * mem_ ; \
} * memory_ ## type ; \
memory_ ## type new_memory_ ## type ( void ) \
{ \
	memory_ ## type mem = ( memory_ ## type ) malloc ( sizeof ( struct memory_ ## type ## _tag ) ) ; \
	mem->size_ = 0 ; \
	mem->mem_ = ( type * ) malloc ( sizeof ( type ) * ( mem->size_ + 1 ) ) ; \
	return mem ; \
} \
void delete_memory_ ## type ( memory_ ## type mem ) \
{ \
	free ( mem->mem_ ) ; \
	mem->mem_ = NULL ; \
	mem->size_ = 0 ; \
	free ( mem ) ; \
} \
void resize_memory_ ## type ( memory_ ## type mem , size_t size ) \
{ \
	if ( mem->size_ <= size ) \
	{ \
		size_t pre_size = mem->size_ + 1 ; \
		mem->size_ = size + 1 ; \
		mem->mem_ = ( type * ) realloc ( mem->mem_ , sizeof ( type ) * ( mem->size_ + 1 ) ) ; \
		memset ( mem->mem_ + pre_size , 0 , ( mem->size_ + 1 ) - pre_size ) ; \
	} \
} \
type get_memory_ ## type ( memory_ ## type mem , size_t index ) \
{ \
	resize_memory_ ## type ( mem , index ) ; \
	return mem->mem_ [ index ] ; \
} \
void set_memory_ ## type ( memory_ ## type mem , size_t index , type value ) \
{ \
	resize_memory_ ## type ( mem , index ) ; \
	mem->mem_ [ index ] = value ; \
}
memory ( char )
memory ( uint8_t )
const char * through ( const char * const cur , const char * const end )
{
	if ( cur == end )
	{
		return end ;
	}
	switch ( * cur )
	{
		case '[' :
		{
			through ( cur + 1 , end ) ;
		}
		break ;
		case ']' :
		{
			return cur ;
		}
		break ;
		default :
		break ;
	}
	return through ( cur + 1 , end ) ;
}
void exec ( const char * cur , const char * const end , memory_uint8_t mem , size_t cur_mem )
{
	for ( ; cur != end && ! feof ( stdin ) ; ++ cur )
	{
		if ( cur == end || feof ( stdin ) )
		{
			return ;
		}
		switch ( * cur )
		{
			case '+' :
			{
				set_memory_uint8_t ( mem , cur_mem , get_memory_uint8_t ( mem , cur_mem ) + 1 ) ;
			}
			break ;
			case '-' :
			{
				set_memory_uint8_t ( mem , cur_mem , get_memory_uint8_t ( mem , cur_mem ) - 1 ) ;
			}
			break ;
			case '>' :
			{
				++ cur_mem ;
			}
			break ;
			case '<' :
			{
				-- cur_mem ;
			}
			break ;
			case ',' :
			{
				int tmp = getchar ( ) ;
				if ( tmp == EOF )
				{
					return ;
				}
				set_memory_uint8_t ( mem , cur_mem , ( uint8_t ) ( unsigned char ) ( tmp ) ) ;
			}
			break ;
			case '.' :
			{
				putchar ( get_memory_uint8_t ( mem , cur_mem ) ) ;
			}
			break ;
			case '[' :
			{
				if ( get_memory_uint8_t ( mem , cur_mem ) )
				{
					exec ( cur + 1 , end , mem , cur_mem ) ;
					-- cur ;
				}
				else
				{
					cur = through ( cur + 1 , end ) ;
				}
				if ( cur == end )
				{
					return ;
				}
			}
			break ;
			case ']' :
			{
				return ;
			}
			break ;
			default :
			{
				fprintf ( stderr , "%s" , "Error.\n" ) ;
				exit ( EXIT_FAILURE ) ;
			}
		}
	}
}
int main ( int argc , char * * argv )
{
	if ( argc != 2 )
	{
		printf ( "please command:\n    $ %s [FILENAME]\n" , argv [ 0 ] ) ;
		return 0 ;
	}
	char codeable [ ] = "+-<>[],." ;
	memory_char code = new_memory_char ( ) ;
	FILE * file = fopen ( argv [ 1 ] , "r" ) ;
	if ( ! file )
	{
		fprintf ( stderr , "can't open file [%s]" , argv [ 1 ] ) ;
		exit ( EXIT_FAILURE ) ;
	}
	int input = fgetc ( file ) ;
	for ( int i = 0 ; input != EOF ; input = fgetc ( file ) )
	{
		if ( strchr ( codeable , input ) != NULL )
		{
			set_memory_char ( code , i , ( char ) ( unsigned char ) input ) ;
			++ i ;
		}
	}
	memory_uint8_t memory = new_memory_uint8_t ( ) ;
	exec ( code->mem_ , code->mem_ + code->size_ , memory , 0 ) ;
}