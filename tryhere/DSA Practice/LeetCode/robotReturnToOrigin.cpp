class Solution {
public:
    bool judgeCircle(string moves) {
        size_t x = 0, y = 0;
        for (char& move : moves) {
            switch (move) {
                case 'U': y++; break;
                case 'D': y--; break;
                case 'L': x--; break;
                case 'R': x++; break;
            }
        }
        return x == 0 && y == 0;
    }
};