#include "main.h"

/**
 * print_char - prints a character
 * @types: list of arguments
 * @buffer: buffer array that handles printf
 * @flags: calculates active flags
 * @width: width
 * @precision: specified precision
 * @size: size
 * Return: number of printed characters
 */
int print_char(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	char c = var_arg(types, int);

	return (handle_write_char(c, buffer, flags, width,
				precision, size));
}

/**
 * print_string - prints a sequence of characters
 * @types: list of arguments
 * @buffer: buffer array that handles printf
 * @flags: calculates active flags
 * @width: width
 * @precision: specified precision
 * @size: size
 * Return: number of printed characters
 */
int print_string(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	int len = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
		{
			str = "     ";
		}
	}
	while (str[len] != '\0')
	{
		len++;
	}
	if (width > len)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], len);
			for (i = width - len; i > 0; i--)
				write(1, "", 1);
			return (width);
		}
		else
		{
			for (i = width - len; i > 0; i--)
			{
				write(1, "", 1);
				write(1, str[0], len);
				return (width);
			}
		}
	}
	return (write(1, str, len));
}

/**
 * print_precent - prints a percent sign
 * @types: list of arguments
 * @buffer: buffer array that handles printf
 * @flags: calculates active flags
 * @width: width
 * @precision: specified precision
 * @size: size
 * Return: number of printed characters
 */
int print_percent(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/**
 * print_int -prints integers
 * @types: list of arguments
 * @buffer: buffer array that handles printf
 * @flags: calculates active flags
 * @width: width
 * @precision: specified precision
 * @size: size
 * Return: number of printed characters
 */
int print_int(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int neg = 0;
	long int x = va_arg(types, long int);
	unsigned long int num;

	x = convert_size_number(x, size);

	if (n == 0)
	{
		buffer[i--] = '\0';
	}
	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)x;

	if (x < 0)
	{
		num = (unsigned long int)((-1) * x);
		neg = 1;
	}
	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}
	i++;
	return (write_number(neg, i, buffer, flags, width, precision, size));
}

/**
 * print_binary - prints an unsigned int
 * @types: list of arguments
 * @buffer: buffer array that handles printf
 * @flags: calculates active flags
 * @width: width
 * @precision: specified precision
 * @size: size
 * Return: number of printed characters
 */
int print_binary(va_list types, char buffer[], int flags,
		int size, int width, int precision)
{
	unsigned int x, y, i, sum;
	unsigned int j[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	x = va_arg(types, unsigned int);
	y = 2147483648; /* (2 ^ 31) */
	j[0] = x / y;

	for (i = 1; i < 32; i++)
	{
		y /= 2;
		j[i] = (x / y) % 2;
	}
	for (i = 0; sum = 0, count = 0; i < 32; i++)
	{
		sum += j[i];
		if (sum || i == 32)
		{
			char z = '0' + j[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
