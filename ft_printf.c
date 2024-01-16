#include "ft_printf.h"

static int ft_putchar(char c)
{
	return (write(1, &c, 1));
}

static int ft_putstr(char *str)
{
	int i;

	i = 0;
	if (str == NULL)
		return (write(1, "(null)", 6));
	while (str[i] != '\0')
		write(1, &str[i++], 1);
	return (i);
}

static int ft_printhex(unsigned long nbr, int maiusc)
{
	char *container;
	char *maiuscarr;
	int	len;
	int tmp;

	container = "0123456789abcdef";
	maiuscarr = "0123456789ABCDEF";
	len = 0;
	if (nbr == 0)
		return (write(1, "0", 1));
	if (nbr > 0)
	{
		tmp = nbr % 16;
		if ((nbr / 16) > 0)
			len += ft_printhex((nbr /= 16), maiusc);
		if (maiusc == FALSE)
			len += ft_putchar(container[tmp]);
		else if (maiusc == 1)
			len += ft_putchar(maiuscarr[tmp]);
	}
	return (len);
}

static int	ft_putnbr(int n)
{
	int len;

	len = 0;
	if (n == -2147483648)
	{
		len += write(1, "-2147483648", 11);
	}
	else if (n < 0)
	{
		len += write(1, "-", 1);
		n = -n;
		len += ft_putnbr(n);
	}
	else if (n > 9)
	{
		len += ft_putnbr(n / 10);
		len += ft_putnbr(n % 10);
	}
	else
		len += ft_putchar(n + 48);
	return (len);
}

static int	ft_printptr(unsigned long address)
{
	unsigned long long tmp;
	int len;

	len = 0;
	if (!address)
		return (write(1, "(nil)", 5));
	tmp = (unsigned long long)address;
	len += write(1, "0x", 2);
	len += ft_printhex(tmp, 0);
	return len;
}

static int ft_print_unsinged(unsigned long n)
{
	int len;

	len = 0;
	if (n > 9)
	{
		len += ft_print_unsinged(n / 10);
		len += ft_print_unsinged(n % 10);
	}
	else
		len += ft_putchar(n + 48);
	return (len);
}

static int	format_selector(char c, va_list args)
{
	if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(args, char*)));
	else if (c == 'x')
		return (ft_printhex((long)va_arg(args, unsigned int), 0));
	else if (c == 'X')
		return (ft_printhex((long)va_arg(args, unsigned int), 1));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr((long)va_arg(args, int)));
	else if (c == 'p')
		return ((long)ft_printptr(va_arg(args, unsigned long)));
	else if (c == '%')
		return (write(1, "%%", 1));
	else if (c == 'u')
		return (ft_print_unsinged(va_arg(args, unsigned int)));
	else
		return (write(1, &c, 1));
}

int	ft_printf(const char *format, ...)
{
	va_list args;
	int len;
	int i;

	va_start(args, format);
	i = 0;
	len = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
			len += format_selector(format[++i], args);
		else
			len += write(1, &format[i], 1);
		i++;
	}
	va_end(args);
	return (len);
}

/*
int main(void)
{
	char c = 'd';
	int p = 42;
	char *str = NULL;

	ft_printf("%%c ------------------\n");
	printf("Real: %c\n", 'c');
	ft_printf("Mine: %c\n", 'c');
	printf("Return len: %d\n", ft_printf("%c\n", 'c'));
	ft_printf("%%s ------------------\n");
	printf("Real: %s\n", "ciao");
	ft_printf("Mine: %s\n", "ciao");
	printf("Return len: %d\n", ft_printf("%s\n", "ciao"));
	printf("Real: %s\n", str);
	ft_printf("Mine: %s\n", NULL);
	ft_printf("%%x ------------------\n");
	printf("Real: %x\n", 'c');
	ft_printf("Mine: %x\n", 'c');
	printf("Real: %x\n", -42);
	ft_printf("Mine: %x\n", -42);
	printf("Real: %x\n", 0);
	ft_printf("Mine: %x\n", 0);
	ft_printf("%%X ------------------\n");
	printf("Real: %X\n", 'c');
	ft_printf("Mine: %X\n", 'c');
	printf("Real: %X\n", -42);
	ft_printf("Mine: %X\n", -42);
	ft_printf("%%d ------------------\n");
	printf("Real: %d\n", 'c');
	ft_printf("Mine: %d\n", 'c');
	printf("Real: %d\n", -42);
	ft_printf("Mine: %d\n", -42);
	ft_printf("%%i ------------------\n");
	printf("Real: %i\n", 'c');
	ft_printf("Mine: %i\n", 'c');
	printf("Real: %i\n", -42);
	ft_printf("Mine: %i\n", -42);
	printf("Real: %i\n", 042);
	ft_printf("Mine: %i\n", 042);
	printf("Real: %i\n", 0x42);
	ft_printf("Mine: %i\n", 0x42);
	ft_printf("%%u ------------------\n");
	printf("Real: %u\n", 'c');
	ft_printf("Mine: %u\n", 'c');
	printf("Real: %u\n", -42);
	ft_printf("Mine: %u\n", -42);
	printf("Real: %u\n", -2);
	ft_printf("Mine: %u\n", -2);
	printf("Real: %u\n", 042);
	ft_printf("Mine: %u\n", 042);
	printf("Real: %u\n", 0x42);
	ft_printf("Mine: %u\n", 0x42);
	ft_printf("%%p ------------------\n");
	printf("Real: %p\n", &c);
	ft_printf("Mine: %p\n", &c);
	printf("Real: %p\n", &p);
	ft_printf("Mine: %p\n", &p);
	//printf("Real: %p\n", -1);
	ft_printf("Mine: %p\n", -1);
	printf("Return len: %d\n", ft_printf("Mine: %p\n", -1));
	ft_printf("%%%% ------------------\n");
	printf("Real: %%\n");
	printf("Mine: %%\n");
	return (0);
}
*/

// 1 hex letter represents 4 bits

// cspdiuxX%