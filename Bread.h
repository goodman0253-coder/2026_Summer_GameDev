#pragma once
#include "BreadBase.h"


class Bread : public BreadBase
{
public:
    Bread(float startX, float startY, AsoUtility::DIR direction);
    virtual ~Bread() override;

    void Update() override;

    int GetCoolTime() const override { return 180; }

    
};

