#pragma once
#include "GameboardItem.h"

class Blocker : public GameboardItem {
public:
    Blocker(const Gameboard& gameBoard) : GameboardItem(gameBoard) {}
    char getDisplayChar() const override {
        return '#';
    }
};
