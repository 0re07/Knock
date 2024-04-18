#pragma once		
#include <map>
#include <vector>
#include <string>
#include "../common/Vector2D.h"

#define lpImageMng ImageMng::GetInstanse()

using VecInt = std::vector<int>;

class ImageMng
{
public:
	static ImageMng& GetInstanse()
	{
		static ImageMng s_Instance;
		return s_Instance;
	}

	const VecInt& GetID(std::string key);			//���ۂɎg�p����Ƃ��͂����ŌĂяo��
	const VecInt& GetID(std::string f_name, std::string key);										//LoadGraph��
	const VecInt& GetID(std::string f_name, std::string key, Vector2D divSize, Vector2D divCnt);	//LoadDivGraph��

private:
	ImageMng();
	~ImageMng();

	std::map<std::string, VecInt> imageMap_;

};

