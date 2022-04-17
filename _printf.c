#include "main.h"
/**
 * _printf - Function to print strings and characters in console.
 *
 * Return: Always a int equivalent to the print length.
 * @format: is a char pointer to a string that takes to print.
 */
int _printf(const char *format, ...)
{
	int i, j, bool = 0, len;
	va_list any;
	print_t p[] = {
		{"c", print_char},
		{"s", print_string},
		{"%", print_percent},
		{"i", print_int},
		{"d", print_int},
		{NULL, NULL}};

	if (format == NULL)
		return (-1);
	len = _strlen(format);
	va_start(any, format);
	for (i = 0; format[i] != '\0'; i++)
	{
		if (format[i] == '%')
		{
			if (format[i + 1] == '\0' || (format[i + 1] == 32 && format[i + 1] == '\0'))
				return (-1);
			for (j = 0; p[j].string != NULL; j++)
			{
				if (format[i + 1] == *(p[j].string))
				{
					len += p[j].fun(any);
					len -= 2, i++, bool = 1; }
			}
			if (bool == 0)
				_putchar(format[i]);
		}
		else
			_putchar(format[i]);
	}
	va_end(any);
	return (len);
}
