#include "Ground.h"
#include <cassert>

void Ground::Initialize(Model* model, uint32_t Ground) {
	// NULLポインタチェック
	assert(model);
	model_ = model;
	Ground_ = Ground;
	// ワールド変換の初期化
	worldTransform_.Initialize();

	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, -1.0f, 0.0f};

	// 行列の転送
	worldTransform_.TransferMatrix();
	worldTransform_.UpdateMatrix();
}

void Ground::Update() {}

void Ground::Draw(ViewProjection& viewProjection_){
	// 3Dモデル描画
	model_->Draw(worldTransform_, viewProjection_);
};