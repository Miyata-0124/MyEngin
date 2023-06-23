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
		DirectX::XMVECTOR scal;
	};

	//�I�u�W�F�N�g�z��
	std::vector<ObjectData> objects;
};

class JsonLoader
{
public:
	void LoadFlomJSONInternal(const	std::string& modelname);
private:

};