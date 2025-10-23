import nimib

nbInit

nbText: """
# RPN 计算器使用手册

## 简介
这是一个基于C++实现的逆波兰表示法（Reverse Polish Notation）计算器。
逆波兰表示法是一种数学表达式表示法，其中操作符位于操作数之后。

## 安装和编译
"""

nbCode:
  # 编译C++程序
  discard "g++ src/rpn_calc.cpp -o rpm_calc"

nbText: """
使用以上命令编译程序，生成可执行文件 `rpm_calc`。

## 基本使用
"""

nbCode:
  # 运行程序
  discard "./rpm_calc"

nbText: """
程序启动后会显示提示信息，等待用户输入。

## 支持的操作
"""

nbText: """
### 四则运算
- **加法**: `+`
- **减法**: `-` 
- **乘法**: `*`
- **除法**: `/`

### 栈操作命令
- **清空栈**: `clear`
- **显示栈**: `show`
- **退出程序**: `q` 或 `quit`
"""

nbText: """
## 使用示例
"""

nbText: """
### 示例 1: 基础运算
计算表达式: `5 5 +`
"""

nbCode:
  discard """
  > 5 5 +
  当前栈: 10
  """

nbText: """
### 示例 2: 复杂表达式  
计算表达式: `1 2 + 3 + 7 7 * +`
"""

nbCode:
  discard """
  > 1 2 + 3 + 7 7 * +
  当前栈: 55
  """

nbText: """
### 示例 3: 连续操作
"""

nbCode:
  discard """
  > 10
  当前栈: 10
  > 5
  当前栈: 10 5
  > /
  当前栈: 2
  > clear
  栈已清空
  """

nbText: """
## 错误代码和异常说明
"""

nbText: """
### 常见错误信息

1. **栈空错误**
"""

nbSave
