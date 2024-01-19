#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "input.h"
#include "MyMath.h"
class FollowCamera {
public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary
	FollowCamera();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	void SetTarget(const WorldTransform* target) { target_ = target; }

	const ViewProjection& GetViewProjection() { return viewProjection_; };

private:
	//ビュープロジェクション
	ViewProjection viewProjection_;
	// ワールド変換データ
	WorldTransform worldTransform_;
	//追従対象
	const WorldTransform* target_ = nullptr;
};
