#include "metatexture.h"
#include "binpack.h"
#include "../io/logger.h"

MetaTexture::MetaTexture() {}

MetaTexture::MetaTexture(std::vector<sf::Texture>& textures)
{
	create(textures);
}

void MetaTexture::create(std::vector<sf::Texture>& textures)
{
	frames.resize(textures.size());
	for (unsigned int i = 0; i < textures.size(); ++i)
	{
		frames[i] = sf::FloatRect(0, 0, textures[i].getSize().x, textures[i].getSize().y);
	}

	int maxSize = sf::Texture::getMaximumSize();
	PowerOfTwoBinPacker packer(maxSize, maxSize);
	if (!packer.process(frames))
	{
		err << "Failed generating metatexture. Your graphics card may have a too low maximal texture size." << endl;
	}

	tex.create(packer.width(), packer.height());

	for (unsigned int i = 0; i < textures.size(); ++i)
	{
		sf::Sprite currentTex;
		currentTex.setTexture(textures[i]);
		currentTex.setPosition(frames[i].left, frames[i].top);
		tex.draw(currentTex);
	}

	tex.display();
}

sf::FloatRect& MetaTexture::getTexRect(unsigned int index)
{
	return frames[index];
}

sf::RenderTexture& MetaTexture::getMetaTexture()
{
	return tex;
}

const sf::Texture& MetaTexture::getTexture()
{
	return tex.getTexture();
}