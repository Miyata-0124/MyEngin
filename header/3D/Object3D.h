/**
 * @file Object3D.h
 * @brief OBJ���f�����Q�[�����ň����ׂ̋@�\
 * @author �~���^_�R�E�L
 * @date 2022/07/20
 */

#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include "DirectXTex/include/d3dx12.h"
#include "Model.h"
#include "header/Collider/CollisionInfo.h"
#include "header/Engin/ViewProjection.h"

class BaseCollider;

enum Identification //����
{
	IDENT_UNKNOWN = -1,
	IDENT_PLAYER,		//�v���C���[
	IDENT_NEUTRAL,		//����
	IDENT_ENEMY,		//�G��
	IDENT_FREND,		//�F�D
	IDENT_ITEM,			//�A�C�e��
	IDENT_GOAL,			//�S�[��
	IDENT_GATE,			//�C�x���g
	IDENT_WALL,			//��
	IDENT_FLOOR,		//��
	IDENT_PIPE,			//�p�C�v(�o���)
};

/// <summary>
/// 3D�I�u�W�F�N�g
/// </summary>
class Object3d
{
protected: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // �T�u�N���X
	// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferDataB0
	{
		//XMFLOAT4 color;	// �F (RGBA)
		XMMATRIX mat;	// �R�c�ϊ��s��
	};

private: // �萔
	static const int division = 50;	// ������
	static const float prizmHeight;	// ���̍���
	static const int planeCount = division * 2 + division * 2; // �ʂ̐�
	static const int vertexCount = planeCount * 3; // ���_��

public: // �ÓI�����o�֐�
	/// <summary>
	/// �ÓI������
	/// </summary>
	/// <param name="device">�f�o�C�X</param>
	/// <param name="window_width">��ʕ�</param>
	/// <param name="window_height">��ʍ���</param>
	static void StaticInitialize(ID3D12Device* device, ViewProjection* camera_);

	/// <summary>
	/// �`��O����
	/// </summary>
	/// <param name="cmdList">�`��R�}���h���X�g</param>
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// �`��㏈��
	/// </summary>
	static void PostDraw();

	/// <summary>
	/// 3D�I�u�W�F�N�g����
	/// </summary>
	/// <returns></returns>
	static Object3d* Create();

	/// <summary>
	/// ���_���W�̎擾
	/// </summary>
	/// <returns>���W</returns>
	static const XMFLOAT3& GetEye() { return eye; }

	/// <summary>
	/// ���_���W�̐ݒ�
	/// </summary>
	/// <param name="position">���W</param>
	static void SetEye(XMFLOAT3 eye);

	/// <summary>
	/// �����_���W�̎擾
	/// </summary>
	/// <returns>���W</returns>
	static const XMFLOAT3& GetTarget() { return target; }

	/// <summary>
	/// �����_���W�̐ݒ�
	/// </summary>
	/// <param name="position">���W</param>
	static void SetTarget(XMFLOAT3 target);

	/// <summary>
	/// �x�N�g���ɂ��ړ�
	/// </summary>
	/// <param name="move">�ړ���</param>
	static void CameraMoveVector(XMFLOAT3 move);

private: // �ÓI�����o�ϐ�
	// �f�o�C�X
	static ID3D12Device* device;
	// �R�}���h���X�g
	static ID3D12GraphicsCommandList* cmdList;
	// ���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootsignature;
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState> pipelinestate;
	// �r���[�s��
	static XMMATRIX matView;
	// �ˉe�s��
	static XMMATRIX matProjection;
	// ���_���W
	static XMFLOAT3 eye;
	// �����_���W
	static XMFLOAT3 target;
	// ������x�N�g��
	static XMFLOAT3 up;

	//�J����
	static ViewProjection* camera;
private:// �ÓI�����o�֐�
	/// <summary>
	/// �J����������
	/// </summary>
	/// <param name="window_width">��ʉ���</param>
	/// <param name="window_height">��ʏc��</param>
	static void InitializeCamera(ViewProjection* camera_);

