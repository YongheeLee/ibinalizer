#pragma once
#include <Base.h>

class IImageT
{
public:
	IImageT() {}

public:
	virtual const unsigned char* getDataAll() = 0;
	virtual const unsigned char* getData(int x, int y) = 0;

	virtual ImgTypeN getImgType() = 0;
	virtual int width() = 0;
	virtual int height() = 0;

	virtual const unsigned char* getDataAll() const = 0;
	virtual const unsigned char* getData(int x, int y) const = 0;

	virtual ImgTypeN getImgType() const = 0;
	virtual int width() const = 0;
	virtual int height() const = 0;
};
