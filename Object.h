#pragma once
#include "Model.h"
#include "MyMath.h"
class Object {
public:
	///< summary>
	/// 初期化
	///  </summary>
	void Initialize(Model* model);

	///< summary>
	/// 更新
	///</summary>
	void Update();

	///< summary>
	/// 描画
	///</summary>
	void Draw(ViewProjection& viewProjection);

	void OnCollision();

	Vector3 GetWorldPosition();

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;
	// モデル
	Model* modelObject_ = nullptr;
	// デスフラグ
	bool isDead_ = false;
};
