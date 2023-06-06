#include "JsonLoader.h"
#include"DirectXTex/DirectXTex.h"

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
	
}
