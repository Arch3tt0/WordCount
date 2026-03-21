#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {  // 需3个参数：程序名、控制参数、文件名
        printf("用法：%s [-c|-w] 输入文件名\n", argv[0]);
        return 1;  // 非0返回值表示程序异常退出
    }

    // ========== 2. 解析控制参数（-c/-w） ==========
    int is_char = 0;  // 标记统计类型：1=字符数，0=单词数
    if (strcmp(argv[1], "-c") == 0) {
        is_char = 1;
    } else if (strcmp(argv[1], "-w") == 0) {
        is_char = 0;
    } else {
        printf("错误：控制参数仅支持 -c（字符数）或 -w（单词数）\n");
        return 1;
    }

    // ========== 3. 打开目标文件 ==========
    FILE *fp = fopen(argv[2], "r");  // 以“读模式”打开文件
    if (fp == NULL) {
        printf("错误：无法打开文件 %s\n", argv[2]);
        return 1;
    }

    // ========== 4. 初始化统计变量 ==========
    int char_count = 0;  // 字符统计结果
    int word_count = 0;  // 单词统计结果
    int prev_sep = 1;    // 标记“前一个字符是否为分隔符”（初始为true，对应文件开头）

    // ========== 5. 逐字符读取并统计 ==========
    int ch;  // 存储当前读取的字符（fgetc返回值为int，兼容EOF）
    while ((ch = fgetc(fp)) != EOF) {  // 循环直到文件末尾
        // -------- 字符统计逻辑：所有字符都计数 --------
        if (is_char) {
            char_count++;
        }

        // -------- 单词统计逻辑：仅当“非分隔符且前一字符是分隔符”时计数 --------
        if (ch == ' ' || ch == ',') {  // 分隔符为空格或逗号
            prev_sep = 1;
        } else {
            if (prev_sep) {  // 前一字符是分隔符，当前字符启动新单词
                word_count++;
                prev_sep = 0;  // 标记当前字符为“非分隔符”
            }
        }
    }

    // ========== 6. 关闭文件并输出结果 ==========
    fclose(fp);  // 释放文件资源
    if (is_char) {
        printf("字符数：%d\n", char_count);
    } else {
        printf("单词数：%d\n", word_count);
    }

    return 0;  // 0表示程序正常退出
}