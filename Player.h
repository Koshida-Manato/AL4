#pragma once

#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Model.h"
#include "Input.h"

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

		const WorldTransform& GetWorldTransform();

	private:
	    // カメラのビュープロジェクション
	    const ViewProjection* viewProjection_ = nullptr;
		//ワールド変換データ
		WorldTransform worldTransform_;
		//モデル
		Model* model_ = nullptr;
		//テクスチャハンドル
		uint32_t player_ = 0u;

	    Input* input_ = nullptr;
};
