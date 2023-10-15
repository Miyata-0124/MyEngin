/**
 * @file CollisionTypes.h
 * @brief 各オブジェクトが持っているコライダーの判別をするためのタイプ
 * @author ミヤタ_コウキ
 * @date 2023_07_25
 */

#pragma once

enum CollisionShapeType
{
	SHAPE_UNKNOWN = -1,
	COLISIONSHAPE_SPHERE,	//球
	COLISIONSHAPE_PLANE,	//平面
	COLISIONSHAPE_RAY,		//レイ
	COLISIONSHAPE_OBB,		//四角形
	COLISIONSHAPE_BOX,		//2D四角形
};