#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - print function
 * @format: format
 * Return: printed characters
 */

int _printf(const char *format, ...)
{
	int x, y = 0, p_char = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list lst;
	char buffer[BUFF_SIZE];

	if (format == NULL)
	{
		return (-1);
	}
	va_start(lst, format);
	for (x = 0; format && format[x] != '\0'; x++)
	{
		if (format[x] != '%')
		{
			buffer[buff_ind++] == format[x];
			if (buff_ind == BUFF_SIZE)
			{
				print_buffer(buffer, &buff_ind); /* write(1, &format[x], 1); */
				p_char++;
			}
		}
		else
		{
			print_buffer(buffer, buff_ind);
			flags = get_flags(format, &x);
			width = get_width(format, &x, lst);
			precision = get_precision(format, &x, lst, buffer, flags,
					width, precision, size);
			if (y == -1)
			{
				return (-1);
			}
			p_char += y;
		}
	}
	print_buffer(buffer, &buff_ind);
	va_end(lst);
	return (p_char);
}

/**
 * print_buffer - prints buffer contets
 * @buffer: char array
 * @buff_ind: index of next char
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
	{
		write(1, &buffer[0], *buff_ind);
	}
	*buff_ind = 0;
}


