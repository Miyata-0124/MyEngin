#pragma once
#include<Windows.h>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<cassert>
#include<DirectXMath.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include "DirectXTex/d3dx12.h"
#include <nlohmann/json.hpp>
#include "Model.h"
#include "Object3D.h"

//�f�[�^�i�[�p
struct LevelData
{
	struct ObjectData
	{
		// �t�@�C����
		std::string fileName;
		// ���s�ړ�
		DirectX::XMVECTOR position;
		// ��]�p
		DirectX::XMVECTOR rotation;
		// �X�P�[�����O
		DirectX::XMVECTOR scaling;
		//�R���C�_�[
		// �R���C�_�[��
		std::string collName;
		// ���S
		DirectX::XMVECTOR center;
		// �T�C�Y
		DirectX::XMVECTOR size;
	};

	//�I�u�W�F�N�g�z��
	std::vector<ObjectData> objects;
};

class JsonLoader
{
public:
	//json�ǂݍ���
	static LevelData* LoadFlomJSONInternal(const std::string& modelname);
private:

};

