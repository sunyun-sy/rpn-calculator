import std/strutils
import nimib

var nbToc: NbBlock

template addToc =
  newNbBlock("nbText", false, nb, nbToc, ""):
    nbToc.output = "## 目录:\n\n"

template nbNewSection(name:string) =
  let anchorName = name.toLower.replace(" ", "-")
  nbText "<a name=\"" & anchorName & "\"></a >\n<br>\n### " & name & "\n\n---"
  nbToc.output.add "1. <a href= "#" & anchorName & "\">" & name & "</a >\n"

template nbSubSection(name:string) =
  let anchorName = name.toLower.replace(" ", "-")
  nbText "<a name=\"" & anchorName & "\"></a >\n<br>\n#### " & name & "\n\n---"
  nbToc.output.add "    * <a href=\"#" & anchorName & "\">" & name & "</a >\n"

template nbQuoteBlock(code: untyped) =
  nbText "<blockquote>"
  code
  nbText "</blockquote>"

nbInit # ----------------------------- START ----------------------------------

nbText: """
《RPN计算器教程》
======================================

- 作者：孙允
- 版本：2.1.1
- 原始翻译：[Morthan](https://habr.com/ru/users/Morthan/)
- 修订、更新、nimib 移植：[janAkali](https://codeberg.org/janAkali)
addToc()

nbNewSection "RPN计算器使用教程"
"""

nbText: """
## 引言
"逆波兰表示法，让计算更直观"
本文档是 RPN 计算器的完整使用教程，详细介绍了逆波兰表示法的概念、使用方法及操作技巧。

## 目录
1. [简介](#简介)
2. [基本概念](#基本概念)
3. [安装与运行](#安装与运行)
4. [基本操作](#基本操作)
5. [功能详解](#功能详解)
6. [快捷键参考](#快捷键参考)
7. [示例演示](#示例演示)
8. [总结](#总结)
"""

nbText: """
## 基本概念

### 什么是逆波兰表示法？
传统中缀表达式：`(5 + 3) × 2`  
RPN 表达式：`5 3 + 2 ×`

### 核心思想
- 操作数在前，运算符在后
- 使用栈结构存储中间结果
- 无需括号，运算顺序明确

### 优势特点
- ：运算顺序明确，无需括号
- ：适合计算机栈结构实现
- ：操作流程自然流畅
"""


nbText: """
基本操作

启动程序

程序启动后，您将看到交互式命令行界面：

· 栈状态显示区域
· 输入提示符 >
· 实时反馈信息
  """


nbText: """
功能详解
数字输入功能：将用户输入的数字压入栈顶

stack.add(5.0)    # 输入数字 5
stack.add(3.2)    # 输入数字 3.2
echo "数字输入演示:"
echo "输入 5.0 后栈: ", stack
echo "输入 3.2 后栈: ", stack
 """

nbText: """
算术运算功能

支持四种基本算术运算，操作时弹出栈顶两个元素进行计算。

加法运算：弹出栈顶两个元素，相加后结果压回栈顶

if stack.len >= 2:
let b = stack.pop()  # 弹出栈顶元素 (3.2)
let a = stack.pop()  # 弹出次栈顶元素 (5.0)
let result = a + b   # 执行加法运算
stack.add(result)    # 结果压回栈顶
echo "算术运算演示:"
echo "计算: ", a, " + ", b, " = ", result
echo "运算后栈状态: ", stack
"""

nbText: """
栈操作功能
提供丰富的栈操作命令，方便调整计算过程。
交换栈顶元素：交换栈顶两个元素的位置

stack.add(10.0)     
stack.add(20.0)
echo "栈操作演示:"
echo "交换前栈状态: ", stack
if stack.len >= 2:
let last = stack.pop()
let secondLast = stack.pop()
stack.add(last)
stack.add(secondLast)
echo "交换后栈状态: ", stack

清空栈：移除栈中所有元素，重新开始计算

stack = @[]
echo "清空栈后状态: ", stack
"""

nbText: """
快捷键参考

操作 命令 功能描述
数字输入 0-9 . 输入数字或小数点到栈顶
加法 + 栈顶两个元素相加
减法 - 次栈顶减栈顶
乘法 * 栈顶两个元素相乘
除法 / 次栈顶除以栈顶
交换 swap 交换栈顶两个元素
丢弃 drop 移除栈顶元素
清空 clear 清空整个栈
显示 show 显示当前栈内容
帮助 help 显示帮助信息
退出 quit 退出程序
"""

nbText: """
示例演示

示例1：基础表达式计算
计算表达式：(5 + 3) × 2

重新初始化栈
stack = @[]
echo "示例1: 计算 (5 + 3) × 2"
echo "RPN 表达式: 5 3 + 2 ×"

步骤1：输入数字

stack.add(5.0)
stack.add(3.0)
echo "1. 输入 5, 3 后栈: ", stack

步骤2：加法运算

let b1 = stack.pop()
let a1 = stack.pop()
stack.add(a1 + b1)
echo "2. 执行加法后栈: ", stack, " (结果: ", stack[^1], ")"

步骤3：输入数字

stack.add(2.0)
echo "3. 输入 2 后栈: ", stack

步骤4：乘法运算

let d1 = stack.pop()
let c1 = stack.pop()
stack.add(c1 * d1)
echo "4. 执行乘法后栈: ", stack, " (最终结果: ", stack[^1], ")"
"""

nbText: """
示例2：复杂表达式计算

计算表达式：(10 - 3) × (2 + 5)
RPN 表达式：10 3 - 2 5 + ×
stack = @[]  # 清空栈

echo "示例2: 计算 (10 - 3) × (2 + 5)"
echo "RPN 表达式: 10 3 - 2 5 + ×"

计算 10 - 3

stack.add(10.0)
stack.add(3.0)
let sub_b = stack.pop()
let sub_a = stack.pop()
stack.add(sub_a - sub_b)
echo "计算 10 - 3 = ", stack[^1]

计算 2 + 5

stack.add(2.0)
stack.add(5.0)
let add_b = stack.pop()
let add_a = stack.pop()
stack.add(add_a + add_b)
echo "计算 2 + 5 = ", stack[^1]

计算乘法

let mul_b = stack.pop()
let mul_a = stack.pop()
stack.add(mul_a * mul_b)
echo "计算 (10 - 3) × (2 + 5) = ", stack[^1]
echo "最终栈状态: ", stack
"""

nbText: """
总结
通过本教程的学习，应该已经掌握了：
核心概念

✅ 理解逆波兰表示法的基本原理
✅ 掌握 RPN 表达式的构建方法
✅ 熟悉栈结构在计算中的应用

操作技能

✅ 熟练使用各种算术运算功能
✅ 掌握栈操作命令的使用技巧
✅ 能够解决复杂的数学表达式计算

实用技巧

· 多使用栈操作命令简化计算流程
· 善用交换功能调整运算顺序
· 及时清空栈避免计算错误积累

祝您使用愉快！ 🎉

如有问题或建议，请联系作者：孙允
项目仓库：https://github.com/sunyun-sy/rpn-calculator
"""
nbSave
