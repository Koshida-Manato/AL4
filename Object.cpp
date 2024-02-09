#include "Object.h"
void Object::Initialize(Model* model) { 
	modelObject_ = model; 
	worldTransform_.Initialize();
	// 初期化
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, -2.0f, 60.0f};
}
void Object::Update() { worldTransform_.UpdateMatrix(); }
void Object::Draw(ViewProjection& viewProjection) {
	modelObject_->Draw(worldTransform_, viewProjection);
}
void Object::OnCollision() { isDead_ = true; };
Vector3 Object::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}
