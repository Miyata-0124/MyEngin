#include "JsonLoader.h"
#include "DirectXTex/DirectXTex.h"

using namespace nlohmann;

LevelData* JsonLoader::LoadFlomJSONInternal(const std::string& modelname)
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

	//���x���f�[�^�i�[�p�C���X�^���X�𐶐�
	LevelData* levelData = new LevelData();

	//"object"�̑S�I�u�W�F�N�g�𑖍�
	for (nlohmann::json& object : deserialize["objects"]) {
		assert(object.contains("type"));

		//��ʂ��擾
		std::string type = object["type"].get<std::string>();

		//��ނ��Ƃ̏���
		//���b�V��
		if (type.compare("MESH") == 0) {
			// �v�f�̒ǉ�
			levelData->objects.emplace_back(LevelData::ObjectData{});
			//���ǉ������v�f�̎Q�Ƃ𓾂�
			LevelData::ObjectData& objectData = levelData->objects.back();

			if (object.contains("file_name")) {
				objectData.fileName = object["file_name"];
			}

			//�g�����X�t�H�[���p�����[�^�̓ǂݍ���
 			nlohmann::json& transform = object["transform"];
			//���s�ړ�
			objectData.position.m128_f32[0] = (float)transform["translation"][1];
			objectData.position.m128_f32[1] = (float)transform["translation"][2];
			objectData.position.m128_f32[2] = -(float)transform["translation"][0];
			objectData.position.m128_f32[3] = 1.0f;
			//��]�p
			objectData.rotation.m128_f32[0] = -(float)transform["rotation"][1];
			objectData.rotation.m128_f32[1] = -(float)transform["rotation"][2];
			objectData.rotation.m128_f32[2] = (float)transform["rotation"][0];
			objectData.rotation.m128_f32[3] = 0.0f;
			//�X�P�[�����O
			objectData.scaling.m128_f32[0] = (float)transform["scaling"][1];
			objectData.scaling.m128_f32[1] = (float)transform["scaling"][2];
			objectData.scaling.m128_f32[2] = (float)transform["scaling"][0];
			objectData.scaling.m128_f32[3] = 0.0f;
			// TODO �R���C�_�[�̃p�����[�^�ǂ�
		}

		//�ċA�֐�
		if (type.compare("children") == 0) {

		}
	}
	return levelData;
}