#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() { delete model_; }

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("hasawei.png");
	//モデルの生成
	model_ = Model::Create();
	//scale
	woldTF_.scale_ = {5.0f, 5.0f, 5.0f};
	//回転角
	woldTF_.rotation_ = {XM_PI/4.0f, XM_PI / 4.0f, 0.0f};
	//worldtranceration
	woldTF_.translation_ = {10.0f, 10.0f, 10.0f};
	//ワールドの初期化
	woldTF_.Initialize();
	//ビューの初期化
	viewPJ_.Initialize();


}

void GameScene::Update() {

	//std::string strDebug = std::string("worldTF_.scale_ =:");
	debugText_->SetPos(50, 75);
	debugText_->Printf(
	  "trace:%f,%f,%f", woldTF_.translation_.x, woldTF_.translation_.y, woldTF_.translation_.z);
	debugText_->SetPos(50, 90);
	debugText_->Printf(
	  "trace:%f,%f,%f", woldTF_.rotation_.x, woldTF_.rotation_.y, woldTF_.rotation_.z);
	debugText_->SetPos(50, 105);
	debugText_->Printf("trace:%f,%f,%f", woldTF_.scale_.x, woldTF_.scale_.y, woldTF_.scale_.z);

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
	model_->Draw(woldTF_, viewPJ_, textureHandle_);
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
