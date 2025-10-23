#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <map>
#include <algorithm>
#include <cctype>

class RPNCalculator {
private:
    std::stack<double> stack;
    std::vector<std::string> history;
    
    // 检查字符串是否为数字
    bool isNumber(const std::string& str) {
        if (str.empty()) return false;
        
        // 处理负数
        size_t start = 0;
        if (str[0] == '-') {
            if (str.length() == 1) return false;
            start = 1;
        }
        
        bool hasDecimal = false;
        for (size_t i = start; i < str.length(); i++) {
            if (str[i] == '.') {
                if (hasDecimal) return false; // 多个小数点
                hasDecimal = true;
            } else if (!std::isdigit(str[i])) {
                return false;
            }
        }
        return true;
    }
    
    // 检查操作符
    bool isOperator(const std::string& str) {
        return str == "+" || str == "-" || str == "*" || str == "/" || 
               str == "sqrt" || str == "^" || str == "sin" || str == "cos" || 
               str == "tan" || str == "fib" || str == "pascal";
    }
    
    // 斐波那契数列计算
    double fibonacci(int n) {
        if (n < 0) throw std::runtime_error("斐波那契数不能为负数");
        if (n == 0) return 0;
        if (n == 1) return 1;
        
        double a = 0, b = 1;
        for (int i = 2; i <= n; i++) {
            double temp = a + b;
            a = b;
            b = temp;
        }
        return b;
    }
    
    // 杨辉三角计算
    double pascal(int row, int col) {
        if (row < 0 || col < 0 || col > row) {
            throw std::runtime_error("杨辉三角坐标无效");
        }
        
        double result = 1;
        for (int i = 1; i <= col; i++) {
            result = result * (row - i + 1) / i;
        }
        return result;
    }

public:
    RPNCalculator() = default;
    
    // 压入数字到栈中
    void push(double value) {
        stack.push(value);
    }
    
    // 从栈中弹出数字
    double pop() {
        if (stack.empty()) {
            throw std::runtime_error("错误: 栈为空");
        }
        double value = stack.top();
        stack.pop();
        return value;
    }
    
    // 查看栈顶元素
    double peek() const {
        if (stack.empty()) {
            throw std::runtime_error("错误: 栈为空");
        }
        return stack.top();
    }
    
    // 清空栈
    void clear() {
        while (!stack.empty()) {
            stack.pop();
        }
    }
    
    // 获取栈大小
    size_t size() const {
        return stack.size();
    }
    
