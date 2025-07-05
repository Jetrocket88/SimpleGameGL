#include "../headers/TextureArray.h"

TextureArray::TextureArray(std::string path)
{
	const unsigned int numTextures = sizeof(blockNames) / sizeof(blockNames[0]);

	//create the texture array
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D_ARRAY, ID);
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, m_Width, m_Height, numTextures, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//load the textures into layers
	for (unsigned int i = 0; i < numTextures; i++) {

		int width, height, nrChannels;
		unsigned char* data;

		std::string blockPath = path + "/" + blockNames[i] + ".png";

		stbi_set_flip_vertically_on_load(true);
		data = stbi_load(blockPath.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);
		if (!data) {
			std::cerr << "Error loading texture: " << blockPath << std::endl;
			stbi_image_free(data);
			exit(-1);
		}

		if (width != m_Width || height != m_Height) {
			std::cerr << "Texture " << blockPath << " has wrong size (expected " << m_Width << "x" << m_Height << ", got " << width << "x" << height << ")\n";
			stbi_image_free(data);
			continue;
		}

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}
}

void TextureArray::Bind(const Shader& shader) const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, ID);
	shader.setInt("uTextureArray", 0);
}
