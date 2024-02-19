﻿#include "FollowCamera.h"

FollowCamera::FollowCamera() {}

void FollowCamera::Initialize() { 
	worldTransform_.Initialize();
	viewProjection_.Initialize();
	input_ = Input::GetInstance();
}

void FollowCamera::Update() {
	//追従対象がいれば
	if (target_) {
		//追従対象からカメラまでのオフセット
		Vector3 offset = {0.0f, 2.0f, -15.0f};
		offset = TransformNormal(offset, MakeRotateYMatrix(viewProjection_.rotation_.y));
		//座標をコピーしてオフセット分ずらす
		viewProjection_.translation_ = Add(target_->translation_, offset);
	}
	//ビュー行列の更新
	XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		// 速さ
		const float rotate = 0.02f;
		viewProjection_.rotation_.y += joyState.Gamepad.sThumbRX / SHRT_MAX * rotate;
	}

	// 行列の更新
	viewProjection_.UpdateMatrix();
}
