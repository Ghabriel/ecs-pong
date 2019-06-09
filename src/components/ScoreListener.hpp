#pragma once

#include <functional>

enum class Team {
    Left,
    Right,
};

struct ScoreListener {
    std::function<void(Team)> fn;
};
