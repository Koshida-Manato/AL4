#include "Player.h"
#include "MyMath.h"
#include <cassert>
void Player::Initialize(Model* model, uint32_t textureHandle) { 
	assert(model);

	model_ = model;
	player_ = textureHandle;

	worldTransform_.Initialize();

	worldTransform_.scale_ = {2.0f, 2.0f, 2.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, -5.0f, 0.0f};

	// 行列の転送
	worldTransform_.TransferMatrix();
	worldTransform_.UpdateMatrix();
}

void Player::Update() { 
	XINPUT_STATE joyState;
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		//速さ
		const float speed = 0.3f;

		//移動量
		Vector3 move = {
		    (float)joyState.Gamepad.sThumbLX / SHRT_MAX * speed, 0.0f,
		    (float)joyState.Gamepad.sThumbLY / SHRT_MAX * speed};

		//移動量に速さを反映
		move = VectorMultiply(speed,Normalize(move));
		 
		worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	}
	worldTransform_.UpdateMatrix();
}

void Player::Draw(ViewProjection& viewProjection) {
	//3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, player_);
}

const WorldTransform& Player::GetWorldTransform() { return worldTransform_; }