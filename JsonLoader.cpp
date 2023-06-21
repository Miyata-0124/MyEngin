#include "JsonLoader.h"
#include "DirectXTex/DirectXTex.h"
#include <nlohmann/json.hpp>

void JsonLoader::LoadFlomJSONInternal(const std::string& modelname)
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


}