	/// <summary>
	/// �O���t�B�b�N�p�C�v���C������
	/// </summary>
	/// <returns>����</returns>
	static void InitializeGraphicsPipeline();

	/// <summary>
	/// �r���[�s����X�V
	/// </summary>
	static void UpdateViewMatrix();

public: // �����o�֐�

	Object3d() = default;

	virtual ~Object3d();

	virtual bool Initialize();
	/// <summary>
	/// ���t���[������
	/// </summary>
	virtual void Update();

	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw();

	#pragma warning(suppress: 4100)
	virtual void OnCollider(const CollisionInfo& info) {};

	/// <summary>
	/// ���W�̎擾
	/// </summary>
	/// <returns>���W</returns>
	const XMFLOAT3& GetPosition() const { return position; }

	/// <summary>
	/// �T�C�Y�̎擾
	/// </summary>
	/// <returns></returns>
	const XMFLOAT3& GetScale()const { return scale; }

	/// <summary>
	/// ��]�̎擾
	/// </summary>
	/// <returns></returns>
	const XMFLOAT3& GetRotation()const { return rotation; }

	const XMFLOAT2& GetRadius()const { return radius; }
	//�Z�b�^�[
	/// <summary>
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="position">���W</param>
	void SetPosition(const XMFLOAT3& position_) { this->position = position_; }
	/// <summary>
	/// �I�u�W�F�N�g�T�C�Y�̐ݒ�
	/// </summary>
	/// <param name="size"></param>
	void SetScale(const XMFLOAT3& scale_) { this->scale = scale_; }
	/// <summary>
	/// ��]�p�̐ݒ�
	/// </summary>
	/// <param name="rotation"></param>
	void SetRotation(const XMFLOAT3& rotation_) { this->rotation = rotation_; }
	/// <summary>
	/// ���a�̐ݒ�
	/// </summary>
	/// <param name="radius_"></param>
	void SetRadius(const XMFLOAT2& radius_) { this->radius = radius_; }
	/// <summary>
	/// ���f���Z�b�g
	/// </summary>
	/// <param name="model_"></param>
	void SetModel(Model* model_) { model = model_; }
	/// <summary>
	/// ���[���h�s��̎擾
	/// </summary>
	/// <returns></returns>
	const XMMATRIX& GetMatWorld() { return matWorld; }
	/// <summary>
	/// �R���C�_�[�̃Z�b�g
	/// </summary>
	/// <param name="collider"></param>
	void SetCollider(BaseCollider* collider);
	/// <summary>
	/// ���ʃR�[�h
	/// </summary>
	/// <param name="ident_"></param>
	void SetIdentification(Identification ident_);
	const Identification& GetIdentification() { return ident; }
protected: // �����o�ϐ�
	//ComPtr<ID3D12Resource> constBuff; // �萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuffB0; // �萔�o�b�t�@
	//ComPtr<ID3D12Resource> constBuffB1; // �萔�o�b�t�@
	// �F
	XMFLOAT4 color = { 1,1,1,1 };
	// ���[�J���X�P�[��
	XMFLOAT3 scale = { 1,1,1 };
	// X,Y,Z�����̃��[�J����]�p
	XMFLOAT3 rotation = { 0,0,0 };
	// ���[�J�����W
	XMFLOAT3 position = { 0,0,0 };
	//���a
	XMFLOAT2 radius = { 0,0 };	//
	// ���[�J�����[���h�ϊ��s��
	XMMATRIX matWorld;
	XMMATRIX matScale, matRot, matTrans;
	// �e�I�u�W�F�N�g
	Object3d* parent = nullptr;
	//���f��
	Model* model = nullptr;

	const char* name = nullptr;
	BaseCollider* collider = nullptr;

	//���ꂼ�ꂪ�����ʃR�[�h
	Identification ident = IDENT_UNKNOWN;
};