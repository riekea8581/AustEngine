#include "UIHelper.h"
#include "..\Sprite\Sprite.h"

void UIHelper::DrawHealthBar(Sprite * s, float xPos, float yPos, float xTrans, int count)
{
	for (int i = 0; i < count; i++)
	{
		s->SetPosition(xPos, yPos);
		s->Render();
		xPos += xTrans;
	}
}