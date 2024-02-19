#pragma once
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Scene.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "FollowCamera.h"
#include "Ground.h"
#include "Skydome.h"


class TitleScene {
public:

	~TitleScene();
	void Initialize();

	void Updata();

	void Draw();

	bool IsSceneEnd() { return isSceneEnd; }

	Scene NextScene() { return Scene::GAME; }

	void Reset();

private:
	bool isSceneEnd = false;
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;

	// シーンを終わらせるフラグ
	uint32_t titleTexture_ = 0;
	Sprite* sprite_ = nullptr;


	///背景描画
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
	// 地面テクスチャハンドル
	uint32_t Ground_ = 0;
	// 地面3Dモデル
	std::unique_ptr<Model> modelGround_ = nullptr;
	// 地面
	std::unique_ptr<Ground> ground_ = nullptr;
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
	std::unique_ptr<FollowCamera> followCamera_ = nullptr;
};
