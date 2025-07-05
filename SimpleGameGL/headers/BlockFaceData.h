#pragma once

enum Dir {
	Back,
	Front,
	Bottom,
	Top,
	Left,
	Right
};

struct Vertex {
	float x;
	float y;
	float z;
	float u;
	float v;
};

constexpr Vertex blockVertexTemplate[6][4] = {
	// Back face (z = -0.5)
	{
		{ -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,}, // Bottom-left
		{  0.5f, -0.5f, -0.5f, 1.0f, 0.0f }, // Bottom-right
		{  0.5f,  0.5f, -0.5f, 1.0f, 1.0f }, // Top-right
		{ -0.5f,  0.5f, -0.5f, 0.0f, 1.0f }  // Top-left
	},
	// Front face (z = +0.5)
	{
		{  0.5f, -0.5f,  0.5f, 1.0f, 0.0f }, // Bottom-right
		{ -0.5f, -0.5f,  0.5f, 0.0f, 0.0f }, // Bottom-left
		{ -0.5f,  0.5f,  0.5f, 0.0f, 1.0f }, // Top-left
		{  0.5f,  0.5f,  0.5f, 1.0f, 1.0f }  // Top-right
	},
	// Bottom face (y = -0.5)
	{
		{ -0.5f, -0.5f,  0.5f, 0.0f, 1.0f }, // Top-left
		{  0.5f, -0.5f,  0.5f, 1.0f, 1.0f }, // Top-right
		{  0.5f, -0.5f, -0.5f, 1.0f, 0.0f }, // Bottom-right
		{ -0.5f, -0.5f, -0.5f, 0.0f, 0.0f }  // Bottom-left
	},
	// Top face (y = +0.5)
	{
		{ -0.5f,  0.5f, -0.5f, 0.0f, 0.0f }, // Bottom-left
		{  0.5f,  0.5f, -0.5f, 1.0f, 0.0f }, // Bottom-right
		{  0.5f,  0.5f,  0.5f, 1.0f, 1.0f }, // Top-right
		{ -0.5f,  0.5f,  0.5f, 0.0f, 1.0f }  // Top-left
	},
	// Left face (x = -0.5)
	{
		{ -0.5f, -0.5f,  0.5f, 1.0f, 0.0f }, // Bottom-right
		{ -0.5f, -0.5f, -0.5f, 0.0f, 0.0f }, // Bottom-left
		{ -0.5f,  0.5f, -0.5f, 0.0f, 1.0f }, // Top-left
		{ -0.5f,  0.5f,  0.5f, 1.0f, 1.0f }  // Top-right
	},
	// Right face (x = +0.5)
	{
		{  0.5f, -0.5f, -0.5f, 1.0f, 0.0f }, // Bottom-right
		{  0.5f, -0.5f,  0.5f, 0.0f, 0.0f }, // Bottom-left
		{  0.5f,  0.5f,  0.5f, 0.0f, 1.0f }, // Top-left
		{  0.5f,  0.5f, -0.5f, 1.0f, 1.0f }  // Top-right
	}
};