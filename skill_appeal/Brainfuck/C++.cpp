#include<stdexcept>
#include<vector>
#include<algorithm>
#include<iostream>
#include<fstream>
class bf_error
	: public std::runtime_error
{
public :
	bf_error ( ) ;
} ;
bf_error::bf_error ( )
	: runtime_error { "bf_error" }
{
}
template < typename iterator , typename = typename std::enable_if < std::is_same < typename std::iterator_traits < iterator >::value_type , char >::value >::type >
auto through ( iterator cur , iterator end ) -> iterator
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
template < typename iterator , typename = typename std::enable_if < std::is_same < typename std::iterator_traits < iterator >::value_type , char >::value >::type >
auto exec ( iterator cur , iterator end , std::vector < unsigned char > & mem , std::vector < unsigned char >::size_type cur_mem ) -> void
{
	for ( ; cur != end && std::cin ; ++ cur )
	{
		mem.resize ( std::max ( mem.size ( ) , cur_mem + 1 ) , '\0' ) ;
		switch ( * cur )
		{
			case '+' :
			{
				++ mem [ cur_mem ] ;
			}
			break ;
			case '-' :
			{
				-- mem [ cur_mem ] ;
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
				char tmp ;
				std::cin.get ( tmp ) ;
				if ( ! std::cin )
				{
					return ;
				}
				mem [ cur_mem ] = tmp ;
			}
			break ;
			case '.' :
			{
				std::cout.put ( mem [ cur_mem ] ) ;
			}
			break ;
			case '[' :
			{
				if ( mem [ cur_mem ] )
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
				throw bf_error { } ;
			}
		}
	}
}
auto main ( int argc , char * * argv ) -> int
{
	if ( argc != 2 )
	{
		std::cout
		<< "please command:" << std::endl 
		<< "    $ " << argv [ 0 ] << " [FILENAME]" << std::endl ;
		return 0 ;
	}
	std::string codeable { "+-<>[],." } ;
	std::vector < char > code ;
	std::ifstream file ( argv [ 1 ] , std::ios_base::binary | std::ios_base::in ) ;
	if ( ! file )
	{
		throw std::runtime_error { std::string { "can't open file [" } + argv [ 1 ] + "]" } ;
	}
	std::copy_if (
		std::istreambuf_iterator < char > ( file ) ,
		std::istreambuf_iterator < char > ( ) ,
		std::back_inserter ( code ) ,
		[ & codeable ] ( char ch ) { return codeable.find ( ch ) != std::string::npos ; }
	) ;
	std::vector < unsigned char > memory ;
	exec ( code.begin ( ) , code.end ( ) , memory , 0 ) ;
}