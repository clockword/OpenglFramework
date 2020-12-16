#include "sprite_animation.h"

SpriteAnimation::SpriteAnimation()
{
	vao = nullptr;
	animStatus = 0;
	animStatusMax = 0;
	animIndex = 0;
	animIndexMax = nullptr;
	animInterval = 0.0f;
	animIntervalMax = nullptr;
	xCenter = nullptr;
	yCenter = nullptr;
	width = nullptr;
	height = nullptr;

	isContinuous = true;
}

SpriteAnimation::~SpriteAnimation()
{
}

void SpriteAnimation::CreateAnim(int status_count, int index_count[])
{
	if (status_count <= 0)
		return;

	animStatusMax = status_count;

	vao = new unsigned int* [status_count];
	animIndexMax = new int[status_count];
	animIntervalMax = new float[status_count];
	xCenter = new int* [status_count];
	yCenter = new int* [status_count];
	width = new int* [status_count];
	height = new int* [status_count];
	for (int i = 0; i < status_count; ++i)
	{
		animIndexMax[i] = index_count[i];

		vao[i] = new unsigned int[index_count[i]];
		xCenter[i] = new int[index_count[i]];
		yCenter[i] = new int[index_count[i]];
		width[i] = new int [index_count[i]];
		height[i] = new int [index_count[i]];
	}
}

void SpriteAnimation::SetAnimInfo(std::vector<std::vector<int>> vao, std::vector<float> max, 
	std::vector<std::vector<int>> xCenter, std::vector<std::vector<int>> yCenter,
	std::vector<std::vector<int>> width, std::vector<std::vector<int>> height)
{
	int size = (int)vao.size();
	int* index = nullptr;
	index = new int[size];
	for (int i = 0; i < size; ++i)
		index[i] = (int)vao[i].size();

	CreateAnim(size, index);

	delete[] index;
	for (int i = 0; i < animStatusMax; ++i)
	{
		int indexMax = animIndexMax[i];
		for (int j = 0; j < indexMax; ++j)
		{
			this->vao[i][j] = vao[i][j];
			this->xCenter[i][j] = xCenter[i][j];
			this->yCenter[i][j] = yCenter[i][j];
			this->width[i][j] = width[i][j];
			this->height[i][j] = height[i][j];
		}
		this->animIntervalMax[i] = max[i];
	}		
}

void SpriteAnimation::UpdateAnim(float deltatime)
{
	animInterval += deltatime;

	if (animInterval >= animIntervalMax[animStatus] * 0.001f)
	{
		animInterval = 0.0f;
		++animIndex;
		if (!isContinuous && animIndex == animIndexMax[animStatus] - 1)
			isContinuous = true;
		if (animIndex >= animIndexMax[animStatus])
			animIndex = 0;
	}
}

void SpriteAnimation::SetAnimStatus(int status, bool isContinuous)
{
	if (!this->isContinuous && isContinuous)
		return;

	this->animStatus = status;
	this->animInterval = 0.0f;
	this->animIndex = 0;

	this->isContinuous = isContinuous;
}

void SpriteAnimation::DeleteAnim()
{
	if (vao != nullptr)
	{
		for (int i = 0; i < animStatusMax; ++i)
		{
			delete[] vao[i];
			delete[] xCenter[i];
			delete[] yCenter[i];
			delete[] width[i];
			delete[] height[i];
		}
		delete[] vao;
		delete[] xCenter;
		delete[] yCenter;
		delete[] width;
		delete[] height;

		delete[] animIndexMax;
		delete[] animIntervalMax;
	}
}

SpriteAnimation& SpriteAnimation::operator=(const SpriteAnimation anim)
{
	animStatusMax = anim.animStatusMax;
	if (vao == nullptr)
		CreateAnim(anim.animStatusMax, anim.animIndexMax);

	for (int i = 0; i < animStatusMax; ++i)
	{
		animIndexMax[i] = anim.animIndexMax[i];
		animIntervalMax[i] = anim.animIntervalMax[i];
		int count = animIndexMax[i];
		for (int j = 0; j < count; ++j)
		{
			vao[i][j] = anim.vao[i][j];
			xCenter[i][j] = anim.xCenter[i][j];
			yCenter[i][j] = anim.yCenter[i][j];
			width[i][j] = anim.width[i][j];
			height[i][j] = anim.height[i][j];
		}
	}

	return *this;
}
