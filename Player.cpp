#include "Player.h"
#include "MyMath.h"
#include <cassert>
void Player::Initialize(
    Model* modelBody, Model* modelHead, Model* modelL_arm_, Model* modelR_arm_) { 

	modelFighterBody_ = modelBody;
	modelFighterHead_ = modelHead;
	modelFighterL_arm_ = modelL_arm_;
	modelFighterR_arm_ = modelR_arm_;

	// 初期化
	worldTransform_.Initialize();
	worldTransformBody_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformL_arm.Initialize();
	worldTransformR_arm.Initialize();
	// 初期化
	worldTransform_.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
	// 体の初期化
	worldTransformBody_.scale_ = {0.7f, 0.7f, 0.7f};
	worldTransformBody_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformBody_.translation_ = {0.0f, 0.0f, 0.0f};
	// 頭の初期化
	worldTransformHead_.scale_ = {0.7f, 0.7f, 0.7f};
	worldTransformHead_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformHead_.translation_ = {0.0f, 0.0f, 0.0f};
	// 左腕の初期化
	worldTransformL_arm.scale_ = {0.7f, 0.7f, 0.7f};
	worldTransformL_arm.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformL_arm.translation_ = {0.0f, 0.0f, 0.0f};
	// 右腕の初期化
	worldTransformR_arm.scale_ = {0.7f, 0.7f, 0.7f};
	worldTransformR_arm.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformR_arm.translation_ = {0.0f, 0.0f, 0.0f};

}

void Player::Update() {
	if (behaviorRequest_) {
		// 振る舞い変更
		behavior_ = behaviorRequest_.value();
		// 初期化実行
		switch (behavior_) {
		case Behavior::kRoot:
		default:
			BehaviorRootInitialize();
		case Behavior::kJump:
			BehaviorJumpInitialize();
			break;
		}
		// 振る舞いリクエストをリセット
		behaviorRequest_ = std::nullopt;
	}
	switch (behavior_) {
	case Behavior::kRoot:
	default:
		BehaviorRootUpdate();
		break;
	case Behavior::kJump:
		BehaviorJumpUpdate();
		break;
	}
	worldTransformBody_.parent_ = &worldTransform_;
	worldTransformHead_.parent_ = &worldTransform_;
	worldTransformL_arm.parent_ = &worldTransform_;
	worldTransformR_arm.parent_ = &worldTransform_;
	// 行列の更新
	worldTransform_.UpdateMatrix();
	worldTransformBody_.UpdateMatrix();
	worldTransformHead_.UpdateMatrix();
	worldTransformL_arm.UpdateMatrix();
	worldTransformR_arm.UpdateMatrix();
}

void Player::BehaviorRootUpdate() { 
	BehaviorRootInitialize();
	XINPUT_STATE joyState;
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		// 速さ
		const float speed = 0.3f;
		// 移動量
		velocity_= {
		    (float)joyState.Gamepad.sThumbLX / SHRT_MAX * speed, 0.0f,
		    (float)joyState.Gamepad.sThumbLY / SHRT_MAX * speed};
		// 移動量に速さを反映
		velocity_ = VectorMultiply(speed, Normalize(velocity_));
		velocity_ = TransformNormal(velocity_, MakeRotateYMatrix(viewProjection_->rotation_.y));
		// 移動
		worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

		// カメラの角度から回転行列を計算する
		/*Matrix4x4 rotateYMatrix = MakeRotateYMatrix(viewProjection_->rotation_.y);*/

		if (velocity_.z != 0 || velocity_.y != 0) {
			worldTransform_.rotation_.y = std::atan2(velocity_.x, velocity_.z);
		}
	};

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_B) {
			// ジャンプリクエスト
			behaviorRequest_ = Behavior::kJump;
			/*jump++;*/
			Sleep(1 * 300);
		}
	} 
	UpdateFloatingGimmick();
}

void Player::InitializeFloatingGimmick() { floatingParameter_ = 0.0f; }

void Player::UpdateFloatingGimmick() {
	// 浮遊移動のサイクル<frame>
	const float Period = 120.0f;
	// 1フレームでのパラメータ加算値
	const float Step = 2.0f * (float)M_PI / (float)Period;
	// パラメータを1ステップ分加算
	floatingParameter_ += Step;
	// 2πwを超えたら0に戻す
	floatingParameter_ = std::fmod(floatingParameter_, 2.0f * (float)M_PI);
	// 浮遊の振幅
	const float Amplitude = 0.3f;
	// 浮遊を座標に反映
	worldTransform_.translation_.y = std::sin(floatingParameter_) * Amplitude;
}

void Player::Draw(ViewProjection& viewProjection) {
	modelFighterBody_->Draw(worldTransformBody_, viewProjection);
	modelFighterHead_->Draw(worldTransformHead_, viewProjection);
	modelFighterL_arm_->Draw(worldTransformL_arm, viewProjection);
	modelFighterR_arm_->Draw(worldTransformR_arm, viewProjection);
}

void Player::Reset(){ 
	jump = 0;
	isDead_ = false;
	isJumpEnd = false;
	Initialize(modelFighterBody_, modelFighterHead_, modelFighterL_arm_, modelFighterR_arm_);
};

void Player::BehaviorJumpInitialize(){ 
	worldTransformBody_.translation_.y = 0; 
	worldTransformL_arm.rotation_.x = 0;
	worldTransformR_arm.rotation_.x = 0;
	//ジャンプ初速
	const float kJumpFirstSpeed = 1.0f;
	//ジャンプ初速を与える
	velocity_.y = kJumpFirstSpeed;
};
void Player::BehaviorRootInitialize(){};
void Player::BehaviorJumpUpdate(){
	//移動
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
	//重力加速度
	const float kGravityAcceleration = 0.05f;
	//加速度ベクトル
	Vector3 accelerationVector = {0, -kGravityAcceleration, 0};
	//加速する
	velocity_ = Add(accelerationVector,velocity_);
	//着地
	if (worldTransform_.translation_.y <= 0.0f) {
		worldTransform_.translation_.y = 0;
		//ジャンプ終了
		behaviorRequest_ = Behavior::kRoot;
	}
};
Vector3 Player::GetCenterPosition() const {
	// ローカル座標のオフセット
	const Vector3 offset = {0.0f, 1.5f, 0.0f};
	// ワールド座標変換
	Vector3 worldPos = Transform(offset, worldTransform_.matWorld_);

	return worldPos;
}

void Player::OnCollision() { isDead_ = true; }