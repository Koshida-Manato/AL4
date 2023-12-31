﻿#include "Player.h"
#include <cassert>
void Player::Initialize(Model* model, uint32_t textureHandle) { 
	assert(model);

	model_ = model;
	player_ = textureHandle;

	worldTransform_.Initialize();
}

void Player::Update() {}

void Player::Draw(ViewProjection& viewProjection) {
	//3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, player_);
}
