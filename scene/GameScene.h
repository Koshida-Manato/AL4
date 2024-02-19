﻿#pragma once

#include "Audio.h"
#include "CollisionManager.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "Enemy.h"
#include "Fade.h"
#include "FollowCamera.h"
#include "Ground.h"
#include "Input.h"
#include "Model.h"
#include "Object.h"
#include "Player.h"
#include "SafeDelete.h"
#include "Scene.h"
#include "Skydome.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
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

	bool IsSceneEnd() { return isSceneEnd; }

	Scene NextScene() { return Scene::CLEAR; }

	void Reset();

	void ChackAllCollisions();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	// プレイヤーテクスチャハンドル
	/*uint32_t Player_ = 0;*/
	// 3Dモデル
	/*Model* model_ = nullptr;*/
	std::unique_ptr<Model> model_ = nullptr;
	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	// ビュープロジェクション
	ViewProjection viewProjection_;
	// 天球テクスチャハンドル
	uint32_t Skydome_ = 0;
	// 天球3Dモデル
	/*Model* modelSkydome_ = nullptr;*/
	std::unique_ptr<Model> modelSkydome_ = nullptr;
	// 天球
	std::unique_ptr<Skydome> skydome_ = nullptr;

	// デバッグカメラ
	/*DebugCamera* debugCamera_ = nullptr;*/
	std::unique_ptr<DebugCamera> debugCamera_ = nullptr;

	// 地面テクスチャハンドル
	uint32_t Ground_ = 0;
	// 地面3Dモデル
	std::unique_ptr<Model> modelGround_ = nullptr;
	// 地面
	std::unique_ptr<Ground> ground_ = nullptr;
	uint32_t Object_ = 0;
	// オブジェクト3Dモデル
	std::unique_ptr<Model> modelObject_ = nullptr;
	// オブジェクト
	std::unique_ptr<Object> object_ = nullptr;

	// 自キャラテクスチャハンドル
	uint32_t Player_ = 0;
	// 自キャラ3Dモデル
	std::unique_ptr<Model> modelPlayer_ = nullptr;
	// 自キャラ
	std::unique_ptr<Player> player_ = nullptr;

	// 3Dモデル
	std::unique_ptr<Model> playerModel_;
	std::unique_ptr<Model> modelFighterBody_;
	std::unique_ptr<Model> modelFighterHead_;
	std::unique_ptr<Model> modelFighterL_arm_;
	std::unique_ptr<Model> modelFighterR_arm_;

	// 敵テクスチャハンドル
	uint32_t Enemy_ = 0;
	// 敵キャラクター3Dモデル
	std::unique_ptr<Model> modelEnemy_ = nullptr;
	// 敵キャラ
	std::unique_ptr<Enemy> enemy_ = nullptr;

	// 3Dモデル
	std::unique_ptr<Model> enemyModel_;

	// フェードイン・アウト
	/*Sprite* fadeSprite_ = nullptr;
	Vector4 fadeColor_ = {1.0f, 1.0f, 1.0f, 1.0f};*/
	std::unique_ptr<Fade> fade_ = nullptr;

	// フォローカメラ
	std::unique_ptr<FollowCamera> followCamera_ = nullptr;

	// シーンを終わらせるフラグ
	bool isSceneEnd = false;

	// フラグ
	bool fadeinFlag = false;
	bool fadeoutFlag = false;

	int fadeTimer = 0;
	bool finishFlag = false;

	// 衝突マネージャ
	std::unique_ptr<CollisionManager> collisionManager_;
};
