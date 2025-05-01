import math
import csv

TEMPLATE_FILENAME = "../src/animations/config/templates.csv"
NUMBER_OF_LIMBS = 6

class TrigonometricError(Exception):
	"""Custom exception raised for trigonmetric argument out of bounds.

	Attributes:
		message -- explanation of the error
	"""
	def __init__(self, message):
		self.message = message
		super().__init__(self.message)

def compute_angle_1(radius, length_2, length_3):
	output = (length_2 ** 2 + radius ** 2 - length_3 ** 2) / (2 * length_2 * radius)
	if abs(output) > 1:
		raise(TrigonometricError("Angle is larger than 1."))
	return output

def compute_angle_2(radius, length_2, length_3):
	output = (-length_2 ** 2  - length_3 ** 2 + radius ** 2) / (-2 * length_2 * length_3)
	if abs(output) > 1:
		raise(TrigonometricError("Angle is larger than 1."))
	return output

def read_template(filename=TEMPLATE_FILENAME, using_header=False):
	output = {}
	with open(filename) as file_object:
		if using_header:
			heading = next(file_object)
		else:
			reader_object = csv.reader(file_object)
			for row in reader_object:
				temporary = output[row[0]] =  list(map(float, row[1:]))
	return output	

def write_template(filename, number_of_points, leg_path_dictionary):
	with open(filename, 'w', newline='') as output_file:
		csv_writer = csv.writer(output_file)
		for i in range(number_of_points):
			row = [leg_cycle(leg=x, cycle_offset=(1 - x % 2) * 50, index=i, leg_path=leg_path_dictionary) for x in range(NUMBER_OF_LIMBS)]
			row = [item for x in row for item in x]	
			csv_writer.writerow(row)

def inverse_kinematics(position_tuple):
	LENGTH_1 = 68.25
	LENGTH_2 = 110.0
	LENGTH_3 = 214.44

	y_zero_offset = 40
	leg_path = read_template()

	leg_path_y50 = leg_path['leg_path_Y50']
	leg_path_z50 = leg_path['leg_path_Z50']
	leg_path_y60 = leg_path['leg_path_Y60']
	leg_path_z60 = leg_path['leg_path_Z60']

	x, y, z = position_tuple
	theta_1 = math.atan(z / x) * 180.0 / math.pi + 90.0
	radius_x = math.sqrt(x * x + z * z) - LENGTH_1
	some_angle_2 = math.atan(y / radius_x)
	radius = math.sqrt(y * y + radius_x * radius_x)
	#print((LENGTH_2 * LENGTH_2 + radius * radius - LENGTH_3 * LENGTH_3) / (2 * LENGTH_2 * radius))
	try:
		#some_angle_1 = -math.acos((LENGTH_2 * LENGTH_2 + radius * radius - LENGTH_3 * LENGTH_3) / (2 * LENGTH_2 * radius))
		some_angle_1 = -math.acos(compute_angle_1(radius, LENGTH_2, LENGTH_3))
	except TrigonometricError:
	    print("Trigonometric argument greater than 1. Truncating value.")
	    #if compute_angle_1(radius, LENGTH_2, LENGTH_3) > 0:
	    #    some_angle_1 = -math.acos(1)
	    #else:
	    #    some_angle_1 = -math.acos(-1)
	    some_angle_1 = math.acos(1)
	theta_2 = (some_angle_2 - some_angle_1) * 180.0 / math.pi
	#print((-LENGTH_2 * LENGTH_2 - LENGTH_3 * LENGTH_3 + radius * radius) / (-2 * LENGTH_2 * LENGTH_3))
	try:
	    #some_angle_3 = math.acos((-LENGTH_2 * LENGTH_2 - LENGTH_3 * LENGTH_3 + radius * radius) / (-2 * LENGTH_2 * LENGTH_3))
		some_angle_3 = math.acos(compute_angle_2(radius, LENGTH_2, LENGTH_3))
	except TrigonometricError:
		print("Trigonometric argument is less than -1. Truncating value.")
		#if compute_angle_2(radius, LENGTH_2, LENGTH_3) > 0:
		#    some_angle_3 = math.acos(1)
		#else:
		#    some_angle_3 = math.acos(-1)
		some_angle_3 = math.acos(-1)
	theta_3 = (math.pi - some_angle_3) * 180.0 / math.pi
		
	return (theta_1, theta_2, theta_3)

def rotate_around_point(x_to_rotate, y_to_rotate, a, b, theta):
	rotated_1 = (x_to_rotate - a) * math.cos(theta * math.pi / 180.0) - (y_to_rotate - b) * math.sin(theta * math.pi / 180.0) + a
	rotated_2 = (x_to_rotate - a) * math.sin(theta * math.pi / 180.0) - (y_to_rotate - b) * math.cos(theta * math.pi / 180.0) + b

	return rotated_1, rotated_2

def leg_cycle(leg,
	cycle_offset,
	index,
	leg_path,
	ground_points=50, # Percent of time the leg is on the ground (50 or 60)
	ground_distance=90, # Distance of the robot from the ground
	radial_distance=250, # Distance from joint 1 to the tip of the leg
	y_scale=0.5,
	z_scale=2.0,
	walk_angle=0,
	points=100,
	y_zero_offset=40): # When 45 for all legs, distance from ground of robot is zero

	leg_path_y50 = leg_path['leg_path_Y50']
	leg_path_z50 = leg_path['leg_path_Z50']
	leg_path_y60 = leg_path['leg_path_Y60']
	leg_path_z60 = leg_path['leg_path_Z60']

	i = int(index + cycle_offset) % points	
	if ground_points == 50:
		x = radial_distance
		y = y_scale * leg_path_y50[i] - y_zero_offset - ground_distance
		z = z_scale * leg_path_z50[i]
	elif ground_points == 60:
		x = radial_distance
		y = y_scale * leg_path_y60[i] - y_zero_offset - ground_distance
		z = z_scale * leg_path_z60[i]
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
