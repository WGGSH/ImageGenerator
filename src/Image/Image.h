#include "../Color/Color.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Image{
private:
	std::string outFileName;                      // 出力ファイル名
	std::vector<char> binaryData;                 // 出力するバイナリ列
	unsigned int imageWidth;                      // 画像の横幅
	unsigned int imageHeight;                     // 画像の縦幅
  std::vector<std::vector<Color>> colorDataList;// 画像データ

	//出力データ生成用メソッド
	void charPush(const unsigned char);    // 1byte
	void shortPush(const unsigned short);  // 2byte
	void intPush(unsigned int);            // 4byte
	void colorPush(const Color&);          // 3byte(色情報)
public:
	Image(); // コンストラクタ
	~Image(); // デストラクタ

	void output();                                  // 画像の書き出し
	void setFileName(std::string);                  // 出力ファイル名の設定
	void setImageSize(unsigned int,unsigned int);   // 画像サイズの設定
	void setPixel(unsigned int,unsigned int,const Color&);// 画素の入力
	void setPixel(unsigned int,unsigned int,const Color*);// 画素の入力
	void clear();                                   // 画像情報の初期化
};

