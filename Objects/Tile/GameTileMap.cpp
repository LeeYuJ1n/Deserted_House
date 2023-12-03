#include "Framework.h"

GameTileMap::GameTileMap(string file)
{
    Pos() = { 80, 80 };
    UpdateWorld();

    Load(file);
}

GameTileMap::~GameTileMap()
{
    for (Quad* tile : bgTiles)
        delete tile;

    for (Tile* tile : objTiles)
        delete tile;
}

void GameTileMap::Render()
{
    for (Quad* tile : bgTiles)
        tile->Render();

    for (Tile* tile : objTiles)
        tile->Render();
}

void GameTileMap::PushObject(Collider* collider)
{
    for (Tile* tile : objTiles)
    {
        tile->GetCollider()->PushCollider(collider);
    }
}

void GameTileMap::GetNodes(vector<Node*>& nodes)
{
    for (Quad* tile : bgTiles)
    {
        Vector2 tilePos = tile->GlobalPos();
        Node* node = new Node(tilePos, nodes.size());

        for (Tile* obj : objTiles)
        {
            Vector2 objPos = obj->GlobalPos();

            if (objPos == tilePos)
            {
                node->SetState(Node::OBSTACLE);
            }
        }

        nodes.push_back(node);
    }
}

void GameTileMap::Load(string file)
{
    BinaryReader* reader = new BinaryReader(file);

    width = reader->UInt();
    height = reader->UInt();

    UINT size = reader->UInt();
    bgTiles.resize(size);

    for (Quad*& tile : bgTiles)
    {
        Tile::Data data;
        data.textureFile = reader->Wstring();
        data.pos.x = reader->Float();
        data.pos.y = reader->Float();
        data.angle = reader->Float();
        data.type = (Tile::Type)reader->Int();

        tile = new Quad(data.textureFile);
        tile->Pos() = data.pos;
        tile->Rot().z = data.angle;
        tile->SetParent(this);
        tile->UpdateWorld();
    }

    size = reader->UInt();
    objTiles.resize(size);

    for (Tile*& tile : objTiles)
    {
        Tile::Data data;
        data.textureFile = reader->Wstring();
        data.pos.x = reader->Float();
        data.pos.y = reader->Float();
        data.angle = reader->Float();
        data.type = (Tile::Type)reader->Int();

        tile = new Tile(data);
        tile->SetParent(this);
        tile->Update();
    }

    delete reader;
}
