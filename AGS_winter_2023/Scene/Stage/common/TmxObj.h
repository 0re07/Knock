#pragma once
#include <map>
#include <string>
#include <vector>
#include "../../../Manager/ImageMng.h"
#include "../../../common/Collision.h"
#include "../../../common/ColBox.h"
#include "../../../common/Vector2D.h"

#include "../../../rapidxml/rapidxml.hpp"
#include "../../../rapidxml/rapidxml_utils.hpp"

class GetAttr;

using MapData = std::map<std::string, std::vector<int>>;
						//string�͑傫���̂œ��삪�x���Ȃ�
						//�ق�Ƃ�enum�Ƃ�������

class TmxObj
{
public:
	TmxObj();
	~TmxObj();

	bool LoadTMX(std::string fileName);
	bool SetMap(rapidxml::xml_node<>* node);

	//�Փ˔���̎擾
	const ColList& GetColList(void);
	const ColList& GetAbyssColList(void);
	const ColList& GetJumpColList(void);
	const ColList& GetFallColList(void);

	//�e�}�b�v�f�[�^�̎擾
	const MapData& GetMapData(void);	
	const int GetMapData(std::string layer, const Vector2D pos);	//pos�͍��W
	const int GetMapData(std::string layer, int x, int y);
	const Vector2D& GetWorldArea(void);	
	const Vector2D& GetTileSize(void);
	const std::string& GetMapKey(void);

	ColBox col_;

private:
	bool LoadTSX(std::string fileName);

	void SetColList(rapidxml::xml_node<>* node, std::string colName,ColList& colList);

	//TSX
	rapidxml::xml_document<> tsxDoc_;

	//TMX
	rapidxml::xml_document<> tmxDoc_;

	unsigned int layerSize_;	//���̃��C���[��ID
	Vector2D worldArea_;		//�}�b�v��ʂ̃T�C�Y
	Vector2D tileSize_;			//�^�C���̃T�C�Y

	//�Փ˔���
	ColList colList_;			//�X�e�[�W
	ColList abyssColList_;		//������Ƃ�
	ColList jumpColList_;		//�W�����v
	ColList fallColList_;		//���n�_

	MapData mapData_;
	std::string mapKey_;
};

