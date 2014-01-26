#include<iostream>
#include<cstdlib>
#include"FTMP/at.hpp"
#include"FTMP/cons.hpp"
#include"FTMP/list.hpp"
#include"FTMP/integral.hpp"
#include"FTMP/reverse.hpp"
#include"FTMP/print.hpp"
#define CH(ch) ftmp::integral < unsigned char , ch >
struct input ;
struct output ;
struct cur_inc ;
struct cur_dec ;
struct ptr_inc ;
struct ptr_dec ;
template < typename >
struct loop ;
template < typename , typename , typename >
struct memory ;
#define PARSER_BF(ch,ins) \
template < typename ... tail > \
struct parse_bf < ftmp::list < CH ( ch ) , tail ... > > \
{ \
	using parse_res = typename parse_bf \
	< \
		ftmp::list < tail ... > \
	>::type ; \
	using type = ftmp::list \
	< \
		typename ftmp::cons \
		< \
			ins , \
			typename ftmp::at \
			< \
				parse_res , \
				ftmp::integral < int , 0 > \
			>::type \
		>::type , \
		typename ftmp::at \
		< \
			parse_res , \
			ftmp::integral < int , 1 > \
		>::type \
	> ; \
}
template < typename >
struct parse_bf ;
PARSER_BF ( ',' , input ) ;
PARSER_BF ( '.' , output ) ;
PARSER_BF ( '<' , cur_dec ) ;
PARSER_BF ( '>' , cur_inc ) ;
PARSER_BF ( '-' , ptr_dec ) ;
PARSER_BF ( '+' , ptr_inc ) ;
template < typename ... tail >
struct parse_bf < ftmp::list < CH ( '[' ) , tail ... > >
{
	using parse_res_1 = typename parse_bf
	<
		ftmp::list < tail ... >
	>::type ;
	using parse_res_2 = typename parse_bf
	<
		typename ftmp::at < parse_res_1 , ftmp::integral < int , 1 > >::type
	>::type ;
	using type = ftmp::list
	<
		typename ftmp::cons
		<
			loop
			<
				typename ftmp::at
				<
					parse_res_1 ,
					ftmp::integral < int , 0 >
				>::type
			> ,
			typename ftmp::at
			<
				parse_res_2 ,
				ftmp::integral < int , 0 >
			>::type
		>::type ,
		typename ftmp::at
		<
			parse_res_2 ,
			ftmp::integral < int , 1 >
		>::type
	> ;
} ;
template < typename ... tail >
struct parse_bf < ftmp::list < CH ( ']' ) , tail ... > >
	: ftmp::list
	<
		ftmp::list < > ,
		ftmp::list < tail ... >
	>
{
} ;
template < >
struct parse_bf < ftmp::list < > >
	: ftmp::list < ftmp::list < > , ftmp::list < > >
{
} ;
template < typename , typename >
struct input_memory ;
template < typename before , typename ignore , typename after , typename word >
struct input_memory < memory < before , ignore , after > , word >
	: ftmp::id < memory < before , word , after > >
{
} ;
template < typename >
struct output_memory ;
template < typename before , typename res , typename after >
struct output_memory < memory < before , res , after > >
	: ftmp::id < res >
{
} ;
template < typename >
struct cur_dec_memory
	: ftmp::id
	<
		memory
		<
			ftmp::list < > ,
			ftmp::integral < unsigned char , '\0' > ,
			ftmp::list < >
		>
	>
{
} ;
template < typename h , typename ... before , typename res , typename after >
struct cur_dec_memory < memory < ftmp::list < h , before ... > , res , after > >
	: ftmp::id
	<
		memory
		<
			ftmp::list < before ... > ,
			h ,
			typename ftmp::cons < res , after >::type
		>
	>
{
} ;
template < typename >
struct cur_inc_memory
	: ftmp::id
	<
		memory
		<
			ftmp::list < > ,
			ftmp::integral < unsigned char , '\0' > ,
			ftmp::list < >
		>
	>
{
} ;
template < typename before , typename res , typename h , typename ... after >
struct cur_inc_memory < memory < before , res , ftmp::list < h , after ... > > >
	: ftmp::id
	<
		memory
		<
			typename ftmp::cons < res , before >::type ,
			h ,
			ftmp::list < after ... >
		>
	>
{
} ;
template < typename before , typename res >
struct cur_inc_memory < memory < before , res , ftmp::list < > > >
	: ftmp::id
	<
		memory
		<
			typename ftmp::cons < res , before >::type ,
			ftmp::integral < unsigned char , '\0' > ,
			ftmp::list < >
		>
	>
{
} ;
template < typename >
struct ptr_dec_memory ;
template < typename before , unsigned char ch , typename after >
struct ptr_dec_memory < memory < before , ftmp::integral < unsigned char , ch > , after > >
	: ftmp::id < memory < before , ftmp::integral < unsigned char , ch - 1 > , after > >
{
} ;
template < typename >
struct ptr_inc_memory ;
template < typename before , unsigned char ch , typename after >
struct ptr_inc_memory < memory < before , ftmp::integral < unsigned char , ch > , after > >
	: ftmp::id < memory < before , ftmp::integral < unsigned char , ch + 1 > , after > >
{
} ;
template < typename , typename env >
struct exec_bf_impl
	: ftmp::id < env >
{
} ;
template < typename loop_ , typename xs , typename env >
struct exec_bf_impl_impl
	: exec_bf_impl
	<
		typename ftmp::cons
		<
			loop_ ,
			xs
		>::type ,
		env
	>
{
} ;
template < typename loop_ , typename xs , typename before , typename after , typename input_ , typename output_ >
struct exec_bf_impl_impl < loop_ , xs , ftmp::list < memory < before , ftmp::integral < unsigned char , '\0' > , after > , input_ , output_ > >
	: exec_bf_impl
	<
		xs ,
		ftmp::list < memory < before , ftmp::integral < unsigned char , '\0' > , after > , input_ , output_ >
	>
{
} ;
template < typename ... bf , typename mem , typename h , typename ... input_ , typename output_ >
struct exec_bf_impl < ftmp::list < input , bf ... > , ftmp::list < mem , ftmp::list < h , input_ ... > , output_ > >
	: exec_bf_impl
	<
		ftmp::list < bf ... > ,
		ftmp::list
		<
			typename input_memory < mem , h >::type ,
			ftmp::list < input_ ... > ,
			output_
		>
	>
{
} ;
template < typename ... bf , typename mem , typename input_ , typename output_ >
struct exec_bf_impl < ftmp::list < output , bf ... > , ftmp::list < mem , input_ , output_ > >
	: exec_bf_impl
	<
		ftmp::list < bf ... > ,
		ftmp::list
		<
			mem ,
			input_ ,
			typename ftmp::cons
			<
				typename output_memory
				<
					mem
				>::type ,
				output_
			>::type
		>
	>
{
} ;
template < typename ... bf , typename mem , typename input_ , typename output_ >
struct exec_bf_impl < ftmp::list < cur_dec , bf ... > , ftmp::list < mem , input_ , output_ > >
	: exec_bf_impl
	<
		ftmp::list < bf ... > ,
		ftmp::list
		<
			typename cur_dec_memory
			<
				mem
			>::type ,
			input_ ,
			output_
		>
	>
{
} ;
template < typename ... bf , typename mem , typename input_ , typename output_ >
struct exec_bf_impl < ftmp::list < cur_inc , bf ... > , ftmp::list < mem , input_ , output_ > >
	: exec_bf_impl
	<
		ftmp::list < bf ... > ,
		ftmp::list
		<
			typename cur_inc_memory
			<
				mem
			>::type ,
			input_ ,
			output_
		>
	>
{
} ;
template < typename ... bf , typename mem , typename input_ , typename output_ >
struct exec_bf_impl < ftmp::list < ptr_dec , bf ... > , ftmp::list < mem , input_ , output_ > >
	: exec_bf_impl
	<
		ftmp::list < bf ... > ,
		ftmp::list
		<
			typename ptr_dec_memory
			<
				mem
			>::type ,
			input_ ,
			output_
		>
	>
{
} ;
template < typename ... bf , typename mem , typename input_ , typename output_ >
struct exec_bf_impl < ftmp::list < ptr_inc , bf ... > , ftmp::list < mem , input_ , output_ > >
	: exec_bf_impl
	<
		ftmp::list < bf ... > ,
		ftmp::list
		<
			typename ptr_inc_memory
			<
				mem
			>::type ,
			input_ ,
			output_
		>
	>
{
} ;
template < typename loop_ , typename ... bf , typename env >
struct exec_bf_impl < ftmp::list < loop < loop_ > , bf ... > , env >
	: exec_bf_impl_impl
	<
		loop < loop_ > ,
		ftmp::list < bf ... > ,
		typename exec_bf_impl < loop_ , env >::type
	>
{
} ;
template < typename env >
struct exec_bf_impl < ftmp::list < > , env >
	: ftmp::id < env >
{
} ;
template < typename , typename >
struct exec_bf ;
template < typename xs , typename chs , typename input_ >
struct exec_bf < ftmp::list < xs , chs > , input_ >
	: ftmp::reverse
	<
		typename ftmp::at
		<
			typename exec_bf_impl
			<
				xs ,
				ftmp::list
				<
					memory < ftmp::list < > , ftmp::integral < unsigned char , '\0' > , ftmp::list < > > ,
					input_ ,
					ftmp::list < >
				>
			>::type ,
			ftmp::integral < int , 2 >
		>::type
	>
{
} ;
template < typename >
struct print_impl ;
template < unsigned char ... ch >
struct print_impl < ftmp::list < ftmp::integral < unsigned char , ch > ... > >
{
	static auto func ( ) -> void
	{
		std::cout << std::string { ch ... } << std::endl ;
	}
} ;
template < typename T >
auto print ( )-> void
{
	print_impl < T >::func ( ) ;
}
auto main ( ) -> int
{
	std::cout
	<< "=====" << std::endl
	<< "1st example" << std::endl
	<< "=====" << std::endl
	<< std::endl ;
	using source001 = ftmp::list
	<
		CH ( '+' ) ,
		CH ( '[' ) ,
		CH ( '>' ) ,
		CH ( ',' ) ,
		CH ( '.' ) ,
		CH ( '<' ) ,
		CH ( ']' )
	> ;
	using code001 = parse_bf < source001 >::type ;
	using input001 = ftmp::list
	<
		CH ( 'E' ) ,
		CH ( 'c' ) ,
		CH ( 'h' ) ,
		CH ( 'o' ) ,
		CH ( ' ' ) ,
		CH ( 's' ) ,
		CH ( 'a' ) ,
		CH ( 'm' ) ,
		CH ( 'p' ) ,
		CH ( 'l' ) ,
		CH ( 'e' ) ,
		CH ( '!' )
	> ;
	using exe_res001 = typename exec_bf
	<
		code001 ,
		input001
	>::type ;
	print < exe_res001 > ( ) ;
	std::cout
	<< std::endl
	<< "=====" << std::endl
	<< "2nd example" << std::endl
	<< "=====" << std::endl
	<< std::endl ;
	using source002 = ftmp::list
	<
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '[' ) ,
		CH ( '>' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '>' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '>' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '<' ) ,
		CH ( '<' ) ,
		CH ( '<' ) ,
		CH ( '-' ) ,
		CH ( ']' ) ,
		CH ( '>' ) ,
		CH ( '.' ) ,
		CH ( '>' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '.' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '.' ) ,
		CH ( '.' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '.' ) ,
		CH ( '>' ) ,
		CH ( '-' ) ,
		CH ( '.' ) ,
		CH ( '-' ) ,
		CH ( '-' ) ,
		CH ( '-' ) ,
		CH ( '-' ) ,
		CH ( '-' ) ,
		CH ( '-' ) ,
		CH ( '-' ) ,
		CH ( '-' ) ,
		CH ( '-' ) ,
		CH ( '-' ) ,
		CH ( '-' ) ,
		CH ( '-' ) ,
		CH ( '.' ) ,
		CH ( '<' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '.' ) ,
		CH ( '-' ) ,
		CH ( '-' ) ,
		CH ( '-' ) ,
		CH ( '-' ) ,
		CH ( '-' ) ,
		CH ( '-' ) ,
		CH ( '-' ) ,
		CH ( '-' ) ,
		CH ( '.' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '+' ) ,
		CH ( '.' ) ,
		CH ( '-' ) ,
		CH ( '-' ) ,
		CH ( '-' ) ,
		CH ( '-' ) ,
		CH ( '-' ) ,
		CH ( '-' ) ,
		CH ( '.' ) ,
		CH ( '-' ) ,
		CH ( '-' ) ,
		CH ( '-' ) ,
		CH ( '-' ) ,
		CH ( '-' ) ,
		CH ( '-' ) ,
		CH ( '-' ) ,
		CH ( '-' ) ,
		CH ( '.' ) ,
		CH ( '>' ) ,
		CH ( '+' ) ,
		CH ( '.' )
	> ;
	using code002 = parse_bf < source002 >::type ;
	using input002 = ftmp::list
	<
	> ;
	using exe_res002 = typename exec_bf
	<
		code002 ,
		input002
	>::type ;
	print < exe_res002 > ( ) ;
}