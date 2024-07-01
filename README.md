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
[](Screens/CircleUnitScreen.png)
