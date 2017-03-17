#pragma once 
#include "../FColor/FColor.h"

#include <iostream>

struct FColor;

typedef struct Color{
	unsigned char r;
	unsigned char g;
	unsigned char b;

	Color();
	Color(unsigned char);
	Color(unsigned char,unsigned char,unsigned char);
	~Color();

	void set(unsigned char,unsigned char,unsigned char);// 色の設定
	void print() const; //出力
	FColor& toFColor();// FColorに変換

	Color& operator+(const Color&)const;// 足し算
	Color& operator-(const Color&)const;// 引き算
	Color& operator*(const Color&)const;// 掛け算(255が最大値)
	Color& operator*(unsigned char)const;// 全色への均等な掛け算

	Color& operator+(const unsigned char)const;// 全要素に加算
	Color& operator-(const unsigned char)const;// 全要素に減算

	Color& operator+=(const Color&);// 自身に加算
	Color& operator-=(const Color&);// 自身に減算
	Color& operator*=(const Color&);// 自身に乗算
	Color& operator*=(unsigned char);// 自身の全要素に乗算a

	// Colorが右辺になる場合
	friend Color& operator+(unsigned char,const Color&);// 自身の全要素に加算
	friend Color& operator-(unsigned char,const Color&);// 自身の全要素に減算
	friend Color& operator*(unsigned char,const Color&);// 自身の全要素に乗算
	friend std::ostream& operator<<(std::ostream&,const Color&);// 文字列を出力

	unsigned char& operator[](unsigned int)const;// 0:R 1:G 2:B
} color_t;
