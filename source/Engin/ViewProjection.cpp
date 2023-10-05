#include "header/Engin/ViewProjection.h"
#include "header/Engin/WinApp.h"

void ViewProjection::Initialeze() {
	eye = { 0, 0, -50.0f };
	target = { 0, 0, 0 };
	up = { 0, 1, 0 };

	UpdateView();
	UpdateProjection();
}

void ViewProjection::Update() {
	UpdateView();
}

void ViewProjection::UpdateView() {
	// ビュー行列の生成
	matView = XMMatrixLookAtLH(
		XMLoadFloat3(&eye),
		XMLoadFloat3(&target),
		XMLoadFloat3(&up));
}

void ViewProjection::UpdateProjection() {
	// 透視投影による射影行列の生成
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)WinApp::window_width / WinApp::window_height,
		0.1f, 1000.0f);
}