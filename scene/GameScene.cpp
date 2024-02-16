#include "GameScene.h"
#include "TextureManager.h"
#include "Player.h"
#include "Skydome.h"
#include "AxisIndicator.h"
#include "Ground.h"

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// プレイヤーテクスチャ読み込み
	Player_ = TextureManager::Load("./Resources/kasu.png");
	// 天球の読み込み
	Skydome_ = TextureManager::Load("./Resources/skydome/Back.png");
	// 地面の読み込み
	Ground_ = TextureManager::Load("./Resources/ground/ground.png");
	// 3Dモデルの生成
	model_.reset(Model::Create());
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
	// 自キャラの生成
	/*player_ = new Player();*/
	/*player_ = std::make_unique<Player>();*/
	// 自キャラの初期化
	/*player_->Initialize(model_.get(),Player_);*/

	// 天球の生成
	/*skydome_ = new Skydome();*/
	skydome_ = std::make_unique<Skydome>();
	// 天球3Dモデルの生成
	modelSkydome_.reset(Model::CreateFromOBJ("skydome", true));
	// 天球の初期化
	skydome_->Initialize(modelSkydome_.get(), Skydome_);

	// 追従カメラの生成
	followCamera_ = std::make_unique<FollowCamera>();
	//追従カメラの初期化
	followCamera_->Initialize();

	// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向が表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	// デバッグカメラの生成
	/*debugCamera_ = new DebugCamera(1280, 720);*/
	debugCamera_ = std::make_unique<DebugCamera>(1260, 720);

	// 地面の生成
	ground_ = std::make_unique<Ground>();
	// 地面3Dモデルの生成
	modelGround_.reset(Model::CreateFromOBJ("ground", true));
	// 地面の初期化
	ground_->Initialize(modelGround_.get(), Ground_);

	//オブジェクトの生成
	object_ = std::make_unique<Object>();
	//3Dモデルの生成
	modelObject_.reset(Model::CreateFromOBJ("object", true));
	//オブジェクトの初期化
	object_->Initialize(modelObject_.get());

	// 自キャラの生成
	player_ = std::make_unique<Player>();
	// 自キャラ3Dモデルの生成
	//modelPlayer_.reset(Model::CreateFromOBJ("bottlePlayer", true));
	modelFighterBody_.reset(Model::CreateFromOBJ("float_Body", true));
	modelFighterHead_.reset(Model::CreateFromOBJ("float_Head", true));
	modelFighterL_arm_.reset(Model::CreateFromOBJ("float_L_arm", true));
	modelFighterR_arm_.reset(Model::CreateFromOBJ("float_R_arm", true));
	// 自キャラのワールドトランスフォームを追従カメラにセット
	followCamera_->SetTarget(&player_->GetWorldTransform());
	player_->SetViewProjection(&followCamera_->GetViewProjection());
	// 自キャラの初期化
	player_->Initialize(
	    modelFighterBody_.get(), modelFighterHead_.get(), modelFighterL_arm_.get(),
	    modelFighterR_arm_.get());

	fade_ = std::make_unique<Fade>();
	fade_->Initialize();
}

void GameScene::Update() {
	//更新処理
	fade_->Update();
	if (fadeinFlag == false) {
		fade_->FadeInStart();
		fadeinFlag = true;
	}
	if (finishFlag == true) {
		if (fadeoutFlag == false) {
			fade_->FadeOutStart();
			fadeoutFlag = true;
		}
		fadeTimer++;
	}
	if (fadeTimer >= 100) {
			isSceneEnd = true;
			fadeinFlag = false;
	}
	// 自キャラの更新
	player_->Update();
	//デバッグカメラの更新
	debugCamera_->Update();
	//追従カメラの更新
	followCamera_->Update();
	//スカイドームの更新
	skydome_->Update();
	//オブジェクトの更新
	object_->Update();

	viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;
	viewProjection_.matView = followCamera_->GetViewProjection().matView;

	viewProjection_.TransferMatrix();

	if (player_->IsJumpEnd() == true) {
		finishFlag = true;
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	//デバッグカメラ
	/*model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), Player_);*/

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	//3Dモデル描画
	/*model_->Draw(worldTransform_, viewProjection_, Player_);*/

	// 自キャラの描画
	player_->Draw(viewProjection_);
	//天球の描画
	skydome_->Draw(viewProjection_);
	//地面の描画
	ground_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// フェード
	fade_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
void GameScene::Reset() {
	player_->Reset();
	isSceneEnd = false;
	fadeinFlag = false;
	fadeoutFlag = false;
}