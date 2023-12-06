#pragma once

class CommandManager : public Singleton<CommandManager>
{
private:
    friend class Singleton;
    
    CommandManager();
    ~CommandManager() = default;

public:
    void Update();

private:

    void StackCommand(int key);
    void CheckCommand();

    void InputInside();

private:
    queue<int> commandQueue;

    unordered_map<string, int> commandTable;

    UINT maxCommandLength = 0;
};