#include <sstream>
#include "../../../Manager/ImageMng.h"
#include "GetAttr.h"
#include "TmxObj.h"

#include "../../../_debug/_DebugConOut.h"
#include "../../../_debug/_DebugDispOut.h"

TmxObj::TmxObj()
{
}

TmxObj::~TmxObj()
{
}

bool TmxObj::LoadTMX(std::string fileName)
{
	rapidxml::file<> xmlFile = fileName.c_str();		//	�t�@�C�����J�� 
	tmxDoc_.parse<0>(xmlFile.data());					//	���g�ɃA�N�Z�X�ł���悤�ɂȂ�

	//���
	rapidxml::xml_node<>* mapNode = tmxDoc_.first_node("map");
	if (mapNode == nullptr)
	{
		TRACE("null�l:mapNode\n" );
		return false;
	}
	rapidxml::xml_node<>* tileset = mapNode->first_node("tileset");
	if (tileset == nullptr)
	{
		TRACE("null�l:tileset\n" );
		return false;
	}
	rapidxml::xml_attribute<>* tsxSource = tileset->first_attribute("source");
	if (tsxSource == nullptr)
	{
		TRACE("null�l:tsxSource\n");
		return false;
	}

	auto getAtr = GetAttr();				//�֐��I�u�W�F�N�g���g��
	if (!getAtr(mapNode,"nextlayerid", layerSize_))
	{
		TRACE("null�l:layerSize_\n");
		return false;
	}
	layerSize_--;		//nextlayerid�̒l�̓��C���[�������炷��Ɓ{1����Ă��邽�ߌ��Z

	if (!getAtr(mapNode, "width", worldArea_.x))
	{
		TRACE("null�l:worldArea_.x\n");
		return false;
	}
	if (!getAtr(mapNode, "height", worldArea_.y))
	{
		TRACE("null�l:worldArea_.y\n");
		return false;
	}
	if (!getAtr(mapNode, "tilewidth", tileSize_.x))
	{
		TRACE("null�l:tsxSource\n");
		return false;
	}
	if (!getAtr(mapNode, "tileheight", tileSize_.y))
	{
		TRACE("null�l:tsxSource\n" );
		return false;
	}

	auto filePass = fileName.substr(0, fileName.find_last_of("/") + 1);
	LoadTSX(filePass + tsxSource->value());

	if (!SetMap(mapNode))
	{
		TRACE("null�l:mapNode\n");
		return false;
	}

	return SetMap(mapNode);
}

bool TmxObj::LoadTSX(std::string fileName)
{
	rapidxml::file<> xmlFile = fileName.c_str();		//	�t�@�C�����J��
	tsxDoc_.parse<0>(xmlFile.data());					//	���g�ɃA�N�Z�X�ł���悤�ɂȂ�

	//���
	rapidxml::xml_node<>* tileset = tsxDoc_.first_node("tileset");
	if (tileset == nullptr)
	{
		TRACE("null�l:tileset\n");
		return false;
	}
	rapidxml::xml_attribute<>* version = tileset->first_attribute("version");
	rapidxml::xml_attribute<>* tiledversion = tileset->first_attribute("tiledversion");
	//TRACE("TSX vesion : %s\n", version->value());
	//TRACE("Tiled vesion : %s\n", tiledversion->value());

	int tilewidth;				//�^�C���̕�
	int tileheight;				//�^�C���̍���
	int tilecount;				//�^�C���̐�
	int columns;

	auto getAtr = GetAttr();	//�֐��I�u�W�F�N�g���g��
	if (!getAtr(tileset,"tilewidth", tilewidth))
	{
		TRACE("null�l:tilewidth\n");
		return false;
	}
	if (!getAtr(tileset, "tileheight", tileheight))
	{
		TRACE("null�l:tileheight\n");
		return false;
	}
	if (!getAtr(tileset, "tilecount", tilecount))
	{
		TRACE("null�l:tilecount\n");
		return false;
	}
	if (!getAtr(tileset, "columns", columns))
	{
		TRACE("null�l:columns\n");
		return false;
	}

	rapidxml::xml_node<>* imageNode = tileset->first_node("image");
	if (imageNode == nullptr)
	{
		TRACE("null�l:imageNode\n");
		return false;
	}

	rapidxml::xml_attribute<>* source = imageNode->first_attribute("source");
	if (source == nullptr)
	{
		TRACE("null�l:source\n");
		return false;
	}

	if (!getAtr(imageNode, "mapKey", mapKey_))
	{
		TRACE("null�l:mapKey\n");
		return false;
	}

	std::string sourcePass = source->value();
	lpImageMng.GetID("./tmx" + sourcePass.substr(1), mapKey_, { tilewidth,tileheight }, { columns, tilecount / columns });

	return true;
}

