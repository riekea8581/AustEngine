#pragma once

#include <map>
#include "AzulCore.h"
#include "RapidXML/rapidxml.hpp"

class Sprite;

class SpriteFont
{
public:
	typedef int Key;
	typedef Sprite Glyph;

private:
	Texture* FontTexture;
	typedef std::map<Key, Glyph *> FontMap;
	FontMap fontmap;

	void XMLtoCollection(std::string path);
	void CreateGlyph(rapidxml::xml_node<char>* node);

public:
	SpriteFont() = delete;
	SpriteFont(const SpriteFont&) = default;
	SpriteFont& operator=(const SpriteFont&) = delete;
	virtual ~SpriteFont(); 
	
	SpriteFont(std::string texPath, std::string xmlPath);
	Glyph * GetGlyph(char c) { return fontmap[c]; };
};