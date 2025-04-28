low_pass_filter(xn, xn_previous, yn_previous, filter_counter, cutoff_freq, dt):
	omega_t = 6.28 * cutoff_freq * dt
	a = (2.0 - omega_t) / (2.0 + omega_t)
	b = omega_t / (2.0 + omega_t)
	yn = a * yn_previous + b * xn + b * xn_previous
	xn_previous = xn
	yn_previous = yn
	filter_counter = filter_counter + 1
	return xn, yn, xn_previous, yn_previous
