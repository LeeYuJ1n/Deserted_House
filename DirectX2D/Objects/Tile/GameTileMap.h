#pragma once

class GameTileMap : public Transform
{
public:
    GameTileMap(string file);
    ~GameTileMap();

    void Render();

    void PushObject(Collider* collider);

    void GetNodes(vector<Node*>& nodes);

    UINT GetWidth() { return width; }
private:
    void Load(string file);

private:
    UINT width, height;

    Vector2 tileSize;

    vector<Quad*> bgTiles;
    vector<Tile*> objTiles;
};