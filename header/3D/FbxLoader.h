/**
 * @file FbxLoader.h
 * @brief FBX�̃��f����ǂݍ��ވׂ̋@�\
 * @author �~���^_�R�E�L
 * @date 2023/05/31
 */

#pragma once

#include "fbxsdk.h"

#include <d3d12.h>
#include <d3dx12.h>
#include<cassert>
#include <string>

#include "FbxModel.h"

class FbxLoader
{
private: //�G�C���A�X
	//std�ȗ�
	using string = std::string;
public: //�萔
	//���f���i�[�p�X
	static const string baseDirectory;
	static const string defaultTextureFileName;
public:
	static void ConvertMatrixFromFbx(DirectX::XMMATRIX* dst, const FbxAMatrix& src);
public:
	/// <summary>
	/// �V���O���g���C���X�^���X�̎擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static FbxLoader* GetInstance();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="device"></param>
	void Initialize(ID3D12Device* device);

	/// <summary>
	/// ��n��
	/// </summary>
	void Finalize();

	FbxModel* LoadModelFromFile(const string& modelName);

	/// <summary>
	/// �m�[�h�\�������
	/// </summary>
	/// <param name="model"></param>
	/// <param name="fbxNode"></param>
	void ParseNodeRecursive(FbxModel* model, FbxNode* fbxNode, Node* parent = nullptr);

	/// <summary>
	/// ���b�V���ǂݎ��
	/// </summary>
	/// <param name="model"></param>
	/// <param name="fbxNode"></param>
	void ParseMesh(FbxModel* model, FbxNode* fbxNode);
	//���_���W�ǂݎ��
	void ParseMeshVertices(FbxModel* model, FbxMesh* fbxMesh);
	//�ʏ��ǂݎ��
	void ParseMeshFaces(FbxModel* model, FbxMesh* fbxMesh);
	//�}�e���A���ǂݎ��
	void ParseMaterial(FbxModel* model, FbxNode* fbxNode);
	//�e�N�X�`���ǂݎ��
	void LoadTexture(FbxModel* model, const std::string& fullpath);
	//�X�L�j���O���̓ǂݎ��
	void ParseSkin(FbxModel* model, FbxMesh* fbxMesh);
private:
	// private�ȃR���X�g���N�^�i�V���O���g���p�^�[���j
	FbxLoader() = default;
	// private�ȃf�X�g���N�^�i�V���O���g���p�^�[���j
	~FbxLoader() = default;
	// �R�s�[�R���X�g���N�^���֎~�i�V���O���g���p�^�[���j
	FbxLoader(const FbxLoader& obj) = delete;
	// �R�s�[������Z�q���֎~�i�V���O���g���p�^�[���j
	void operator=(const FbxLoader& obj) = delete;

	//ID3D12�f�o�C�X
	ID3D12Device* device = nullptr;
	//FBX�}�l�[�W���[
	FbxManager* fbxManager = nullptr;
	//FBX�C���|�[�^�[
	FbxImporter* fbxImporter = nullptr;

	std::string ExtractFileName(const std::string& path);


};