    // 显示当前栈内容
    void displayStack() const {
        if (stack.empty()) {
            std::cout << "栈: [空]" << std::endl;
            return;
        }
        
        std::stack<double> temp = stack;
        std::vector<double> elements;
        
        while (!temp.empty()) {
            elements.push_back(temp.top());
            temp.pop();
        }
        
        std::cout << "栈: ";
        for (auto it = elements.rbegin(); it != elements.rend(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
    
    // 执行计算
    void calculate(const std::string& operation) {
        if (operation == "+") {
            if (stack.size() < 2) throw std::runtime_error("错误: 需要2个操作数进行加法");
            double b = pop();
            double a = pop();
            push(a + b);
        }
        else if (operation == "-") {
            if (stack.size() < 2) throw std::runtime_error("错误: 需要2个操作数进行减法");
            double b = pop();
            double a = pop();
            push(a - b);
        }
        else if (operation == "*") {
            if (stack.size() < 2) throw std::runtime_error("错误: 需要2个操作数进行乘法");
            double b = pop();
            double a = pop();
            push(a * b);
        }
        else if (operation == "/") {
            if (stack.size() < 2) throw std::runtime_error("错误: 需要2个操作数进行除法");
            double b = pop();
            if (b == 0) throw std::runtime_error("错误: 除零错误");
            double a = pop();
            push(a / b);
        }
        else if (operation == "sqrt") {
            if (stack.empty()) throw std::runtime_error("错误: 需要1个操作数进行平方根运算");
            double a = pop();
            if (a < 0) throw std::runtime_error("错误: 不能对负数求平方根");
            push(std::sqrt(a));
        }
        else if (operation == "^") {
            if (stack.size() < 2) throw std::runtime_error("错误: 需要2个操作数进行幂运算");
            double b = pop();
            double a = pop();
            push(std::pow(a, b));
        }
        else if (operation == "sin") {
            if (stack.empty()) throw std::runtime_error("错误: 需要1个操作数进行正弦运算");
            double a = pop();
            push(std::sin(a * M_PI / 180.0)); // 转换为弧度
        }
        else if (operation == "cos") {
            if (stack.empty()) throw std::runtime_error("错误: 需要1个操作数进行余弦运算");
            double a = pop();
            push(std::cos(a * M_PI / 180.0));
        }
        else if (operation == "tan") {
            if (stack.empty()) throw std::runtime_error("错误: 需要1个操作数进行正切运算");
            double a = pop();
            double rad = a * M_PI / 180.0;
            if (std::cos(rad) == 0) throw std::runtime_error("错误: 正切值不存在");
            push(std::tan(rad));
        }
        else if (operation == "fib") {
            if (stack.empty()) throw std::runtime_error("错误: 需要1个操作数计算斐波那契数");
            double n = pop();
            if (n != static_cast<int>(n) || n < 0) {
                throw std::runtime_error("错误: 斐波那契数必须是非负整数");
            }
            push(fibonacci(static_cast<int>(n)));
        }
        else if (operation == "pascal") {
            if (stack.size() < 2) throw std::runtime_error("错误: 需要2个操作数计算杨辉三角");
            double col = pop();
            double row = pop();
            if (row != static_cast<int>(row) || col != static_cast<int>(col)) {
                throw std::runtime_error("错误: 杨辉三角坐标必须是整数");
            }
            push(pascal(static_cast<int>(row), static_cast<int>(col)));
        }
        else {
            throw std::runtime_error("错误: 未知操作符 '" + operation + "'");
        }
    }
    
    // 处理RPN表达式
    double processExpression(const std::string& expression) {
        std::istringstream iss(expression);
        std::string token;
        std::vector<std::string> tokens;
        
        // 分割tokens
        while (iss >> token) {
            tokens.push_back(token);
        }
        
        // 处理每个token
        for (const auto& t : tokens) {
            if (isNumber(t)) {
                push(std::stod(t));
            } else if (isOperator(t)) {
                calculate(t);
            } else {
                throw std::runtime_error("错误: 无效的token '" + t + "'");
            }
        }
        
        if (stack.size() != 1) {
            throw std::runtime_error("错误: 表达式不完整");
        }
        
        double result = pop();
        history.push_back(expression + " = " + std::to_string(result));
        return result;
    }
    
    // 显示计算历史
    void showHistory() const {
        if (history.empty()) {
            std::cout << "计算历史: [空]" << std::endl;
            return;
        }
        
        std::cout << "计算历史:" << std::endl;
        for (size_t i = 0; i < history.size(); i++) {
            std::cout << i + 1 << ". " << history[i] << std::endl;
        }
    }
    // 清空历史
    void clearHistory() {
        history.clear();
    }
};

// 批量计算函数
void batchCalculation(RPNCalculator& calc, const std::vector<std::string>& expressions) {
    std::cout << "开始批量计算..." << std::endl;
    for (size_t i = 0; i < expressions.size(); i++) {
        try {
            calc.clear();
            double result = calc.processExpression(expressions[i]);
            std::cout << "表达式 " << (i + 1) << ": " << expressions[i] << " = " << result << std::endl;
        } catch (const std::exception& e) {
            std::cout << "表达式 " << (i + 1) << " 错误: " << e.what() << std::endl;
        }
    }
    std::cout << "批量计算完成." << std::endl;
}

// 显示帮助信息
void showHelp() {
    std::cout << "\n=== RPN计算器帮助 ===" << std::endl;
    std::cout << "基本操作:" << std::endl;
    std::cout << "  +, -, *, /  : 四则运算" << std::endl;
    std::cout << "  sqrt        : 平方根" << std::endl;
    std::cout << "  ^           : 幂运算" << std::endl;
    std::cout << "  sin, cos, tan: 三角函数(角度制)" << std::endl;
    std::cout << "高级操作:" << std::endl;
    std::cout << "  fib         : 斐波那契数列 (n fib -> fib(n))" << std::endl;
    std::cout << "  pascal      : 杨辉三角 (row col pascal -> C(row, col))" << std::endl;
    std::cout << "命令:" << std::endl;
    std::cout << "  stack       : 显示当前栈" << std::endl;
    std::cout << "  clear       : 清空栈" << std::endl;
    std::cout << "  history     : 显示计算历史" << std::endl;
    std::cout << "  clearhistory: 清空历史" << std::endl;
    std::cout << "  batch       : 进入批量计算模式" << std::endl;
    std::cout << "  help        : 显示此帮助" << std::endl;
    std::cout << "  q           : 退出程序" << std::endl;
    std::cout << "示例:" << std::endl;
    std::cout << "  5 5 +        -> 10" << std::endl;
    std::cout << "  2 3 ^        -> 8" << std::endl;
    std::cout << "  9 sqrt       -> 3" << std::endl;
    std::cout << "  5 fib        -> 5" << std::endl;
    std::cout << "  4 2 pascal   -> 6" << std::endl;
    std::cout << "====================\n" << std::endl;
}

int main() {
    RPNCalculator calc;
    std::string input;
    
    std::cout << "=== C++ RPN 计算器 ===" << std::endl;
    std::cout << "输入 'help' 查看帮助, 'q' 退出程序." << std::endl;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        
        if (input == "q" || input == "quit") {
            break;
        } else if (input == "help") {
            showHelp();
        } else if (input == "stack") {
            calc.displayStack();
        } else if (input == "clear") {
            calc.clear();
            std::cout << "栈已清空." << std::endl;
        } else if (input == "history") {
            calc.showHistory();
        } else if (input == "clearhistory") {
            calc.clearHistory();
            std::cout << "历史已清空." << std::endl;
        } else if (input == "batch") {
            std::cout << "批量计算模式 (输入空行结束):" << std::endl;
            std::vector<std::string> expressions;
            std::string expr;
            int count = 1;
            
            while (true) {
                std::cout << "表达式 " << count << ": ";
                std::getline(std::cin, expr);
                if (expr.empty()) break;
                expressions.push_back(expr);
                count++;
            }
            
            if (!expressions.empty()) {
                batchCalculation(calc, expressions);
            }
        } else if (!input.empty()) {
            try {
                double result = calc.processExpression(input);
                std::cout << "结果: " << result << std::endl;
            } catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
            }
        }
    }
    
    std::cout << "感谢使用RPN计算器!" << std::endl;
    return 0;
}
