#include<utility>
#include<vector>
#include<iostream>
auto main ( ) -> int
{
	std::cout
	<< "# 彼女募集" << std::endl
	<< "==================" << std::endl
	<< "## 募集の背景" << std::endl
	<< "" << std::endl
	<< "楽しく話せ  " << std::endl
	<< "互いに悩みや希望を共有し  " << std::endl
	<< "一緒に落ち着いていられるような  " << std::endl
	<< "そんな相手が欲しいと思い  " << std::endl
	<< "彼女を募集します  " << std::endl
	<< "" << std::endl
	<< "## パートナーの条件" << std::endl
	<< "" << std::endl ;
	int i = 1 ;
	for ( auto str :
	{
		"たばこを吸わない人" ,
		"スレンダー体型" ,
		"論理的に話すことの出来る人" ,
		"お互いが対等の立場に立てる人" ,
		"ネガティブでない人" ,
		"あまり負の方向性に感情的にならない人" ,
		"Twitter、女優、モデル等の僕の趣味を認めてくれる人" ,
	} )
	{
		std::cout << i << ". " << str << std::endl ;
		++ i ;
	}
	std::cout
	<< std::endl
	<< "## こんな人はアウトです" << std::endl
	<< "" << std::endl ;
	i = 1 ;
	for ( auto str :
	{
		"タバコ吸う人" ,
		"ぽっちゃり体型" ,
		"上に列挙された条件を見て「体型が条件に入ってる！　見た目で判断良くない！」という人" ,
		"というかそもそも僕の列挙した条件を見てブチ切れない人" ,
	} )
	{
		std::cout << i << ". " << str << std::endl ;
		++ i ;
	}
	std::cout
	<< std::endl
	<< "## 南山まさかずのプロフィール" << std::endl
	<< "" << std::endl ;
	for ( auto elem : std::vector < std::pair < std::string , std::string > >
	{
		{ "年齢" , "19歳" } ,
		{ "性別" , "男" } ,
		{ "身長" , "160cm" } ,
		{ "体重" , "50～52kgをふらふら" } ,
		{ "性格" , "マイペース　興味のあることにとことん取り組む　比較的頑固？　好奇心結構あります" } ,
		{ "好きな動物" , "ネコ" } ,
		{ "恋愛対象" , "女性" } ,
		{ "恋愛遍歴" , "中学時代に1回、高校時代に2回女性と付き合ったことがあります" } ,
		{ "職業（？）" , "大学生" } ,
		{ "趣味" , "読書　プログラミング　Twitter　女優・モデル" } ,
		{ "言語" , "C++(C++11) Haskell" } ,
		{ "OS" , "Windows Linux" } ,
		{ "マシン" , "こだわりなし（今持ってるのはLenovoのです）" } ,
		{ "好きな女優・モデル" , "主に能年玲奈、桑田彩" } ,
		{ "好きなアーティスト" , "miwa" } ,
		{ "好きな音楽" , "supercellの曲とか" } ,
	} )
	{
		std::cout << "* " << elem.first << ':' << elem.second << std::endl ;
	}
	std::cout
	<< std::endl
	<< "## 連絡先" << std::endl
	<< "" << std::endl
	<< "パートナーの条件のとりあえず半分以上を満たしている人  " << std::endl
	<< "よろしくお願いします”  " << std::endl
	<< "" << std::endl
	<< "email:masakazu.minamiyama@gmail.com" << std::endl ;
}