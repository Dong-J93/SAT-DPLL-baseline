# 基于SAT的二进制数独游戏求解程序



## 使用须知

1. 是_最最最简单的实现版本_（包括：邻接表，递归，复制回溯，策略为选第一个变元），能在性能算例与一些中型算例上运行，程序突然结束就是内存爆了
2. 需要下载算例文件`SAT测试备选算例`
3. 使用时只需要修改读取路径为（2）中文件的路径，注意`\\`，位于cnfparser.c文件的第6行，运行代码后选择操作1
4. 选择别的cnf文件可修改main.c文件的第26-30行代码
5. 为了突出后续优化效果，贴心地为您负优化了一些部分
6. 如果有任何问题，请提issue，看心情回
7. 会更新数独部分，但是这两天不想写，不接受催更
