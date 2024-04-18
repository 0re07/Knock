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
	rapidxml::file<> xmlFile = fileName.c_str();		//	ファイルを開く 
	tmxDoc_.parse<0>(xmlFile.data());					//	中身にアクセスできるようになる

	//解析
	rapidxml::xml_node<>* mapNode = tmxDoc_.first_node("map");
	if (mapNode == nullptr)
	{
		TRACE("null値:mapNode\n" );
		return false;
	}
	rapidxml::xml_node<>* tileset = mapNode->first_node("tileset");
	if (tileset == nullptr)
	{
		TRACE("null値:tileset\n" );
		return false;
	}
	rapidxml::xml_attribute<>* tsxSource = tileset->first_attribute("source");
	if (tsxSource == nullptr)
	{
		TRACE("null値:tsxSource\n");
		return false;
	}

	auto getAtr = GetAttr();				//関数オブジェクトを使う
	if (!getAtr(mapNode,"nextlayerid", layerSize_))
	{
		TRACE("null値:layerSize_\n");
		return false;
	}
	layerSize_--;		//nextlayeridの値はレイヤー総数からすると＋1されているため減算

	if (!getAtr(mapNode, "width", worldArea_.x))
	{
		TRACE("null値:worldArea_.x\n");
		return false;
	}
	if (!getAtr(mapNode, "height", worldArea_.y))
	{
		TRACE("null値:worldArea_.y\n");
		return false;
	}
	if (!getAtr(mapNode, "tilewidth", tileSize_.x))
	{
		TRACE("null値:tsxSource\n");
		return false;
	}
	if (!getAtr(mapNode, "tileheight", tileSize_.y))
	{
		TRACE("null値:tsxSource\n" );
		return false;
	}

	auto filePass = fileName.substr(0, fileName.find_last_of("/") + 1);
	LoadTSX(filePass + tsxSource->value());

	if (!SetMap(mapNode))
	{
		TRACE("null値:mapNode\n");
		return false;
	}

	return SetMap(mapNode);
}

bool TmxObj::LoadTSX(std::string fileName)
{
	rapidxml::file<> xmlFile = fileName.c_str();		//	ファイルを開く
	tsxDoc_.parse<0>(xmlFile.data());					//	中身にアクセスできるようになる

	//解析
	rapidxml::xml_node<>* tileset = tsxDoc_.first_node("tileset");
	if (tileset == nullptr)
	{
		TRACE("null値:tileset\n");
		return false;
	}
	rapidxml::xml_attribute<>* version = tileset->first_attribute("version");
	rapidxml::xml_attribute<>* tiledversion = tileset->first_attribute("tiledversion");
	//TRACE("TSX vesion : %s\n", version->value());
	//TRACE("Tiled vesion : %s\n", tiledversion->value());

	int tilewidth;				//タイルの幅
	int tileheight;				//タイルの高さ
	int tilecount;				//タイルの数
	int columns;

	auto getAtr = GetAttr();	//関数オブジェクトを使う
	if (!getAtr(tileset,"tilewidth", tilewidth))
	{
		TRACE("null値:tilewidth\n");
		return false;
	}
	if (!getAtr(tileset, "tileheight", tileheight))
	{
		TRACE("null値:tileheight\n");
		return false;
	}
	if (!getAtr(tileset, "tilecount", tilecount))
	{
		TRACE("null値:tilecount\n");
		return false;
	}
	if (!getAtr(tileset, "columns", columns))
	{
		TRACE("null値:columns\n");
		return false;
	}

	rapidxml::xml_node<>* imageNode = tileset->first_node("image");
	if (imageNode == nullptr)
	{
		TRACE("null値:imageNode\n");
		return false;
	}

	rapidxml::xml_attribute<>* source = imageNode->first_attribute("source");
	if (source == nullptr)
	{
		TRACE("null値:source\n");
		return false;
	}

	if (!getAtr(imageNode, "mapKey", mapKey_))
	{
		TRACE("null値:mapKey\n");
		return false;
	}

	std::string sourcePass = source->value();
	lpImageMng.GetID("./tmx" + sourcePass.substr(1), mapKey_, { tilewidth,tileheight }, { columns, tilecount / columns });

	return true;
}

/// <summary>
/// 衝突判定の取得
/// </summary>
/// <param name="node">取得先ノード</param>
/// <param name="colName">取得コリジョンの名前</param>
/// <param name="colList">コリジョン格納先</param>
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

	//レイヤーがなくなるまで
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

		//レイヤーがコリジョン(当たり判定)の場合はもう一度
		if (layerName == "Col" || 
			layerName == "abyssCol" ||
			layerName == "jump" ||
			layerName == "fall")
		{
			continue;
		}

		//レイヤーの幅と高さを取る
		Vector2D layerSize;
		getAtr(layer, "width", layerSize.x);
		getAtr(layer, "height", layerSize.y);

		//	Vector2Dなので初期値0
		//	0が入ると後々falseになるためnullチェックしてない

		if (worldArea_ != layerSize)
		{
			return false;
		}

		//csvつくる
		auto layerDeta = mapData_.try_emplace(layerName);			//格納先
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

		//文字列をばらしてデータからマップの詳しい情報を格納する
		std::stringstream dataStream;
		dataStream << csvData->value();					//データを流し込む
		for (auto& vecData : layerDeta.first->second)
		{
			std::string numStr;
			getline(dataStream, numStr, ',');
			vecData = atoi(numStr.c_str()) - firstgid;	//画像のずれを修正
		}
	}

	//衝突判定の取得
	SetColList(node, "Col", colList_);				//ステージ
	SetColList(node, "abyssCol", abyssColList_);	//落ちるところ
	SetColList(node, "jump", jumpColList_);			//ジャンプ台
	SetColList(node, "fall", fallColList_);			//ジャンプ台

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
		TRACE("指定したlayerが存在しない\n");
		return false;
	}
	if (x > worldArea_.x || x < 0 ||
		y > worldArea_.y || y < 0)
	{
		TRACE("xまたはyが範囲内ではない\n");
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
