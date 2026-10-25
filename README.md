# C 小游戏

这个仓库包含两个 Windows 控制台小游戏：

- `minesweeper/`：扫雷
- `snake/`：贪吃蛇

## 构建

扫雷由 `test.c`、`game.c` 和 `game.h` 组成；贪吃蛇的全部代码在 `snake.c` 中。两个项目都依赖 Windows 控制台环境。使用 MSVC 编译含中文输出的扫雷代码时，可添加 `/utf-8` 选项。
