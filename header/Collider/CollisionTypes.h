/**
 * @file CollisionTypes.h
 * @brief �e�I�u�W�F�N�g�������Ă���R���C�_�[�̔��ʂ����邽�߂̃^�C�v
 * @author �~���^_�R�E�L
 * @date 2023_07_25
 */

#pragma once

enum CollisionShapeType
{
	SHAPE_UNKNOWN = -1,
	COLISIONSHAPE_SPHERE,	//��
	COLISIONSHAPE_PLANE,	//����
	COLISIONSHAPE_RAY,		//���C
	COLISIONSHAPE_OBB,		//�l�p�`
	COLISIONSHAPE_BOX,		//2D�l�p�`
};