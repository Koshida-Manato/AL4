#pragma once

#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Model.h"

/// <summary>
/// 自キャラ
/// </summary>
class Player {
	public:
		/// <summary>
		/// 自キャラ
		/// </summary>
		void Initialize(Model* model, uint32_t textureHandle);

		/// <summary>
		/// 自キャラ
		/// </summary>
		void Update();

		/// <summary>
		/// 自キャラ
		/// </summary>
		void Draw(ViewProjection& viewProjection);

	private:
		//ワールド変換データ
		WorldTransform worldTransform_;
		//モデル
		Model* model_ = nullptr;
		//テクスチャハンドル
		uint32_t player_ = 0u;
};
