#pragma once

int Initialize();
int Release();
void ProcessInput();
void InitApple();
void InitBomb();
void MoveApple();
void MoveSnake(int dir);
int DrawBuffer(int DeltaTime);