#ifndef SPRITE_ANIMATION
#define SPRITE_ANIMATION

#include <vector>

class SpriteAnimation
{
private:
    unsigned int** vao;
    int animStatus;
    int animStatusMax;
    int animIndex;
    int* animIndexMax;
    float animInterval;
    float* animIntervalMax;
    int** xCenter;
    int** yCenter;
    int** width;
    int** height;
protected:
    void CreateAnim(int status_count, int index_count[]);
public:
    SpriteAnimation();
    ~SpriteAnimation();

    void SetAnimInfo(std::vector<std::vector<int>> vao, std::vector<float> max, 
        std::vector<std::vector<int>> xCenter, std::vector<std::vector<int>> yCenter,
        std::vector<std::vector<int>> width, std::vector<std::vector<int>> height);

    void UpdateAnim(float deltatime);

    void SetAnimStatus(int status);
    unsigned int GetVao() { return this->vao[animStatus][animIndex]; }
    unsigned int* GetVao(int status, int index) { return &this->vao[status][index]; }
    int GetCenterX() { return this->xCenter[animStatus][animIndex]; }
    int GetCenterY() { return this->yCenter[animStatus][animIndex]; }
    int GetWidth() { return this->width[animStatus][animIndex]; }
    int GetHeight() { return this->height[animStatus][animIndex]; }
    int GetAnimStatusMax() { return this->animStatusMax; }
    int GetAnimIndexMax(int status) { return this->animIndexMax[status]; }

    void DeleteAnim();

    SpriteAnimation& operator = (const SpriteAnimation anim);
};

#endif