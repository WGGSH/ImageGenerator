#include "Color.h"

#include <iostream>
using namespace std;

// 全要素を0で初期化するコンストラクタ
Color::Color()
{
	for(int i=0;i<3;i++){
		(*this)[i]=0;
	}
}

// 全要素を指定の値で初期化するコンストラクタ
Color::Color(unsigned char val) :
	r(val),g(val),b(val)
{
}
// 引数から初期値を決定するコンストラクタ
Color::Color(unsigned char r,unsigned char g,unsigned char b):
	r(r),g(g),b(b)
{
}

// デストラクタ
Color::~Color()
{
}

// 色の設定
void Color::set(unsigned char r,unsigned char g,unsigned char b)
{
	this->r=r;
	this->g=g;
	this->b=b;
	return;
}

// 出力
void Color::print()const
{
	cout<<"(";
	for(int i=0;i<3;i++){
		cout<<static_cast<int>((*this)[i]);
		if(i!=2)cout<<",";
	}
	cout<<")"<<endl;
	return;
}

// FColorに変換
/*FColor& Color::toFColor()
{
	return *new FColor(this->r/255.0f,this->g/255.0f,this->b/255.0f);
}*/

// +operator
// 各要素の和を返す
Color& Color::operator+(const Color& color)const
{
	Color *rCol=new Color();
	int buf=0;
	for(int i=0;i<3;i++){
		buf=(*this)[i]+const_cast<Color&>(color)[i];
		if(buf>255)buf=255;
		if(buf<0)buf=0;
		(*rCol)[i]=buf;
	}
	return *rCol;	
}

// -operator
// 各要素の差を返す
Color& Color::operator-(const Color& color)const
{
	Color *rCol=new Color();
	int buf=0;
	for(int i=0;i<3;i++){
		buf=(*this)[i]-const_cast<Color&>(color)[i];
		if(buf>255)buf=255;
		if(buf<0)buf=0;
		(*rCol)[i]=buf;
	}
	return *rCol;
}

// *operator
// 各要素の乗算
Color& Color::operator*(const Color& color)const
{
	Color *rCol=new Color();
	for(int i=0;i<3;i++){
		int buf=static_cast<int>((*this)[i]*const_cast<Color&>(color)[i]/255.0f);
		if(buf>255)buf=255;
		if(buf<0)buf=0;
		(*rCol)[i]=buf;
	}
	return *rCol;
}

// *operator
// 全要素を指定した値の乗算
Color& Color::operator*(unsigned char val)const
{
	Color *rCol=new Color();
	for(int i=0;i<3;i++){
		int buf=static_cast<int>((*this)[i]*val/255.0f);
		if(buf>255)buf=255;
		if(buf<0)buf=0;
		(*rCol)[i]=buf;
	}
	return *rCol;
}

// +operator
// 全要素に整数を加算
Color& Color::operator+(unsigned char val)const
{
	Color *rCol=new Color();
	for(int i=0;i<3;i++){
		int buf=(*this)[i]+val;
		if(buf<0)buf=0;
		if(buf>255)buf=255;
		(*rCol)[i]=buf;
	}
	return *rCol;
}

// -operator
// 全要素に整数を減算
Color& Color::operator-(unsigned char val)const
{
	Color *rCol=new Color();
	for(int i=0;i<3;i++){
		int buf=(*this)[i]-val;
		if(buf<0)buf=0;
		if(buf>255)buf=255;
		(*rCol)[i]=buf;
	}
	return *rCol;
}

// +=operator
// 自身に加算する
Color& Color::operator+=(const Color& color)
{
	for(int i=0;i<3;i++){
		int buf=(*this)[i]+const_cast<Color&>(color)[i];
		if(buf>255)buf=255;
		if(buf<0)buf=0;
		(*this)[i]=buf;
	}
	return *this;
}

// -=operator
// 自身に加算する
Color& Color::operator-=(const Color& color)
{
	for(int i=0;i<3;i++){
		int buf=(*this)[i]-const_cast<Color&>(color)[i];
		if(buf>255)buf=255;
		if(buf<0)buf=0;
		(*this)[i]=buf;
	}
	return *this;
}

// *=operator
// 自身に加算する
Color& Color::operator*=(const Color& color)
{
	for(int i=0;i<3;i++){
		int buf=static_cast<int>((*this)[i]*const_cast<Color&>(color)[i]/255.0f);
		if(buf>255)buf=255;
		if(buf<0)buf=0;
		(*this)[i]=buf;
	}
	return *this;
}

// *=operator
// 自身の全要素に加算する
Color& Color::operator*=(unsigned char val)
{
	for(int i=0;i<3;i++){
		int buf=static_cast<int>((*this)[i]*val/255.0f);
		if(buf>255)buf=255;
		if(buf<0)buf=0;
		(*this)[i]=buf;
	}
	return *this;
}

// グローバル演算子オーバーロード

// +operator
// unsigned char + Color
Color& operator+(unsigned char val,const Color& col)
{
	Color *rCol=new Color();
	for(int i=0;i<3;i++){
		int buf=val+col[i];
		if(buf<0)buf=0;
		if(buf>255)buf=255;
		(*rCol)[i]=buf;
	}
	return *rCol;
}

// -operator
// unsigned char - Color
Color& operator-(unsigned char val,const Color& col)
{
	Color *rCol=new Color();
	for(int i=0;i<3;i++){
		int buf=val-col[i];
		if(buf<0)buf=0;
		if(buf>255)buf=255;
		(*rCol)[i]=buf;
	}
	return *rCol;
}

// *operator
// unsigned char - Color
Color& operator*(unsigned char val,const Color& col)
{
	Color *rCol=new Color();
	for(int i=0;i<3;i++){
		int buf=static_cast<int>(col[i]*val/255.0f);
		if(buf<0)buf=0;
		if(buf>255)buf=255;
		(*rCol)[i]=buf;
	}
	return *rCol;
}

// <<operator
// 自身の文字列を渡す
ostream& operator<<(ostream& os,const Color& col)
{
	os<<"(";
	for(int i=0;i<3;i++){
		os<<static_cast<int>(col[i]);
		if(i!=2)os<<",";
	}
	os<<")";
	return os;
}

// []operator
// 0~2の値を渡すと,それぞれ対応するRGB値を返す
unsigned char& Color::operator[](unsigned int index)const
{
	switch(index){
		case 0:
			return const_cast<unsigned char&>(this->r);
			break;
		case 1:
			return const_cast<unsigned char&>(this->g);
			break;
		case 2:
			return const_cast<unsigned char&>(this->b);
			break;
		default:
			return const_cast<unsigned char&>(this->r);
			break;
	}
}

