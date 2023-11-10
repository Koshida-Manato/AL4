#include "Player.h"
#include <cassert>
void Player::Initialize(Model* model, uint32_t textureHandle) { 
	assert(model);

	model_ = model;
	player_ = textureHandle;

	worldTransform_.Initialize();

	worldTransform_.scale_ = {2.0f, 2.0f, 2.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, -2.0f, 0.0f};

	// 行列の転送
	worldTransform_.TransferMatrix();
	worldTransform_.UpdateMatrix();
}

void Player::Update() {}

void Player::Draw(ViewProjection& viewProjection) {
	//3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, player_);
}
