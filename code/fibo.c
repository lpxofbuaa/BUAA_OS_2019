int fibo(int n) {
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else if (n == 2)
		return 1;
	else {
		int a = 1;
		int b = 1;
		int c = 2;
		while (n > 2) {
			c = a + b;
			a = b;
			b = c;
			n--;
		}
		return c;
	}
	return 0;
}
