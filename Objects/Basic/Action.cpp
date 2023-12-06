#include "Framework.h"

Action::Action(string path, string file, bool isLoop, float speed)
{
    LoadClip(path, file, isLoop, speed);
}

Action::Action()
{
}

Action::~Action()
{
    delete clip;
}

void Action::Update()
{
    clip->Update();
}

void Action::Render()
{
    clip->Render();
}

void Action::Start()
{
    clip->Play();
}

void Action::LoadClip(string path, string file, bool isLoop, float speed)
{
    tinyxml2::XMLDocument* document = new tinyxml2::XMLDocument();
    document->LoadFile((path + file).c_str());

    tinyxml2::XMLElement* atlas = document->FirstChildElement();
    string textureFile = path + atlas->Attribute("imagePath");

    vector<Frame*> frames;
    tinyxml2::XMLElement* sprite = atlas->FirstChildElement();

    while (sprite != nullptr)
    {
        float x, y, w, h;
        x = sprite->FloatAttribute("x");
        y = sprite->FloatAttribute("y");
        w = sprite->FloatAttribute("w");
        h = sprite->FloatAttribute("h");

        frames.push_back(new Frame(ToWString(textureFile), x, y, w, h));

        sprite = sprite->NextSiblingElement();
    }

    clip = new Clip(frames, isLoop, speed);

    delete document;
}