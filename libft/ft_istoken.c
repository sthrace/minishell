int	ft_istoken(int c)
{
	if ((c >= 33 && c <= 58) || (c >= 60 && c <= 126))
		return (c);
	return (0);
}