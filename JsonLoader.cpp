#include "JsonLoader.h"
#include "DirectXTex/DirectXTex.h"
#include <nlohmann/json.hpp>

void JsonLoader::LoadFlomJSONInternal(const std::string& modelname)
{
	//�t�@�C���X�g���[��
	std::ifstream file;

	//.json�t�@�C�����J��
	const std::string filename = modelname + ".json";
	const std::string directoryPath = "Resources/" + modelname + "/";
	//�t�@�C�����J��
	file.open(directoryPath + filename);
	//�t�@�C���I�[�v�����`�F�b�N
	if (file.fail()) { //���s������
		assert(0);
	}

	//JSON�����񂩂�𓀂����f�[�^
	nlohmann::json deserialize;

	//��
	file >> deserialize;

	//���������x���G�f�B�^�t�@�C�����`�F�b�N
	assert(deserialize.is_object());
	assert(deserialize.contains("name"));
	assert(deserialize["name"].is_string());

	//"name"�𕶎���Ƃ��Ď擾
	std::string name = deserialize["name"].get<std::string>();
	//���������x���G�f�B�^�t�@�C�����`�F�b�N
	assert(name.compare("scene") == 0);


}
