#include "header/3D/JsonLoader.h"
#include "DirectXTex/include/DirectXTex.h"

using namespace nlohmann;

LevelData* JsonLoader::LoadFlomJSONInternal(const std::string& modelname)
{
	//ファイルストリーム
	std::ifstream file;

	//.jsonファイルを開く
	const std::string filename = modelname + ".json";
	const std::string directoryPath = "Resources/" + modelname + "/";
	//ファイルを開く
	file.open(directoryPath + filename);
	//ファイルオープンをチェック
	if (file.fail()) { //失敗したら
		assert(0);
	}

	//JSON文字列から解凍したデータ
	nlohmann::json deserialize;

	//解凍
	file >> deserialize;

	//正しいレベルエディタファイルかチェック
	assert(deserialize.is_object());
	assert(deserialize.contains("name"));
	assert(deserialize["name"].is_string());

	//"name"を文字列として取得
	std::string name = deserialize["name"].get<std::string>();
	//正しいレベルエディタファイルかチェック
	assert(name.compare("scene") == 0);

	//レベルデータ格納用インスタンスを生成
	LevelData* levelData = new LevelData();

	//"object"の全オブジェクトを走査
	for (nlohmann::json& object : deserialize["objects"]) {
		assert(object.contains("type"));

		//種別を取得
		std::string type = object["type"].get<std::string>();

		//種類ごとの処理
		//メッシュ
		if (type.compare("MESH") == 0) {
			// 要素の追加
			levelData->objects.emplace_back(LevelData::ObjectData{});
			//今追加した要素の参照を得る
			LevelData::ObjectData& objectData = levelData->objects.back();

			if (object.contains("file_name")) {
				objectData.fileName = object["file_name"];
			}

			//トランスフォームパラメータの読み込み
			nlohmann::json& transform = object["transform"];
			//平行移動
			objectData.position.m128_f32[0] = (float)transform["translation"][1];
			objectData.position.m128_f32[1] = (float)transform["translation"][2];
			objectData.position.m128_f32[2] = -(float)transform["translation"][0];
			objectData.position.m128_f32[3] = 1.0f;
			//回転角
			objectData.rotation.m128_f32[0] = -(float)transform["rotation"][1];
			objectData.rotation.m128_f32[1] = -(float)transform["rotation"][2];
			objectData.rotation.m128_f32[2] = (float)transform["rotation"][0];
			objectData.rotation.m128_f32[3] = 0.0f;
			//スケーリング
			objectData.scaling.m128_f32[0] = (float)transform["scaling"][1];
			objectData.scaling.m128_f32[1] = (float)transform["scaling"][2];
			objectData.scaling.m128_f32[2] = (float)transform["scaling"][0];
			objectData.scaling.m128_f32[3] = 0.0f;
			// TODO コライダーのパラメータ読み
			nlohmann::json& collider = object["collider"];
			//中心
			objectData.center.m128_f32[0] = (float)collider["center"][1];
			objectData.center.m128_f32[1] = (float)collider["center"][2];
			objectData.center.m128_f32[2] = (float)collider["center"][0];
			objectData.center.m128_f32[3] = 1.0f;
			//サイズ
			objectData.size.m128_f32[0] = (float)collider["size"][1];
			objectData.size.m128_f32[1] = (float)collider["size"][2];
			objectData.size.m128_f32[2] = (float)collider["size"][0];
			objectData.size.m128_f32[3] = 0.0f;
		}

		//再帰関数
		if (type.compare("children") == 0) {

		}
	}
	return levelData;
}
