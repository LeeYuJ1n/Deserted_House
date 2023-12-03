#include "Framework.h"

CommandManager::CommandManager()
{
    commandTable["261"] = 12;
    //TODO : 커맨드 추가시 작성

    for (pair<string, int> command : commandTable)
    {
        if (command.first.size() > maxCommandLength)
            maxCommandLength = command.first.size();
    }
}

void CommandManager::Update()
{
    //InputInside();
}

void CommandManager::InputInside()
{
    if (KEY_DOWN(VK_RIGHT))
        StackCommand('0' + 6);
    if (KEY_DOWN(VK_LEFT))
        StackCommand('0' + 4);
    if (KEY_DOWN(VK_UP))
        StackCommand('0' + 8);
    if (KEY_DOWN(VK_DOWN))
        StackCommand('0' + 2);

    if (KEY_DOWN('X'))
    {
        StackCommand('0' + 1);
        CheckCommand();
    }
}

void CommandManager::StackCommand(int key)
{
    commandQueue.push(key);

    if (commandQueue.size() > maxCommandLength)
        commandQueue.pop();
}

void CommandManager::CheckCommand()
{
    string command;

    while (commandQueue.size() > 0)
    {
        command += commandQueue.front();
        commandQueue.pop();
    }

    while (command.size() > 0)
    {
        if (commandTable.count(command) > 0)
        {
            Observer::Get()->ExcuteIntParamEvent("Action", commandTable[command]);
            return;
        }
                
        //command = command.substr(1, command.length());
        command.erase(command.begin());
    }
}
