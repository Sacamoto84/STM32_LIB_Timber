/**
 ******************************************************************************
 * Timber
 *
 * Версия 1.0 19.10.2025
 *
 ******************************************************************************
 */

#ifndef UTILS_LOGUART_H_
#define UTILS_LOGUART_H_

#include "usart.h"
#include "stdio.h"
#include "stdarg.h"
#include "string.h"

#define COLOR_WARNING "\33[38;05;11m"
#define COLOR_ERROR   "\33[38;05;9m"
#define COLOR_RESET   "\33[0m"

class Timber {
public:

	void init(UART_HandleTypeDef *_huart) {
		huart = _huart;
	}

	void clear(void) {
		print("\33[1m\n");
	}   //Очистка терминала


	void reset(void) {
		print("\33[0m");
	}

	void resetln(void) {
		print("\33[0m\n");
	}

	void print(char const *format) {
		HAL_UART_Transmit(huart, (uint8_t*) format, strlen(format), 1000);
	}

	template<typename ... Args> void print(char const *const format,
			Args const &... args) noexcept {
		sprintf(str, format, args ...);
		HAL_UART_Transmit(huart, (uint8_t*) str, strlen(str), 1000);
	}

	template<typename ... Args>
	void println(char const *const format, Args const &... args) noexcept {
		sprintf(str, format, args ...);
		strcat(str, "\n");
		HAL_UART_Transmit(huart, (uint8_t*) str, strlen(str), 1000);

	}

	void println(char const *format) {
		HAL_UART_Transmit(huart, (uint8_t*) format, strlen(format), 1000);
	}

	//Вывести строку с нужным цветом

	template<typename ... Args>
	void w(char const *const format, Args const &... args) noexcept {
		sprintf(str, format, args ...);
		colorStringln(11, str);
	}

	template<typename ... Args>
	void e(char const *const format, Args const &... args) noexcept {
		sprintf(str, format, args ...);
		colorStringln(9, str);
	}

	template<typename ... Args>
	void i(char const *const format, Args const &... args) noexcept {
		sprintf(str, format, args ...);
		colorStringln(45, str);
	}

	template<typename ... Args>
	void s(char const *const format, Args const &... args) noexcept {
		sprintf(str, format, args ...);
		colorStringln(10, str);
	}

	char str[256];

	UART_HandleTypeDef *huart;

	void w(char const *const format) {
		colorStringln(11, format);
	}

	void e(char const *const format) {
		colorStringln(9, format);
	}

	void i(char const *const format) {
		colorStringln(45, format);
	}

	void s(char const *const format) {
		colorStringln(10, format);
	}

	void setBold(void) {
		char s[16];
		sprintf(s, "\33[01m");
		print(s);
	}

	void setItalic(void) {
		char s[16];
		sprintf(s, "\33[03m");
		print(s);
	}

	void setUnderline(void) {
		char s[16];
		sprintf(s, "\33[04m");
		print(s);
	}

	void setRevers(void) {
		char s[16];
		sprintf(s, "\33[07m");
		print(s);
	}

	void setFlash(void) {
		char s[16];
		sprintf(s, "\33[08m");
		print(s);
	}

	void color(int color = 15) {
		char s[16];
		sprintf(s, "\33[38;05;%dm", color);
		print(s);
	}

	void bgcolor(int color = 0) {
		char s[16];
		sprintf(s, "\33[48;05;%dm", color);
		print(s);
	}

	void colorString(int c, char const *const format) {
		color(c);
		print(format);
		print("\33[0m");
	}

	void colorString(int color, int bgcolor, char const *const format) {
		char s[32];
		sprintf(s, "\33[38;05;%d;48;05;%dm", color, bgcolor);
		print(s);
		print(format);
		print("\33[0m");
	}

	void colorStringln(int c, char const *const format) {
		color(c);
		print(format);
		print("\33[0m\n");
	}

	void colorStringln(int color, int bgcolor, char const *const format) {
		char s[32];
		sprintf(s, "\33[38;05;%d;48;05;%dm", color, bgcolor);
		print(s);
		print(format);
		print("\33[0m\n");
	}

};

#endif /* UTILS_LOGUART_H_ */
