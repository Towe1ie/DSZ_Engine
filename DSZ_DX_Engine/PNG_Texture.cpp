#include "PNG_Texture.h"
#include <stdlib.h>
#include <png.h>
#include "EngineCore.h"

void PNG_Texture::Load(char* file_name)
{
	png_byte header[8];

	//FILE *fp = fopen(file_name, "rb");
	FILE *fp = NULL;
	fopen_s(&fp, file_name, "rb");
	if (fp == 0)
	{
		perror(file_name);
		//this->texture = 0;
		return;
	}

	// read the header
	fread(header, 1, 8, fp);

	if (png_sig_cmp(header, 0, 8))
	{
		fprintf(stderr, "error: %s is not a PNG.\n", file_name);
		fclose(fp);
		//this->texture = 0;
		return;
	}

	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr)
	{
		fprintf(stderr, "error: png_create_read_struct returned 0.\n");
		fclose(fp);
		//this->texture = 0;
		return;
	}

	// create png info struct
	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
	{
		fprintf(stderr, "error: png_create_info_struct returned 0.\n");
		png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
		fclose(fp);
		//this->texture = 0;
		return;
	}

	// create png info struct
	png_infop end_info = png_create_info_struct(png_ptr);
	if (!end_info)
	{
		fprintf(stderr, "error: png_create_info_struct returned 0.\n");
		png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
		fclose(fp);
		//this->texture = 0;
		return;
	}

	// the code in this if statement gets called if libpng encounters an error
	if (setjmp(png_jmpbuf(png_ptr))) {
		fprintf(stderr, "error from libpng\n");
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		fclose(fp);
		//this->texture = 0;
		return;
	}

	// init png reading
	png_init_io(png_ptr, fp);

	// let libpng know you already read the first 8 bytes
	png_set_sig_bytes(png_ptr, 8);

	// read all the info up to the image data
	png_read_info(png_ptr, info_ptr);

	// variables to pass to get info
	png_uint_32 temp_width, temp_height;

	// get info about png
	png_get_IHDR(png_ptr, info_ptr, &temp_width, &temp_height, &bit_depth, &color_type,
		NULL, NULL, NULL);

	this->width = temp_width;
	this->height = temp_height;

	//printf("%s: %lux%lu %d\n", file_name, temp_width, temp_height, color_type);

	if (bit_depth != 8)
	{
		fprintf(stderr, "%s: Unsupported bit depth %d.  Must be 8.\n", file_name, bit_depth);
		//this->texture = 0;
		return;
	}

	DXGI_FORMAT format;
	switch (color_type)
	{
		case PNG_COLOR_TYPE_RGB:
			
			break;
		case PNG_COLOR_TYPE_RGB_ALPHA:
			//format = GL_RGBA;
			break;
		default:
			fprintf(stderr, "%s: Unknown libpng color type %d.\n", file_name, color_type);
			this->texture = 0;
			return;
	}

	// Update the png info struct.
	png_read_update_info(png_ptr, info_ptr);

	// Row size in bytes.
	size_t rowbytes = png_get_rowbytes(png_ptr, info_ptr);

	// glTexImage2d requires rows to be 4-byte aligned
	rowbytes += 3 - ((rowbytes - 1) % 4);

	// Allocate the image_data as a big block, to be given to opengl
	image_data = (png_byte *)malloc(rowbytes * temp_height * sizeof(png_byte) + 15);
	if (image_data == NULL)
	{
		fprintf(stderr, "error: could not allocate memory for PNG image data\n");
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		fclose(fp);
		//this->texture = 0;
		return;
	}

	// row_pointers is for pointing to image_data for reading the png with libpng
	png_byte ** row_pointers = (png_byte **)malloc(temp_height * sizeof(png_byte *));
	if (row_pointers == NULL)
	{
		fprintf(stderr, "error: could not allocate memory for PNG row pointers\n");
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		free(image_data);
		fclose(fp);
		//this->texture = 0;
		return;
	}

	// set the individual row_pointers to point at the correct offsets of image_data
	for (unsigned int i = 0; i < temp_height; i++)
	{
		row_pointers[temp_height - 1 - i] = image_data + i * rowbytes;
	}

	// read the png into image_data through row_pointers
	png_read_image(png_ptr, row_pointers);

	// Generate the OpenGL texture object
	//GLuint texture;
	//glGenTextures(1, &texture);
	//glBindTexture(GL_TEXTURE_2D, texture);
	//glTexImage2D(GL_TEXTURE_2D, 0, format, temp_width, temp_height, 0, format, GL_UNSIGNED_BYTE, image_data);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	D3D11_TEXTURE2D_DESC td;
	ZeroMemory(&td, sizeof(td));
	td.Height = height;
	td.Width = width;
	td.MipLevels = 0;
	td.ArraySize = 1;
	td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	td.CPUAccessFlags = 0;
	td.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

	ID3D11Device* dev = (ID3D11Device*)EngineCore::GetGraphicsAPI()->GetDevice();
	ID3D11DeviceContext* devcon = (ID3D11DeviceContext*)EngineCore::GetGraphicsAPI()->GetDeviceContext();

	dev->CreateTexture2D(
		&td,
		NULL,
		&texture
	);

	devcon->UpdateSubresource(
		texture,
		0,
		NULL,
		image_data,
		(width * 4) * sizeof(unsigned char),
		0
	);

	D3D11_SHADER_RESOURCE_VIEW_DESC vd;
	ZeroMemory(&vd, sizeof(vd));
	vd.Format = td.Format;
	vd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	vd.Texture2D.MostDetailedMip = 0;
	vd.Texture2D.MipLevels = -1;

	dev->CreateShaderResourceView(
		texture,
		&vd,
		&textureView
	);

	devcon->GenerateMips(textureView);

	// clean up
	png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
	//free(image_data);
	free(row_pointers);
	fclose(fp);
	//this->texture = texture;
}

PNG_Texture::~PNG_Texture()
{
	free(image_data);
	texture->Release();
	textureView->Release();
}
ID3D11Texture2D* PNG_Texture::GetTexture2D()
{
	return texture;
}

ID3D11ShaderResourceView* PNG_Texture::GetShaderResourceView()
{
	return textureView;
}

