#include "../headers/Texture.h"

Texture::Texture(std::string path, std::string fileType)
{
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	stbi_set_flip_vertically_on_load(true);
	data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if (data) {
		GLenum format = GL_RGB;
		if (nrChannels == 4) format = GL_RGBA;
		else if (nrChannels == 3) format = GL_RGB;
		else if (nrChannels == 1) format = GL_RED;
		else {
			std::cout << "Unsupported channel count: " << nrChannels << std::endl;
			stbi_image_free(data);
			return;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Error loading texture: " << path << std::endl;
	}
	stbi_image_free(data);
}


void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, texID);
}

void Texture::UnBind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
