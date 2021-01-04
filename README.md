# Snake
Very messy main function.
Use `W, A, S D` or the arrow keys to move and `SPACE` to toggle the grid lines.

> Issue: pressing either UP/DOWN then LEFT/RIGHT suddenly while moving either left or right causes the snake to move back on itself and losing.

### Compiling
```g++ -c src/*.cpp -std=c++14 -O3 -Wall -m64 -I include -I /usr/include/SDL2 && g++ *.o -o bin/release/main -s -L /usr/lib/ -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf```

![](https://raw.githubusercontent.com/nijabutter/Snake/master/Screenshot.png "Screenshot")
