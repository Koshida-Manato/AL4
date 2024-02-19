#pragma once
#include "Input.h"
#include "Model.h"
#include "MyMath.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <assert.h>

/// <summary>
/// 地面
/// </summary>
class Ground {
public:
	void Initialize(Model* model, uint32_t Ground);

	void Update();

	void Draw(ViewProjection& viewProjection_);

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t Ground_ = 0u;
};
