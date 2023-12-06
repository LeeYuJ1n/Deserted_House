#pragma once

struct GlobalEvent
{
    void operator()(string keyword);
    void operator()(string keyword, string args);
};
