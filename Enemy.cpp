#include "Enemy.h"

void Enemy::Initialize(Model*modelEnemy) {
	modelEnemy_ = modelEnemy;
	// 初期化
	worldTransform_.Initialize();
	// 場所の初期化
	worldTransform_.scale_ = {0.7f, 0.7f, 0.7f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, 0.0f, 30.0f};
}

void Enemy::Update() {

	worldTransform_.parent_ = &worldTransform_;
	// 行列の更新
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	// 3Dモデルを描画
	modelEnemy_->Draw(worldTransform_, viewProjection);
}
void Enemy::OnCollision() { isDead_ = true; }

Vector3 Enemy::GetCenterPosition() const {
	// ローカル座標のオフセット
	const Vector3 offset = {0.0f, 1.5f, 0.0f};
	// ワールド座標変換
	Vector3 worldPos = Transform(offset, worldTransform_.matWorld_);

	return worldPos;
}
