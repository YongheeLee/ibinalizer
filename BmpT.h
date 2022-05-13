#pragma once
#include <memory>
#include <mutex>
#include <IImageT.h>

class BmpT : public IImageT
{
public:
	BmpT() {}
	~BmpT() {
		if (data != nullptr)
			free(data);
	}

public:
	static std::shared_ptr<BmpT> create(const char* path, ImgTypeN type);
	static std::shared_ptr<BmpT> create(int width, int height, ImgTypeN type);

	void allocByFile(const char* path, ImgTypeN type);
	void allocBySize(int width, int height, ImgTypeN type);

	virtual const unsigned char* getDataAll() { return data; }
	virtual const unsigned char* getData(int x, int y) {
		if (data == nullptr)
			return nullptr;

		if (imgType == ImgTypeN::Gray)
			return &data[y * wid + x];
		else
			return &data[3 * (y * wid + x)];
	}
	
	virtual ImgTypeN getImgType() { return imgType; }
	virtual int width() { return wid; }
	virtual int height() { return hei; }

	virtual const unsigned char* getDataAll() const { return data; }
	virtual const unsigned char* getData(int x, int y) const {
		if (data == nullptr)
			return nullptr;

		if (imgType == ImgTypeN::Gray)
			return &data[y * wid + x];
		else
			return &data[3 * (y * wid + x)];
	}

	virtual ImgTypeN getImgType() const { return imgType; }
	virtual int width() const { return wid; }
	virtual int height() const { return hei; }

private:
	ImgTypeN imgType = ImgTypeN::Unknown;
	unsigned char* data = nullptr;
	int wid, hei;
	std::mutex mtx;
};

typedef std::shared_ptr<BmpT> BmpPtr;

