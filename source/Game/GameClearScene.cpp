#include "header/Game/GameClearScene.h"
#include "header/Game/GameSceneManager.h"

#include "header/Game/Player.h"
#include "header/Game/Gate.h"
#include "header/Game/ClearBox.h"
#include "header/Game/Wall.h"
#include "header/Game/MoveGate.h"

#include "header/Game/Rain.h"

#include "easing/Easing.h"

#include "header/Game/GameTitleScene.h"

void GameClearScene::Initialize(ViewProjection* camera_, Input* input_)
{
	camera = camera_;
	input = input_;

	//�X�v���C�g���ʕ����̏�����
	spriteCommon->Initialize(directXCom);
	spriteCommon->Loadtexture(1, "GameClear.png");
	spriteCommon->Loadtexture(2, "white1x1.png");

	//�N���A
	clearSprite->Initialize(spriteCommon);
	//�Ó]
	blackOut->Initialize(spriteCommon);

	//��x�����錾���Ȃ�
	Object3d::StaticInitialize(directXCom->GetDevice(), camera);

	//json�ǂݍ���
	jsonLoader = JsonLoader::LoadFlomJSONInternal("sherter");

	//�v���C���[���f��
	Model* playerModel = Model::LoadFromOBJ("player");
	//�n�ʉ����f��
	//Model* item_ = Model::LoadFromOBJ("Item");

	//�v���C���[
	objPlayer = Player::Create(playerModel);
	objPlayer->SetInput(input);

#pragma region �p�[�e�B�N���֌W
	rain = Rain::Create();
#pragma	endregion

	//�}�b�v�ǂݍ���
	LoadMap();
}

void GameClearScene::Finalize()
{
	delete rain;
	delete blackOut;
	delete clearSprite;
	delete objPlayer;
	for (auto object : objects) {
		delete object;
	}
}

void GameClearScene::Update()
{
#pragma region �p�[�e�B�N��
	rain->Update();
#pragma endregion
	//�v���C���[
	if (!objClearBox->GetIsGoal())
	{
		objPlayer->Update();
	}
	
	for (auto object : objects) {
		object->Update();
	}
	if (objGate->GetRotation().x >= 90.0f)
	{
		blackOut->Update();
	}

	if (blackOut->GetMinAlpha() > blackOut->GetMaxAlpha())
	{
		clearSprite->Update();
	}
	//����}�l�[�W���[
	collisionManager->CheckAllCollisions();

	//�e�N���X�ɏ���n��
	objGate->SetIsGoal(objClearBox->GetIsGoal());

	if (input->TriggerKey(DIK_R))
	{
		GameBaseScene* scene = new GameTitleScene();
		sceneManager->SetNextScene(scene);
	}

}

void GameClearScene::Draw()
{
	Particle::PreDraw(directXCom->GetCommandList());
	rain->Draw();
	Particle::PostDraw();

	Object3d::PreDraw(directXCom->GetCommandList());
	//�v���C���[
	objPlayer->Draw();
	for (auto object : objects) {
		object->Draw();
	}
	objClearBox->Draw();


	Object3d::PostDraw();

	blackOut->Draw();
	clearSprite->Draw();
}

void GameClearScene::LoadMap()
{
	for (auto& objectData : jsonLoader->objects) {
		//�n�ʂɐڂ��Ă���ǃI�u�W�F�N�g
		Model* model = Model::LoadFromOBJ("wall");
		//���̃X�e�[�W�ֈړ����邽�߂̃I�u�W�F�N�g
		//Model* backGround = Model::LoadFromOBJ("BG");
		//��
		Model* gate = Model::LoadFromOBJ("gate");

		Model* clear = Model::LoadFromOBJ("clear");

		decltype(models)::iterator it = models.find(objectData.fileName);
		if (objectData.fileName == "floor")
		{
			if (it != models.end()) { model = it->second; }
			//���f�����w�肵��3D�I�u�W�F�N�g�𐶐�
			objWall = Wall::Create(model);
			//���W
			DirectX::XMFLOAT3 scale;
			DirectX::XMStoreFloat3(&scale, objectData.scaling);
			objWall->SetScale(scale);

			//��]�p
			DirectX::XMFLOAT3 rot;
			DirectX::XMStoreFloat3(&rot, objectData.rotation);
			objWall->SetRotation(rot);

			//���W
			DirectX::XMFLOAT3 pos;
			DirectX::XMStoreFloat3(&pos, objectData.position);
			objWall->SetPosition(pos);

			//�R���C�_�[
			/*DirectX::XMFLOAT3 center;
			DirectX::XMFLOAT2 radius;
			DirectX::XMStoreFloat3(&center, objectData.center);
			DirectX::XMStoreFloat2(&radius, objectData.size);*/

			//�z��ɓo�^
			objects.push_back(objWall);
		}

		if (objectData.fileName == "Gate")
		{
			if (it != models.end()) { gate = it->second; }
			//���f�����w�肵��3D�I�u�W�F�N�g�𐶐�
			objGate = Gate::Create(gate);
			//���W
			DirectX::XMFLOAT3 scale;
			DirectX::XMStoreFloat3(&scale, objectData.scaling);
			objGate->SetScale(scale);

			//��]�p
			DirectX::XMFLOAT3 rot;
			DirectX::XMStoreFloat3(&rot, objectData.rotation);
			objGate->SetRotation(rot);

			//���W
			DirectX::XMFLOAT3 pos;
			DirectX::XMStoreFloat3(&pos, objectData.position);
			objGate->SetPosition(pos);

			//�R���C�_�[
			/*DirectX::XMFLOAT3 center;
			DirectX::XMFLOAT2 radius;
			DirectX::XMStoreFloat3(&center, objectData.center);
			DirectX::XMStoreFloat2(&radius, objectData.size);*/

			//�z��ɓo�^
			objects.push_back(objGate);
		}

		if (objectData.fileName == "MoveGate")
		{
			if (it != models.end()) { clear = it->second; }
			//�ړ��p�Q�[�g
			objClearBox = ClearBox::Create(clear);
			//���W
			DirectX::XMFLOAT3 scale;
			DirectX::XMStoreFloat3(&scale, objectData.scaling);
			objClearBox->SetScale(scale);

			//��]�p
			DirectX::XMFLOAT3 rot;
			DirectX::XMStoreFloat3(&rot, objectData.rotation);
			objClearBox->SetRotation(rot);

			//���W
			DirectX::XMFLOAT3 pos;
			DirectX::XMStoreFloat3(&pos, objectData.position);
			objClearBox->SetPosition(pos);

			//�z��ɓo�^
			objects.push_back(objClearBox);
		}
	}
}
