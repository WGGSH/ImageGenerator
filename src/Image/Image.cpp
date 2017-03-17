#include "Image.h"

using namespace std;

// コンストラクタ
Image::Image()
{
}

// デストラクタ
Image::~Image()
{
	this->colorDataList.clear();
	this->binaryData.clear();
}

// 4byte挿入する
void Image::intPush(unsigned int val)
{
	char *pval=reinterpret_cast<char*>(&val);
	for(int i=0;i<4;i++){
		this->binaryData.push_back(pval[i]);
	}
}

// 2byte挿入する
void Image::shortPush(unsigned short val)
{
	char *pval=reinterpret_cast<char*>(&val);
	for(int i=0;i<2;i++){
		this->binaryData.push_back(pval[i]);
	}
}

// 1byte挿入する
void Image::charPush(const unsigned char val)
{
	this->binaryData.push_back(val);
}

// 色情報を挿入する
void Image::colorPush(const Color& color)
{
	for(int i=2;i>=0;i--){
		this->charPush(const_cast<Color&>(color)[i]);
	}
}

// 出力処理
void Image::output()
{
	// 詰める領域の計算
	int padding=(4-(this->imageWidth*3)%4)%4;

	// 使用する情報
	unsigned int OFFSET=54;
	unsigned int IMAGESIZE=(this->imageWidth*3+padding)*this->imageHeight;
	unsigned int FILESIZE=IMAGESIZE+OFFSET;
	

	// ファイルヘッダの登録

	// 1:ファイルタイプ
	this->charPush('B');
	this->charPush('M');
	// 2:ファイルサイズ
	this->intPush(FILESIZE);
	// 3:予約領域1
	this->shortPush(0);
	// 4:予約領域2
	this->shortPush(0);
	// 5:ファイル先頭から画像データまでのオフセット
	this->intPush(OFFSET);

	// 情報ヘッダの登録

	// 1:情報ヘッダさイズ
	this->intPush(40);
	// 2:画像の幅
	this->intPush(this->imageWidth);
	// 3:画像の高さ
	this->intPush(this->imageHeight);
	// 4:プレーン数
	this->shortPush(1);
	// 5:色ビット数
	this->shortPush(24);
	// 6:圧縮形式
	this->intPush(0);
	// 7:画像データサイズ
	this->intPush(IMAGESIZE);
	// 8:水平解像度
	this->intPush(0);
	// 9:垂直解像度
	this->intPush(0);
	//10:格納パレット数
	this->intPush(0);
	//11:重要色数
	this->intPush(0);

	// 色情報の登録
	for(vector<vector<Color>>::reverse_iterator rit=this->colorDataList.rbegin(),end=this->colorDataList.rend();
			rit!=end;rit++){
		for(auto col:*rit){
			this->colorPush(col);
		}
		// 詰める
		for(int i=0;i<padding;i++)this->charPush(0);
	}

	// 出力
	ofstream outFile;
	outFile.open(this->outFileName,ios::out);

	for(auto binary:this->binaryData){
		outFile<<binary;
	}
}

// ファイル名の登録
void Image::setFileName(string name)
{
	this->outFileName=name;
}

// 画像サイズの設定
void Image::setImageSize(unsigned int width,unsigned int height)
{
	this->imageWidth=width;
	this->imageHeight=height;
	this->colorDataList.resize(this->imageHeight);
	for(auto &height:this->colorDataList){
		height.resize(this->imageWidth);
	}
}

// 画素の入力
void Image::setPixel(unsigned int x,unsigned int y,const Color& color)
{
	if(x<0 || x>=this->imageWidth || y<0 || y>=this->imageHeight)return;
	this->colorDataList.at(y).at(x)=color;
}

// 画素の入力
void Image::setPixel(unsigned int x,unsigned int y,const Color* color)
{
	if(x<0 || x>=this->imageWidth || y<0 || y>=this->imageHeight)return;
	this->colorDataList.at(y).at(x)=*color;
}

// 画素の初期化
void Image::clear()
{
	Color white={0,0,0};
	for(auto &height:this->colorDataList){
		for(auto &width:height){
			width=white;
		}
	}
}
