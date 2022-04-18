#include "main.h"

/**
 * init_params - clears struct fields and reset buf
 * @params: the parameters struct
 * @ap: the argument pointer
 *
 * Return: void
 */
void init_params(params_t *params, va_list ap)
{
	params->unsign = 0;

	params->plus_flag = 0;
	params->space_flag = 0;
	params->hashtag_flag = 0;
	params->zero_flag = 0;
	params->minus_flag = 0;

	params->width = 0;
	params->precision = UINT_MAX;

	params->h_modifier = 0;
	params->l_modifier = 0;
	(void)ap;
}

print-functions.c
#include "main.h"

/**
 * print_char - prints character
 * @ap: argument pointer
 * @params: the parameters struct
 *
 * Return: number chars printed
 */
int print_char(va_list ap, params_t *params)
{
	char pad_char = ' ';
	unsigned int pad = 1, sum = 0, ch = va_arg(ap, int);

	if (params->minus_flag)
		sum += _putchar(ch);
	while (pad++ < params->width)
		sum += _putchar(pad_char);
	if (!params->minus_flag)
		sum += _putchar(ch);
	return (sum);
}

/**
 * print_int - prints integer
 * @ap: argument pointer
 * @params: the parameters struct
 *
 * Return: number chars printed
 */
int print_int(va_list ap, params_t *params)
{
	long l;

	if (params->l_modifier)
		l = va_arg(ap, long);
	else if (params->h_modifier)
		l = (short int)va_arg(ap, int);
	else
		l = (int)va_arg(ap, int);
	return (print_number(convert(l, 10, 0, params), params));
}

/**
 * print_string - prints string
 * @ap: argument pointer
 * @params: the parameters struct
 *
 * Return: number chars printed
 */
int print_string(va_list ap, params_t *params)
{
	char *str = va_arg(ap, char *), pad_char = ' ';
	unsigned int pad = 0, sum = 0, i = 0, j;

	(void)params;
	switch ((int)(!str))
		case 1:
			str = NULL_STRING;

	j = pad = _strlen(str);
	if (params->precision < pad)
		j = pad = params->precision;

	if (params->minus_flag)
	{
		if (params->precision != UINT_MAX)
			for (i = 0; i < pad; i++)
				sum += _putchar(*str++);
		else
			sum += _puts(str);
	}
	while (j++ < params->width)
		sum += _putchar(pad_char);
	if (!params->minus_flag)
	{
		if (params->precision != UINT_MAX)
			for (i = 0; i < pad; i++)
				sum += _putchar(*str++);
		else
			sum += _puts(str);
	}
	return (sum);
}

/**
 * print_percent - prints string
 * @ap: argument pointer
 * @params: the parameters struct
 *
 * Return: number chars printed
 */
int print_percent(va_list ap, params_t *params)
{
	(void)ap;
	(void)params;
	return (_putchar('%'));
}

/**
 * print_S - custom format specifier
 * @ap: argument pointer
 * @params: the parameters struct
 *
 * Return: number chars printed
 */
int print_S(va_list ap, params_t *params)
{
	char *str = va_arg(ap, char *);
	char *hex;
	int sum = 0;

	if ((int)(!str))
		return (_puts(NULL_STRING));
	for (; *str; str++)
	{
		if ((*str > 0 && *str < 32) || *str >= 127)
		{
			sum += _putchar('\\');
			sum += _putchar('x');
			hex = convert(*str, 16, 0, params);
			if (!hex[1])
				sum += _putchar('0');
			sum += _puts(hex);
		}
		else
		{
			sum += _putchar(*str);
		}
	}
	return (sum);
}

