import math

TEMPLATE_FILENAME = "src/animations/config/templates.csv"

def read_template():
	pass

def inverse_kinematics(position_tuple):
	LENGTH_1 = 68.25
	LENGTH_2 = 110.0
	LENGTH_3 = 214.44

	y_zero_offset = 40
	leg_path_y50, leg_path_z50, leg_path_y60, leg_path_z60 = read_template()

	x, y, z = position_tuple
	theta_1 = math.atan(z / x) * 180.0 / math.pi + 90.0
	radius_x = math.sqrt(x * x + z * z) - LENGTH_1
	some_angle_2 = math.atan(y / radius_x)
	radius = math.sqrt(y * y + radius_x * radius_x)
	some_angle_1 = -math.acos((LENGTH_2 * LENGTH_2 + radius * radius - LENGTH_3 * LENGTH_3) / (2 * LENGTH_2 * radius))
	theta_2 = (some_angle_2 - some_angle_1) * 180.0 / math.pi
	some_angle_3 = math.acos((-LENGTH_2 * LENGTH_2 - LENGTH_3 * LENGTH_3 + radius * radius) / (-2 * LENGTH_2 * LENGTH_3))
	theta_3 = (math.pi - some_angle_3) * 180.0 / math.pi

	return (theta_1, theta_2, theta_3)

def rotate_around_point(x_to_rotate, y_to_rotate, a, b, theta):
	rotated_1 = (x_to_rotate - a) * math.cos(theta * math.pi / 180.0) - (y_to_rotate - b) * math.sin(theta * math.pi / 180.0) + a
	rotated_2 = (x_to_rotate - a) * math.sin(theta * math.pi / 180.0) - (y_to_rotate - b) * math.cos(theta * math.pi / 180.0) + b

	return rotated_1, rotated_2

def leg_cycle(leg, cycle_offset, ground_points, ground_distance, radial_distance, y_scale, z_scale, index, walk_angle, points=100):
	i = int(index + cycle_offset) % points	
	if ground_points == 50:
		x = radial_distance
		y = y_scale * leg_path_y50[k] - y_zero_offset - ground_distance
		z = z_scale * leg_path_z50[k]
	elif ground_points == 60:
		x = radial_distance
		y = y_scale * leg_path_y60[k] - y_zero_offset - ground_distance
		z = z_scale * leg_path_z60[k]
	else:
		x = 0
		y = 0
		z = 0

	if leg == 1:
		angle = 60.0 + walk_angle
	elif leg == 2:
		angle = 0.0 + walk_angle
	elif leg == 3:
		angle = -60.0 + walk_angle
	elif leg == 4:
		angle = 60 - walk_angle
	elif leg == 5:
		angle = 0 - walk_angle
	elif leg == 6:
		angle = - 60 - walk_angle
	else:
		angle = 0

	rotated_1, rotated_2 = rotate_around_point(z, x, 0, radial_distance, angle)
	z = rotated_1
	x = rotated_2
	theta_1, theta_2, theta_3 = inverse_kinematics((x, y, z))

	return (theta_1, theta_2, theta_3)
