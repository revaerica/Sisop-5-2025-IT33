#include "shell.h"
#include "kernel.h"
#include "std_lib.h"

char username[64] = "user";
char companyTag[32] = "";
int currentColor = 0x0F;

void setColor(int color) {
    currentColor = color;
    setTextColor(color);
    clearScreen(color);
}

void showPrompt() {
    printString(username);
    if (companyTag[0] != '\0') {
        printString(companyTag);
    }
    printString("> ");
}

void parseCommand(char *buf, char *cmd, char arg[2][64]) {
    int i = 0, j = 0;
    clear((byte *)cmd, 64);
    clear((byte *)arg[0], 64);
    clear((byte *)arg[1], 64);
    while (buf[i] == ' ') i++;
    while (buf[i] != ' ' && buf[i] != '\0' && buf[i] != '\r') cmd[j++] = buf[i++];
    cmd[j] = '\0';
    while (buf[i] == ' ') i++;
    j = 0;
    while (buf[i] != ' ' && buf[i] != '\0' && buf[i] != '\r') arg[0][j++] = buf[i++];
    arg[0][j] = '\0';
    while (buf[i] == ' ') i++;
    j = 0;
    while (buf[i] != '\0' && buf[i] != '\r') arg[1][j++] = buf[i++];
    arg[1][j] = '\0';
}

void handleCommand(char *cmd, char *buf, char arg[2][64]) {
    int a, b, result;
    char output[32];

    if (strcmp(cmd, "user")) {
        if (arg[0][0] == '\0') strcpy(username, "user");
        else strcpy(username, arg[0]);
        printString("Username changed to "); printString(username); printString("\r\n");
    } else if (strcmp(cmd, "grandcompany")) {
        if (strcmp(arg[0], "maelstrom")) { setColor(0x0C); strcpy(companyTag, "@Storm"); }
        else if (strcmp(arg[0], "twinadder")) { setColor(0x0E); strcpy(companyTag, "@Serpent"); }
        else if (strcmp(arg[0], "immortalflames")) { setColor(0x0B); strcpy(companyTag, "@Flame"); }
        else printString("Unknown company\r\n");
    } else if (strcmp(cmd, "clear")) {
        setColor(0x07); companyTag[0] = '\0';
    } else if (strcmp(cmd, "add")) {
        atoi(arg[0], &a); atoi(arg[1], &b); result = a + b; itoa(result, output);
        printString(output); printString("\r\n");
    } else if (strcmp(cmd, "sub")) {
        atoi(arg[0], &a); atoi(arg[1], &b); result = a - b; itoa(result, output);
        printString(output); printString("\r\n");
    } else if (strcmp(cmd, "mul")) {
        atoi(arg[0], &a); atoi(arg[1], &b); result = a * b; itoa(result, output);
        printString(output); printString("\r\n");
    } else if (strcmp(cmd, "div")) {
        atoi(arg[0], &a); atoi(arg[1], &b);
        if (b == 0) printString("Error: Division by zero\r\n");
        else { result = div(a, b); itoa(result, output); printString(output); printString("\r\n"); }
    } else if (strcmp(cmd, "yogurt")) {
        unsigned int t = getBiosTick();
        int idx = mod(t, 3);
        printString("gurt> ");
        if (idx == 0) printString("yo\r\n");
        else if (idx == 1) printString("ts unami gng </3\r\n");
        else printString("sygau\r\n");
    } else if (strcmp(cmd, "yo")) {
        printString("gurt\r\n");
    } else if (strcmp(cmd, "gurt")) {
        printString("yo\r\n");
    } else {
        printString(buf); // echo
    }
}

void shell() {
    char buf[128], cmd[64], arg[2][64];
    printString("Welcome to EorzeOS!\r\n");
    while (1) {
        showPrompt();
        readString(buf);
        parseCommand(buf, cmd, arg);
        handleCommand(cmd, buf, arg);
    }
}
// Tambahkan fungsi bila perlu
