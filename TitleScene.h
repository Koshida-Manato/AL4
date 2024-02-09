#pragma once
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Scene.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

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
};
