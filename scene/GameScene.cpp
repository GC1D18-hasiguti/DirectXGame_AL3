#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <random>

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() { delete model_; }

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	//乱数生成
	std::random_device seed_gen;
	//めるせんぬ／ツイスター
	std::mt19937_64 engine(seed_gen());
	//乱数範囲(回転角)
	std::uniform_real_distribution<float> rotDist(0.0f, XM_2PI);
	//乱数範囲(座標)
	std::uniform_real_distribution<float> posDist(-10.0f, 10.0f);
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("hasawei.png");
	//モデルの生成
	model_ = Model::Create();
	for (size_t i = 0; i < _countof(woldTF_); i++) {

		// scale
		woldTF_[i].scale_ = {1.0f, 1.0f, 1.0f};
		//回転角
		woldTF_[i].rotation_ = {rotDist(engine),rotDist(engine),rotDist(engine)};
		// worldtranceration
		woldTF_[i].translation_ = {posDist(engine), posDist(engine), posDist(engine)};
		//ワールドの初期化
		woldTF_[i].Initialize();
	}
	//ビューの初期化
	viewPJ_.Initialize();
	

}

void GameScene::Update() {

	for (size_t i = 0; i < _countof(woldTF_); i++) {

		// std::string strDebug = std::string("worldTF_.scale_ =:");
		/* debugText_->SetPos(50, 75);
		debugText_->Printf(
		  "trace:%f,%f,%f", woldTF_[i].translation_.x, woldTF_[i].translation_.y,
		  woldTF_[i].translation_.z);
		debugText_->SetPos(50, 90);
		debugText_->Printf(
		  "trace:%f,%f,%f", woldTF_[i].rotation_.x, woldTF_[i].rotation_.y, woldTF_[i].rotation_.z);
		debugText_->SetPos(50, 105);
		debugText_->Printf(
		  "trace:%f,%f,%f", woldTF_[i].scale_.x, woldTF_[i].scale_.y, woldTF_[i].scale_.z);
		  */
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

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

	//描画
	for (size_t i = 0; i < _countof(woldTF_); i++) {
		model_->Draw(woldTF_[i], viewPJ_, textureHandle_);
	}
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
