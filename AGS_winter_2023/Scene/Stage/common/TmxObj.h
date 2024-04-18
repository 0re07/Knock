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
						//stringは大きいので動作が遅くなる
						//ほんとはenumとかがいい

class TmxObj
{
public:
	TmxObj();
	~TmxObj();

	bool LoadTMX(std::string fileName);
	bool SetMap(rapidxml::xml_node<>* node);

	//衝突判定の取得
	const ColList& GetColList(void);
	const ColList& GetAbyssColList(void);
	const ColList& GetJumpColList(void);
	const ColList& GetFallColList(void);

	//各マップデータの取得
	const MapData& GetMapData(void);	
	const int GetMapData(std::string layer, const Vector2D pos);	//posは座標
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

	unsigned int layerSize_;	//次のレイヤーのID
	Vector2D worldArea_;		//マップ画面のサイズ
	Vector2D tileSize_;			//タイルのサイズ

	//衝突判定
	ColList colList_;			//ステージ
	ColList abyssColList_;		//落ちるとこ
	ColList jumpColList_;		//ジャンプ
	ColList fallColList_;		//着地点

	MapData mapData_;
	std::string mapKey_;
};

