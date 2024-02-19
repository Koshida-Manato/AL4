#include "MyMath.h"
#include "Model.h"
#include "WorldTransform.h"
#include "BaseCharacter.h"

class Enemy : public BaseCharacter {
public:
	// デストラクタ

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model*mdelEnemy);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(const ViewProjection& viewProjection);

	void OnCollision();

	// 中心座標を取得
	Vector3 GetCenterPosition() const override;

private:
	// WorldTransform worldTransform_;
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	// 3Dモデル
	Model* modelEnemy_;

	bool isDead_ = false;
};