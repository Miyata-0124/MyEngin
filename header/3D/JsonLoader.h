/**
 * @file JsonLoader.h
 * @brief Json�t�@�C����ǂݍ��ݗ��p�ł���@�\
 * @author �~���^_�R�E�L
 * @date 2023/07/14
 */

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
#include "DirectXTex/include/d3dx12.h"
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
		//���S
		DirectX::XMVECTOR center;
		//�T�C�Y
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

