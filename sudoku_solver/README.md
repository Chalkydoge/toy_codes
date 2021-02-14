# 一个无聊的求解数独的程序

- [ ] (命令行)版本, 毫无卵用, 仅供娱乐😂

- [x] ~~GUI是不可能会的~~ ...(!)

## 使用方式

输入: None.

输出: 一个`9 * 9`的数独, 以.代表空格, 输出的保证为有效的数独, 并且只有唯一的一个解.

## 介绍

- 使用`Dancing Links`求解精确覆盖问题

- 数独的3个限制条件就可以完美的匹配精确匹配的条件: 1. 完全覆盖 2. 最小代价 3. 确定性

- DLX采用双向循环十字链表(数组)的方式对于回溯状态进行更好的存储与表示

- link 与 delete中的操作: `L[R[X]] = L[X], R[L[X]] =R[X]` 就巧妙地将X结点`删除`

- 对于每一行每一列, 都要填写一个数字-> 0 - 80 的link

- 对于每一行 `1~9` 只能出现1次 81 -> 162

- 对于每一列 `1~9` 只能出现1次 163 -> 242

- 对于每一宫 `1~9` 只能出现1次 243 -> 323

- 最后的dance算法就是试图寻找一个可能的解: 每次选择最少的行, 删除本行与及其关联的所有, 然后继续递归查找.