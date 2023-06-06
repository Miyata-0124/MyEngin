#include "JsonLoader.h"
#include"DirectXTex/DirectXTex.h"

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
	
}
