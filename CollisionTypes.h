#pragma once

enum CollisionShapeType
{
	SHAPE_UNKNOWN = -1,
	COLISIONSHAPE_SPHERE,	//球
	COLISIONSHAPE_PLANE,	//平面
	COLISIONSHAPE_RAY,		//レイ
	COLISIONSHAPE_OBB,		//四角形
};