from animation_processing.processing import read_template, write_template 

OUTPUT_FILENAME = "../src/animations/config/sample_output.csv"
NUMBER_OF_POINTS = 100

temporary = read_template()
write_template(OUTPUT_FILENAME, number_of_points=100)

