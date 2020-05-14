#include "SpriteFont.h"
#include "Sprite.h"
#include "RapidXML/rapidxml_utils.hpp"
#include "../Resource Managers/TextureManager.h"
#include "../Resource Managers/ImageManager.h"

SpriteFont::SpriteFont(std::string texPath, std::string xmlPath)
{
	FontTexture = TextureManager::Get(texPath.c_str());
	XMLtoCollection(xmlPath);
}

void SpriteFont::XMLtoCollection(std::string path)
{
	rapidxml::file<char> FontData(path.c_str());

	using namespace rapidxml;
	xml_document<> doc;
	doc.parse<0>(FontData.data());

	xml_node<>* node = doc.first_node();
	while (node != nullptr)
	{
		if (strcmp(node->name(), "fontMetrics") == 0)
		{
			DebugMsg::out("SpriteFont: font data start for %s\n",
				node->first_attribute()->value());
			node = node->first_node();
		}
		else if (strcmp(node->name(), "character") == 0)
		{
			DebugMsg::out("SpriteFont: char data found\n");
			CreateGlyph(node);
			node = node->next_sibling();
		}
	}
}

void SpriteFont::CreateGlyph(rapidxml::xml_node<char>* node)
{
	rapidxml::xml_node<char>* keynode = node;
	Key key = atoi(keynode->first_attribute()->value());

	keynode = keynode->first_node();
	float x = (float)atoi(keynode->value());
	keynode = keynode->next_sibling();
	float y = (float)atoi(keynode->value());
	keynode = keynode->next_sibling();
	float w = (float)atoi(keynode->value());
	keynode = keynode->next_sibling();
	float h = (float)atoi(keynode->value());

	ImageManager::Load((std::to_string(key)).c_str(),
		FontTexture, new Rect(x, y, w, h));
	fontmap[key] = new Glyph((std::to_string(key)).c_str());
}

SpriteFont::~SpriteFont()
{
	for (FontMap::iterator it = fontmap.begin(); it != fontmap.end(); it++)
	{
		delete (*it).second;
	}
}