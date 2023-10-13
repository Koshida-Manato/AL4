#pragma once
#include "Input.h"
#include "Model.h"
#include "MyMath.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <assert.h>
class Skydome {
public:
	void Initialize(Model* model, uint32_t Skydome);

	void Update();

	void Draw(ViewProjection& viewProjection_);

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t Skydome_ = 0u;
};