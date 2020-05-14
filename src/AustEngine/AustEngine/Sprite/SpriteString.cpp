#include "SpriteString.h"
#include "Sprite.h"
#include "SpriteFont.h"

SpriteString::SpriteString(const SpriteFont& sf)
{
	sfont = new SpriteFont(sf);
}

SpriteString::SpriteString(SpriteFont * sf, std::string s, int x, int y)
{
	sfont = sf;
	int strIndex;
	posX = x;
	posY = y;

	for (std::string::iterator it = s.begin(); it != s.end(); ++it)
	{
		glyphs[strIndex] = sfont->GetGlyph(*it);
		strIndex++;
	}
}

void SpriteString::Set(int x, int y)
{
	posX = x;
	posY = y;
}

void SpriteString::Set(SpriteFont * sf, std::string s, int x, int y)
{
	sfont = sf;
	int strIndex;
	posX = x;
	posY = y;

	for (std::string::iterator it = s.begin(); it != s.end(); ++it)
	{
		glyphs[strIndex] = sfont->GetGlyph(*it);
		strIndex++;
	}
}

void SpriteString::Render()
{
	float offset = 0;
	for (GlyphCollection::iterator it = glyphs.begin(); it != glyphs.end(); ++it)
	{
		(*it).second->SetPosition((float) posX + offset, (float) posY);
		(*it).second->Render();
		offset += (*it).second->GetWidth();
	}
}