#pragma once

#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include<Input.h>

//振る舞い
enum class Behavior {
	kRoot, //通常状態
	kJump, //ジャンプ中
};

/// <summary>
/// 自キャラ
/// </summary>
class Player {
	public:
		/// <summary>
		/// 自キャラ
		/// </summary>
		void Initialize(Model* modelBody,Model*modelHead,Model*modelL_arm_,Model*modelR_arm);

		/// <summary>
		/// 自キャラ
		/// </summary>
		void Update();

		/// <summary>
		/// 自キャラ
		/// </summary>
		void Draw(ViewProjection& viewProjection);

		const WorldTransform& GetWorldTransform(){ 
			return worldTransform_;
		};

		void SetViewProjection(const ViewProjection* viewProjection) {
		    viewProjection_ = viewProjection;
	    }

		//浮遊ギミック初期化
	    void InitializeFloatingGimmick();

		//浮遊ギミック更新
	    void UpdateFloatingGimmick();

		//ジャンプ行動初期化
	    void BehaviorJumpInitialize();

		//ジャンプ行動更新
	    void BehaviorJumpUpdate();

	private:
		//ワールド変換データ
	    WorldTransform worldTransform_;
	    WorldTransform worldTransformBody_;
	    WorldTransform worldTransformHead_;
	    WorldTransform worldTransformL_arm;
	    WorldTransform worldTransformR_arm;
	    // カメラのビュープロジェクション
	    const ViewProjection* viewProjection_ = nullptr;
		//モデル
		Model* model_ = nullptr;
		//テクスチャハンドル
		/*uint32_t player_ = 0u;*/

		//3Dモデル
	    Model* modelFighterBody_;
	    Model* modelFighterHead_;
	    Model* modelFighterL_arm_;
	    Model* modelFighterR_arm_;

	    Input* input_ = nullptr;

		//浮遊ギミックの媒介変数
	    float floatingParameter_ = 0.0f;
};
