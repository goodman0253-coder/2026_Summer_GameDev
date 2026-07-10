#pragma once
class BaseScene
{
public:
    BaseScene() {}
    virtual ~BaseScene() {}
    virtual void Initialize() = 0; // ‰Šú‰»
    virtual void Update() = 0;     // XV
    virtual void Draw() = 0;       // •`‰æ
};