/// <summary>
/// �Փ˔���̎擾
/// </summary>
/// <param name="node">�擾��m�[�h</param>
/// <param name="colName">�擾�R���W�����̖��O</param>
/// <param name="colList">�R���W�����i�[��</param>
void TmxObj::SetColList(rapidxml::xml_node<>* node, std::string colName, ColList& colList)
{
	for (auto colNode = node->first_node("objectgroup");
		colNode != nullptr;
		colNode = colNode->next_sibling())
	{
		std::string grpName;

		auto getAtr = GetAttr();
		getAtr(colNode, "name", grpName);
		if (grpName != colName)
		{
			continue;
		}

		for (auto objNode = colNode->first_node("object");
			objNode != nullptr;
			objNode = objNode->next_sibling())
		{
			double x, y, w, h;
			getAtr(objNode, "x", x);
			getAtr(objNode, "y", y);
			getAtr(objNode, "width", w);
			getAtr(objNode, "height", h);

			colList.push_back(
				Collision
				{
					Vector2DDouble{x,y},
					Vector2DDouble{w,h}
				}
			);
		}
	}
}

bool TmxObj::SetMap(rapidxml::xml_node<>* node)
{
	if (node == nullptr)
	{
		return false;
	}

	auto tileset = node->first_node("tileset");
	if (tileset == nullptr)
	{
		return false;
	}

	auto getAtr = GetAttr();
	int firstgid;
	getAtr(tileset, "firstgid", firstgid);

	//���C���[���Ȃ��Ȃ�܂�
	for (auto layer = node->first_node("layer");
		layer != nullptr;
		layer = layer->next_sibling())
	{
		if (layer == nullptr)
		{
			return false;
		}

		std::string layerName;
		getAtr(layer, "name", layerName);

		//���C���[���R���W����(�����蔻��)�̏ꍇ�͂�����x
		if (layerName == "Col" || 
			layerName == "abyssCol" ||
			layerName == "jump" ||
			layerName == "fall")
		{
			continue;
		}

		//���C���[�̕��ƍ��������
		Vector2D layerSize;
		getAtr(layer, "width", layerSize.x);
		getAtr(layer, "height", layerSize.y);

		//	Vector2D�Ȃ̂ŏ����l0
		//	0������ƌ�Xfalse�ɂȂ邽��null�`�F�b�N���ĂȂ�

		if (worldArea_ != layerSize)
		{
			return false;
		}

		//csv����
		auto layerDeta = mapData_.try_emplace(layerName);			//�i�[��
		if (layerDeta.second)
		{
			layerDeta.first->second.resize(worldArea_.x * worldArea_.y);
		}

		auto data = layer->first_node("data");
		if (data == nullptr)
		{
			return false;
		}
		auto csvData = data->first_node();

		//��������΂炵�ăf�[�^����}�b�v�̏ڂ��������i�[����
		std::stringstream dataStream;
		dataStream << csvData->value();					//�f�[�^�𗬂�����
		for (auto& vecData : layerDeta.first->second)
		{
			std::string numStr;
			getline(dataStream, numStr, ',');
			vecData = atoi(numStr.c_str()) - firstgid;	//�摜�̂�����C��
		}
	}

	//�Փ˔���̎擾
	SetColList(node, "Col", colList_);				//�X�e�[�W
	SetColList(node, "abyssCol", abyssColList_);	//������Ƃ���
	SetColList(node, "jump", jumpColList_);			//�W�����v��
	SetColList(node, "fall", fallColList_);			//�W�����v��

	return true;
}

const ColList& TmxObj::GetColList(void)
{
	return colList_;
}

const ColList& TmxObj::GetAbyssColList(void)
{
	return abyssColList_;
}

const ColList& TmxObj::GetJumpColList(void)
{
	return jumpColList_;
}

const ColList& TmxObj::GetFallColList(void)
{
	return fallColList_;
}

const MapData& TmxObj::GetMapData(void)
{
	return mapData_;
}

const int TmxObj::GetMapData(std::string layer, const Vector2D pos)
{
	Vector2D grid = pos / tileSize_;
	return GetMapData(layer, grid.x, grid.y);
}

const int TmxObj::GetMapData(std::string layer, int x, int y)
{
	if (!mapData_.count(layer))
	{
		TRACE("�w�肵��layer�����݂��Ȃ�\n");
		return false;
	}
	if (x > worldArea_.x || x < 0 ||
		y > worldArea_.y || y < 0)
	{
		TRACE("x�܂���y���͈͓��ł͂Ȃ�\n");
		return false;
	}
	int point = x + y * worldArea_.x;

	if (point < 0 || point >= mapData_[layer].size())
	{
		return false;
	}
	if (mapData_[layer][point] < -1)
	{
		return false;
	}

	//mapData_[layer][point] = id;

	return mapData_[layer][point];
}

const Vector2D& TmxObj::GetWorldArea(void)
{
	return worldArea_;
}

const Vector2D& TmxObj::GetTileSize(void)
{
	return tileSize_;
}

const std::string& TmxObj::GetMapKey(void)
{
	return mapKey_;
}
