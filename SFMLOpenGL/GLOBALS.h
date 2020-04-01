#pragma once

const int SCREEN_WIDTH{ 800 };
const int SCREEN_HEIGHT{ 600 };

constexpr float ASPECT_RATIO{ SCREEN_WIDTH / static_cast<float>(SCREEN_HEIGHT) };

const static float CAMERA_Z_VALUE{ 20.0f };

const float SCREEN_START{ -20.0f };
const float SCREEN_END{ 20.0f };
const float GROUND_POS{ (-10.0f) };