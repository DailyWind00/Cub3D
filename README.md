# Cub3D ✅115/100
A raycaster like Wolfenstein 3D

This project make you use your first graphic library :
- ![cub3D subject](fr.subject.pdf)

I did this project with Tuvosyl
- ![Tuvosyl Github](https://github.com/tuvosyl)

Check also my itch.io profile :
- [itch.io](https://dailywind.itch.io/)

This project use the readline function, causing some leaks and weirds issues in the code, to fix the leaks, use :
```shell
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s --keep-debuginfo=yes --suppressions="mlx42.supp" ./minishell
```


To understand my program, you need to see the circle unit :
[CircleUnitScreen.png](https://github.com/DailyWind00/Cub3D/blob/main/Screens/CircleUnitScreen.png)

To use the program, you must do these commands :
```shell
cd cub3D
make

# Program :
./cub3D <MAP PATH>
```

To use the mouse for camera, you must do these commands :
```shell
cd cub3D
make bonus

# Program :
./cub3D <MAP PATH>
```

You also have these commands for cleaning the cub3D directory :
```shell
# Clean all object files (*.o)
make clean

# Clean executable & object files
make fclean

# Clean everything and recompile the executable
make re
```
