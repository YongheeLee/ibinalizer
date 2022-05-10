#define _CRT_SECURE_NO_WARNINGS
#include <BmpT.h>

std::shared_ptr<BmpT> BmpT::create(const char* path, ImgTypeN type)
{
	BmpPtr bmp = std::make_shared<BmpT>();
	bmp->allocByFile(path, type);

	return bmp;
}

std::shared_ptr<BmpT> BmpT::create(int width, int height, ImgTypeN type)
{
	BmpPtr bmp = std::make_shared<BmpT>();
	bmp->allocBySize(width, height, type);

	return bmp;
}


void BmpT::allocByFile(const char* path, ImgTypeN type)
{
	FILE* fp = fopen(path, "rb");
	if (fp == nullptr)
		return;

	const int headerSize = 54;
	unsigned char info[headerSize];
	fread(info, sizeof(unsigned char), headerSize, fp);

	wid = *(int*)&info[18];
	hei = *(int*)&info[22];
	imgType = type;

	int pxSz = 0;

	if (imgType == ImgTypeN::Color)
	{
		pxSz = 3;
		data = (unsigned char*)calloc(wid * hei * pxSz, sizeof(unsigned char));
		fread(data, sizeof(unsigned char), wid * hei * 3, fp);
	}
	else if (imgType == ImgTypeN::Gray)
	{
		pxSz = 1;
		unsigned char* tmp = (unsigned char*)calloc(wid * hei * 3, sizeof(unsigned char));
		fread(tmp, sizeof(unsigned char), wid * hei * 3, fp);

		data = (unsigned char*)calloc(wid * hei * pxSz, sizeof(unsigned char));

		for (int h = 0; h < hei; ++h)
		{
			for (int w = 0; w < wid; ++w)
			{
				int idx = (h * wid + w) * 3;
				float r = float(tmp[idx + 2]);
				float g = float(tmp[idx + 1]);
				float b = float(tmp[idx + 0]);
				unsigned char gray = (unsigned char)(0.2126f * r + 0.7152f * g + 0.0722f * b);
				data[h * wid + w] = gray;
			}
		}

		free(tmp);
	}

	fclose(fp);
}

void BmpT::allocBySize(int width, int height, ImgTypeN type)
{
	wid = width;
	hei = height;
	imgType = type;

	int pxSz = imgType == ImgTypeN::Unknown ? 0 : imgType == ImgTypeN::Gray ? 1 : 3;
	data = (unsigned char*)calloc(wid * hei * pxSz, sizeof(unsigned char));
}