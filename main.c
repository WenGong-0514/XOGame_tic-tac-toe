#include <stdio.h> 

#ifndef STDBOOL_H
#define STDBOOL_H

typedef int bool;
#define true 1
#define false 0

#endif

// 检查棋盘状态：1为玩家胜利，2为机器胜利，0为平局，-1为游戏进行中
int checkwin(int board[9]) {
    int win_conditions[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
    };
    for (int i = 0; i < 8; i++) {
        if (board[win_conditions[i][0]] != 0 &&
            board[win_conditions[i][0]] == board[win_conditions[i][1]] &&
            board[win_conditions[i][1]] == board[win_conditions[i][2]]) {
            return board[win_conditions[i][0]];
        }
    }
    for (int i = 0; i < 9; i++) {
        if (board[i] == 0) return -1;
    }
    return 0;
}

// 判断棋盘上是否还有空位
bool isMovesLeft(int board[9]) {
    for (int i = 0; i < 9; i++) {
        if (board[i] == 0) {
            return true;
        }
    }
    return false;
}

// 迷你麦克斯算法：评估当前棋盘的最佳得分
int minimax(int board[9], int depth, bool isMax) {
    int score = checkwin(board);
    if (score == 1) return -10 + depth;  // 黑棋胜，返回负分
    if (score == 2) return 10 - depth;   // 白棋胜，返回正分
    if (!isMovesLeft(board)) return 0;   // 平局

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < 9; i++) {
            if (board[i] == 0) {
                board[i] = 2;
                int moveVal = minimax(board, depth + 1, false);
                board[i] = 0;
                if (moveVal > best) {
                    best = moveVal;
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 9; i++) {
            if (board[i] == 0) {
                board[i] = 1;
                int moveVal = minimax(board, depth + 1, true);
                board[i] = 0;
                if (moveVal < best) {
                    best = moveVal;
                }
            }
        }
        return best;
    }
}

// 寻找当前棋盘状态下电脑的最佳移动
int findBestMove(int board[9]) {
    int gameStatus = checkwin(board);
    if (gameStatus != -1) {
    	if(gameStatus == 0)return 99;// 游戏已经结束，无需继续寻找最佳移动
        if(gameStatus == 1)return -11; 
        if(gameStatus == 2)return 9;
    }

    int bestVal = -1000;
    int bestMove = -1;
    for (int i = 0; i < 9; i++) {
        if (board[i] == 0) {
            board[i] = 2;
            int moveVal = minimax(board, 0, false);
            board[i] = 0;
            if (moveVal > bestVal) {
                bestMove = i;
                bestVal = moveVal;
            }
        }
    }
    return bestMove;
}

// 主函数，用于测试findBestMove函数
int main() {
    int board[9] = {0, 0, 0,
					0, 0, 0,
					0, 0, 0}; // 示例棋盘，1表示玩家，2表示机器
    int bestMove = findBestMove(board);
    printf("电脑应下的位置是：%d\n", bestMove + 1); // 输出电脑应下的位置
    //返回100和棋 返回-10则玩家胜利 返回10则机器胜利 返回1-9则最优解
    //理论上不能返回-10 即玩家无论如何不能胜利 如果完全由机器运行的对局出现了-10 那么这个代码就是垃圾 依托答辩
    return 0;
}

