#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "Skydome.h"
#include <memory>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	
	//プレイヤーテクスチャハンドル
	uint32_t Player_ = 0;
	//3Dモデル
	/*Model* model_ = nullptr;*/
	std::unique_ptr<Model> model_ = nullptr;
	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//ビュープロジェクション
	ViewProjection viewProjection_;
	// 自キャラ
	/*Player* player_ = nullptr;*/
	std::unique_ptr<Player> player_ = nullptr;

	//天球テクスチャハンドル
	uint32_t Skydome_ = 0;
	//天球3Dモデル
	/*Model* modelSkydome_ = nullptr;*/
	std::unique_ptr<Model> modelSkydome_ = nullptr;
	//天球
	std::unique_ptr<Skydome> skydome_ = nullptr;
};
