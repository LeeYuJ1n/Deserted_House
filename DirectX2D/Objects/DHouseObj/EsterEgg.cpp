#include "Framework.h"

EsterEgg::EsterEgg()
{
	// image = new Quad(L"Textures/DHouseTexure/Artist.png");
	// image->Pos() = { CENTER_X, CENTER_Y };
	// image->UpdateWorld();

	image2 = new Quad(L"Textures/DHouseTexure/Artist2.png");
	image2->Pos() = { CENTER_X, CENTER_Y };
	image2->UpdateWorld();
}

EsterEgg::~EsterEgg()
{
	// delete image;
	delete image2;
}

void EsterEgg::Update()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		Audio::Get()->Stop("LostArk");
		Audio::Get()->Play("FirstBGM");

		SceneManager::Get()->ChangeScene("Dhouse");

		//if (!active) //음악반전
		//추가 힌트 : 음악을 부르거나 할 때는 이전 음악을 적절히 수동으로 멈춰주는 것도 필요합니다
		//더 좋은 건 오디오를 스스로 개조해서 "NewPlay" - 기존 곡을 멈추고 새곡 시작 같은 걸 만드는 것도....
	}
}

void EsterEgg::Render()
{
	image2->Render();
}


